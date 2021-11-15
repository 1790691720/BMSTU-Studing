import json

from flask import Blueprint, render_template, url_for, request
from flask_table import Table, Col
from flask_table.html import element

from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

edit_app = Blueprint('edit', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/db_config.json', 'r')))


class ExternalURLCol(Col):
    def __init__(self, name, url_attr, class_attr, **kwargs):
        self.url_attr = url_attr
        self.class_attr = class_attr
        super(ExternalURLCol, self).__init__(name, **kwargs)

    def td_contents(self, item, attr_list):
        text = self.from_attr_list(item, attr_list)
        url = self.from_attr_list(item, [self.url_attr])
        classURL = self.from_attr_list(item, [self.class_attr])
        return element('a', {'href': url, 'class': classURL}, content=text)


class ItemTableEditUsers(Table):
    idLogin = Col('id')
    Login = Col('Логин')
    PasswordL = Col('Пароль')
    AccessLevel = Col('Уровень доступа')
    UpdateLink = ExternalURLCol(' ', url_attr='urlUpdate', attr='nameUpdate', class_attr="classUpdate")
    DeleteLink = ExternalURLCol(' ', url_attr='urlDelete', attr='nameDelete', class_attr="classDelete")


class ItemTableEditProducts(Table):
    idProduct = Col('Артикул')
    Name = Col('Продукт')
    Material = Col('Материал')
    UnitOfMeasurement = Col('Единица измерения')
    PricePerUnit = Col('Цена')
    ActualQuantity = Col('Актуальное количество')
    FixationDate = Col('Дата фиксации')
    ReservedProduct = Col('Зарезервировано продукта')
    ReservationDate = Col('Дата резервации')
    UpdateLink = ExternalURLCol(' ', url_attr='urlUpdate', attr='nameUpdate', class_attr="classUpdate")
    DeleteLink = ExternalURLCol(' ', url_attr='urlDelete', attr='nameDelete', class_attr="classDelete")


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
        user['classUpdate'] = f""
        user['urlDelete'] = url_for('edit.edit_users') + f'/delete' + f'/{idLogin}'
        user['nameDelete'] = f'Удалить'
        user['classDelete'] = f"confirmable"
    table = ItemTableEditUsers(result)

    HTMLtable = table.__html__()
    file = open(r'.\edit\templates\edit_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'edit_base.html\' %}{% block child %}<div class="article_3">')
    file.write(HTMLtable)
    file.write('</div>{% endblock %}')
    file.close()

    return render_template('edit_child.html', title="Все пользователи",url_for_insert=url_for('edit.edit_insert_user'), insertWhat="Добавить пользователя")


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
        return render_template('edit_result_user.html', url_back='../users')


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
        return render_template('edit_result_user.html', url_back='../users')


@edit_app.route('/users/delete/<user>')
@group_permission_decorator
def edit_delete_user(user):
    SQLserver.update_insert('edit_deleteUser.sql', idLogin=int(user))
    return render_template('edit_delete_user.html', idLogin=int(user))


# endregion

# region Worker

@edit_app.route('/products')
@group_permission_decorator
def edit_products():
    result = SQLserver.request('edit_AllProductsInfo.sql')
    for product in result:
        idProduct = product['idProduct']
        product['urlUpdate'] = url_for('edit.edit_products') + f'/{idProduct}'
        product['nameUpdate'] = f'Редактировать'
        product['classUpdate'] = f""
        product['urlDelete'] = url_for('edit.edit_products') + f'/delete' + f'/{idProduct}'
        product['nameDelete'] = f'Удалить'
        product['classDelete'] = f"confirmable"
    table = ItemTableEditProducts(result)

    HTMLtable = table.__html__()
    file = open(r'.\edit\templates\edit_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'edit_base.html\' %}{% block child %}<div class="article_3">')
    file.write(HTMLtable)
    file.write('</div>{% endblock %}')
    file.close()

    return render_template('edit_child.html', title="Все продукты",url_for_insert=url_for('edit.edit_insert_product'), insertWhat="Добавить продукт")


@edit_app.route('/products/<product>', methods=['GET', 'POST'])
@group_permission_decorator
def edit_product(product):
    if request.method == 'GET':
        result = SQLserver.request('edit_getProduct.sql', id=product)[0]
        return render_template('edit_product.html',
                               idProduct=result['idProduct'],
                               Name=result['Name'],
                               Material=result['Material'],
                               UnitOfMeasurement=result['UnitOfMeasurement'],
                               PricePerUnit=result['PricePerUnit'],
                               ActualQuantity=result['ActualQuantity'],
                               FixationDate=result['FixationDate'],
                               ReservedProduct=result['ReservedProduct'],
                               ReservationDate=result['ReservationDate'])
    else:
        idProduct = int(product)
        Name = request.form.get('Name')
        Material = request.form.get('Material')
        UnitOfMeasurement = request.form.get('UnitOfMeasurement')
        PricePerUnit = request.form.get('PricePerUnit')
        ActualQuantity = request.form.get('ActualQuantity')
        FixationDate = request.form.get('FixationDate')
        ReservedProduct = request.form.get('ReservedProduct')
        ReservationDate = request.form.get('ReservationDate')
        SQLserver.update_insert('edit_updateProduct.sql',
                                idProduct=idProduct,
                                Name=Name,
                                Material=Material,
                                UnitOfMeasurement=UnitOfMeasurement,
                                PricePerUnit=PricePerUnit,
                                ActualQuantity=ActualQuantity,
                                FixationDate=FixationDate,
                                ReservedProduct=ReservedProduct,
                                ReservationDate=ReservationDate)
        return render_template('edit_result_product.html', url_back='../products')




@edit_app.route('/products/add', methods=['GET', 'POST'])
@group_permission_decorator
def edit_insert_product():
    if request.method == 'GET':
        return render_template('edit_insert_product.html')
    else:
        Name = request.form.get('Name')
        Material = request.form.get('Material')
        UnitOfMeasurement = request.form.get('UnitOfMeasurement')
        PricePerUnit = request.form.get('PricePerUnit')
        ActualQuantity = request.form.get('ActualQuantity')
        FixationDate = request.form.get('FixationDate')
        ReservedProduct = request.form.get('ReservedProduct')
        ReservationDate = request.form.get('ReservationDate')
        SQLserver.update_insert('edit_insertProduct.sql',
                                Name=Name,
                                Material=Material,
                                UnitOfMeasurement=UnitOfMeasurement,
                                PricePerUnit=PricePerUnit,
                                ActualQuantity=ActualQuantity,
                                FixationDate=FixationDate,
                                ReservedProduct=ReservedProduct,
                                ReservationDate=ReservationDate)
        return render_template('edit_result_product.html', url_back='../products')

@edit_app.route('/products/delete/<product>')
@group_permission_decorator
def edit_delete_product(product):
    SQLserver.update_insert('edit_deleteProduct.sql', idProduct=int(product))
    return render_template('edit_delete_product.html', idProduct=int(product))

# endregion
