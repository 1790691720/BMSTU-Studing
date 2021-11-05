import json

from flask import Blueprint, render_template, url_for
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
    idLogin = Col('idLogin')
    Login = Col('Login')
    PasswordL = Col('Password')
    AccessLevel = Col('AccessLevel')
    Link = ExternalURLCol(' ', url_attr='url', attr='name')


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
        test = url_for('edit.edit_users')
        idLogin = user['idLogin']
        user['url'] = test + f'/{idLogin}'
        user['name'] = f'Редактировать'
        print()
    table = ItemTableEditUsers(result)

    return table.__html__()  # TODO делать красивую страницу


@edit_app.route('/users/<user>')
@group_permission_decorator
def edit_user(user):
    result = SQLserver.request('edit_getUser.sql', id=user)


    return f'{result}'
# endregion
