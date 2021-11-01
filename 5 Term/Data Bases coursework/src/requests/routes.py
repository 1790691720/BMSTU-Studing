import json

from flask import Blueprint, render_template, request
from flask_table import Table, Col

from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

requests_app = Blueprint('requests', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/db_config.json', 'r')))

LevelToName = {'0': 'Разработчик',
               '1': 'Администратор',
               '2': 'Директор',
               '3': 'Работник склада',
               '4': 'Покупатель'}
NameToLevel = {'Разработчик': '0',
               'Администратор': '1',
               'Директор': '2',
               'Работник склада': '3',
               'Покупатель': '4'}


class ItemTableAllUsers(Table):
    Login = Col('Логин')
    AccessLevel = Col('Уровень доступа')


class ItemTableCustomerOrders(Table):
    idOrder = Col('Номер заказа')
    idProduct = Col('Артикул')
    OrderQuantity = Col('Количество')
    OrderSum = Col('Сумма заказа')
    OrderDate = Col('Дата заказа')
    OrderStatus = Col('Статус')
    OrderStatusDate = Col('Дата последнего изменения статуса')

class ItemTableOrdersBetweenDates(Table):
    idOrder = Col('Номер заказа')
    idProduct = Col('Артикул')
    OrderQuantity = Col('Количество')
    OrderSum = Col('Сумма заказа')
    OrderDate = Col('Дата заказа')

class ItemTableOrdersWithMinSum(Table):
    idOrder = Col('Номер заказа')
    idProduct = Col('Артикул')
    OrderQuantity = Col('Количество')
    OrderSum = Col('Сумма заказа')
    OrderDate = Col('Дата заказа')

class ItemTableProductsWithLesserQuantity(Table):
    idProduct = Col('Артикул')
    Name = Col('Продукт')
    ActualQuantity = Col('Актуальное количество')
    FixationDate = Col('Дата фиксации')
    ReservedProduct = Col('Зарезервировано продукта')
    RevervationDate = Col('Дата резервации')

def request_execute(table):
    HTMLtable = table.__html__()
    file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')

    file.write('{% extends \'request_result_base.html\' %}{% block child %}<div class="article_3">')
    if HTMLtable == "<p>No Items</p>":
        file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
    else:
        file.write(HTMLtable)
    file.write('</div>{% endblock %}')
    file.close()


# region General
@requests_app.route('/')
@group_permission_decorator
def requests_index():
    return render_template('request_index.html')  # TODO: показывать только разрешенные запросы


# endregion

# region Admin
@requests_app.route('/AllUsers', methods=['GET', 'POST'])
@group_permission_decorator
def requests_allUsers():
    if request.method == 'GET':
        return render_template('request_allUsers.html')
    else:
        accessLevel = request.form.get('accessLevel')
        if accessLevel == 'Все':
            result = SQLserver.request('requests_allUsers.sql')
            title = f'Все пользователи'
        else:
            result = SQLserver.request('requests_usersWithId.sql', accessLevel=NameToLevel[accessLevel])
            title = f'Пользователи с уровнем допуска {accessLevel}'
        table = ItemTableAllUsers(result)
        request_execute(table)
        return render_template('request_result_child.html', url_back='./allUsers',
                               title=title)


# endregion

# region Customer
@requests_app.route('/idCustomer', methods=['GET', 'POST'])
@group_permission_decorator
def requests_idCustomer():
    customerNames = SQLserver.request('requests_CustomerNames.sql')
    if request.method == 'GET':
        file = open(r'.\requests\templates\request_idCustomer_child.html', 'w', encoding='utf-8')

        file.write(
            '{% extends \'request_idCustomer_base.html\' %}{% block child %}<div><select name="customerName">')
        for name in customerNames:
            temp = name['Name']
            file.write(f'<option>{temp}</option>')
        file.write('</select></div>{% endblock %}')
        file.close()

        return render_template('request_idCustomer_child.html')
    else:
        customerName = request.form.get('customerName')
        title = f'Заказы заказчика {customerName}'
        for name in customerNames:
            if name['Name'] == customerName:
                customerName = int(name['idCustomer'])
                break
        result = SQLserver.request('requests_customerOrders.sql',
                                   customerName=customerName)
        for i in range(len(result)):
            result[i]['idOrder'] = i + 1
        table = ItemTableCustomerOrders(result)
        request_execute(table)
        return render_template('request_result_child.html', url_back='./idCustomer',
                               title=title)


# endregion

# region Director
@requests_app.route('/OrdersBetweenDates', methods=['GET', 'POST'])
@group_permission_decorator
def requests_ordersBetweenDates():
    if request.method == 'GET':
        return render_template('request_ordersBetweenDates.html')
    else:
        dateMin = request.form.get('dateMin')
        dateMax = request.form.get('dateMax')
        result = SQLserver.request('requests_ordersBetweenDates.sql', dateMin=dateMin, dateMax=dateMax)

        table = ItemTableOrdersBetweenDates(result)
        request_execute(table)
        return render_template('request_result_child.html', url_back='./OrdersBetweenDates',
                               title=f"Заказы между {dateMin} и {dateMax}")

@requests_app.route('/OrdersWithMinSum', methods=['GET', 'POST'])
@group_permission_decorator
def requests_ordersWithMinSum():
    if request.method == 'GET':
        return render_template('request_ordersWithMinSum.html')
    else:
        sumMin = request.form.get('sumMin')
        result = SQLserver.request('request_ordersWithMinSum.sql', sumMin=sumMin)

        table = ItemTableOrdersWithMinSum(result)
        request_execute(table)
        return render_template('request_result_child.html', url_back='./request_ordersWithMinSum',
                               title=f"Заказы с минимальной суммой {sumMin}")

# endregion




# region Worker

@requests_app.route('/ProductsWithLesserQuantity', methods=['GET', 'POST'])
@group_permission_decorator
def requests_ProductsWithLesserQuantity():
    if request.method == 'GET':
        return render_template('request_ProductsWithLesserQuantity.html')
    else:
        quantityProduct = request.form.get('quantityProduct')
        result = SQLserver.request('request_ProductsWithLesserQuantity.sql', quantityProduct=quantityProduct)

        table = ItemTableProductsWithLesserQuantity(result)
        request_execute(table)
        return render_template('request_result_child.html', url_back='./ProductsWithLesserQuantity',
                               title=f"Все продукты, количество которых меньше чем {quantityProduct}")
# endregion
