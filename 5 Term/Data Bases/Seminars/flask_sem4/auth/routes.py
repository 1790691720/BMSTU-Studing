from flask import Blueprint, render_template, request, session

from access import group_permission_decorator

auth_app = Blueprint('auth', __name__, template_folder='templates')


@auth_app.route('/login', methods=['GET', 'POST'])
@group_permission_decorator
def login_page():
    if request.method == 'GET':
        return render_template('login.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')
        if login == 'admin' and password == 'admin':
            session['group_name'] = 'admin'
            return "Logged in as ADMIN"
        if login == 'kuku' and password == 'kuku':
            session['group_name'] = 'typical'
            return "Logged in as TYPICAL"
        return "invalid, idi domoi"
