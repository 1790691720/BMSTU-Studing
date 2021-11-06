import json

from flask import Blueprint, render_template, url_for, request
from flask_table import Table, Col
from flask_table.html import element

from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

edit_app = Blueprint('edit', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/db_config.json', 'r')))


class ExternalURLCol(Col):
    def __init__(self, name, url_attr, **kwargs):
        self.url_attr = url_attr
        super(ExternalURLCol, self).__init__(name, **kwargs)

    def td_contents(self, item, attr_list):
        text = self.from_attr_list(item, attr_list)
        url = self.from_attr_list(item, [self.url_attr])
        return element('a', {'href': url}, content=text)


class ItemTableEditUsers(Table):
    idLogin = Col('id')
    Login = Col('Логин')
    PasswordL = Col('Пароль')
    AccessLevel = Col('Уровень доступа')
    UpdateLink = ExternalURLCol(' ', url_attr='urlUpdate', attr='nameUpdate')
    DeleteLink = ExternalURLCol(' ', url_attr='urlDelete', attr='nameDelete')


# region General
@edit_app.route('/')
@group_permission_decorator
def edit_index():
    return render_template('edit_index.html')


# endregion

# region Admin
@edit_app.route('/users')
@group_permission_decorator
def edit_users():
    result = SQLserver.request('edit_AllUsersInfo.sql')
    for user in result:
        idLogin = user['idLogin']
        user['urlUpdate'] = url_for('edit.edit_users') + f'/{idLogin}'
        user['nameUpdate'] = f'Редактировать'
        user['urlDelete'] = url_for('edit.edit_users') + f'/delete' + f'/{idLogin}'
        user['nameDelete'] = f'Удалить'
        print()
    table = ItemTableEditUsers(result)

    HTMLtable = table.__html__()
    file = open(r'.\edit\templates\edit_users_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'edit_users_base.html\' %}{% block child %}<div class="article_3">')
    file.write(HTMLtable)
    file.write('</div>{% endblock %}')
    file.close()

    return render_template('edit_users_child.html')


@edit_app.route('/users/<user>', methods=['GET', 'POST'])
@group_permission_decorator
def edit_user(user):
    if request.method == 'GET':
        result = SQLserver.request('edit_getUser.sql', id=user)[0]
        return render_template('edit_user.html', idLogin=result['idLogin'], Login=result['Login'],
                               PasswordL=result['PasswordL'], AccessLevel=result['AccessLevel'])
    else:
        idLogin = int(user)
        Login = request.form.get('Login')
        PasswordL = request.form.get('PasswordL')
        AccessLevel = int(request.form.get('AccessLevel'))
        SQLserver.update_insert('edit_updateUser.sql', idLogin=idLogin, Login=Login, PasswordL=PasswordL,
                                AccessLevel=AccessLevel)
        return render_template('edit_result.html', url_back='../users')

@edit_app.route('/users/add', methods=['GET', 'POST'])
@group_permission_decorator
def edit_insert_user():
    if request.method == 'GET':
        return render_template('edit_insert_user.html')
    else:
        Login = request.form.get('Login')
        PasswordL = request.form.get('PasswordL')
        AccessLevel = int(request.form.get('AccessLevel'))
        SQLserver.update_insert('edit_insertUser.sql', Login=Login, PasswordL=PasswordL,
                                AccessLevel=AccessLevel)
        return render_template('edit_result.html', url_back='../users')

@edit_app.route('/users/delete/<user>')
@group_permission_decorator
def edit_delete_user(user):
    SQLserver.update_insert('edit_deleteUser.sql', idLogin=int(user))
    return render_template('edit_delete_user.html', idLogin=int(user))

# endregion
