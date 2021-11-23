import json

from flask import Blueprint, render_template, request, session

from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

auth_app = Blueprint('auth', __name__, template_folder='templates')


LevelToName = {'0': 'Пользователь',
               '1': 'Администратор',
               '2': 'Super Пользователь'}


@auth_app.route('/', methods=['GET', 'POST'])
@group_permission_decorator
def auth_index():
    if request.method == 'GET':
        return render_template('auth_index.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')
        SQLserver = SQLmaster(json.load(open('config/db_config.json', 'r')))
        result = SQLserver.request('LoginPass.sql', Login=login, PasswordL=password)

        if len(result) == 0:
            return render_template('auth_failed.html')
        else:
            session['group_name'] = LevelToName[f"{result[0]['AccessLevel']}"]
            return render_template('auth_successfully.html', name=session['group_name'])


@auth_app.route('/unauth')
@group_permission_decorator
def auth_unauth():
    session.clear()
    return render_template('auth_unauth.html', name='Гость')
