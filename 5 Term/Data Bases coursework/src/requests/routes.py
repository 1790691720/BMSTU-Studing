import json

from flask import Blueprint, render_template, request
from flask_table import Table, Col

from sql.SQLmaster import SQLmaster

requests_app = Blueprint('requests', __name__, template_folder='templates')

SQLserver = SQLmaster(json.load(open('sql/configDataBase.json', 'r')))


class ItemTableRequest1(Table):
    idCustomer = Col('idCustomer')
    Name = Col('Name')
    City = Col('City')
    Telephone = Col('Telephone')
    TotalSum = Col('TotalSum')
    ContractDate = Col('ContractDate')


class ItemTableRequest2(Table):
    idOrder = Col('idOrder')
    idCustomer = Col('idCustomer')
    idProduct = Col('idProduct')
    OrderDate = Col('OrderDate')
    OrderSum = Col('OrderSum')
    OrderStatus = Col('OrderStatus')
    OrderStatusDate = Col('OrderStatusDate')
    OrderQuantity = Col('OrderQuantity')


class ItemTableRequest3(Table):
    OrderStatus = Col('OrderStatus')
    countOrderStatus = Col('COUNT(OrderStatus)')


class ItemTableRequest4(Table):
    idCustomer = Col('idCustomer')
    Telephone = Col('Telephone')


class ItemTableRequest5(Table):
    idCustomer = Col('idCustomer')
    OrderSum = Col('OrderSum')


class ItemTableRequest6(Table):
    idCustomer = Col('idCustomer')
    OrderSum = Col('OrderSum')


@requests_app.route('/')
def requests_index():
    return render_template('request_index.html')


@requests_app.route('/request1', methods=['GET', 'POST'])  # TODO: переделать  HTML
def requests_request1():
    if request.method == 'GET':
        return render_template('request_1.html')
    else:
        year = request.form.get('year')
        month = request.form.get('month')
        result = SQLserver.request('1_request.sql', year=year, month=month)
        table = ItemTableRequest1(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding="utf-8")
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div>')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
        return render_template('request_result_child.html')


@requests_app.route('/request2', methods=['GET', 'POST'])
def requests_request2():
    if request.method == 'GET':
        return render_template('request_2.html')
    else:
        numberParam = request.form.get('numberParam')
        result = SQLserver.request('2_request.sql', lastDays=numberParam)
        table = ItemTableRequest2(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="table">')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request3', methods=['GET', 'POST'])
def requests_request3():
    if request.method == 'GET':
        return render_template('request_3.html')
    else:
        numberParam = request.form.get('numberParam')
        result = SQLserver.request('3_request.sql', lastDays=numberParam)
        for temp in result:
            temp['countOrderStatus'] = temp['COUNT(OrderStatus)']
            del temp['COUNT(OrderStatus)']
        table = ItemTableRequest3(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="table">')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request4', methods=['GET', 'POST'])
def requests_request4():
    if request.method == 'GET':
        return render_template('request_4.html')
    else:
        telephoneLike = request.form.get('telephoneLike')
        result = SQLserver.request('4_request.sql', telephoneLike=telephoneLike)
        table = ItemTableRequest4(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="table">')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request5', methods=['GET', 'POST'])
def requests_request5():
    if request.method == 'GET':
        return render_template('request_5.html')
    else:
        numberParam = request.form.get('numberParam')
        result = SQLserver.request('5_request.sql', numberParam=numberParam)
        for temp in result:
            temp['OrderSum'] = temp['SUM(OrderSum)']
            del temp['SUM(OrderSum)']
        table = ItemTableRequest5(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="table">')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request6', methods=['GET', 'POST'])  # TODO: хз что как параметры
def requests_request6():
    if request.method == 'GET':
        return render_template('request_6.html')
    else:
        date_min = request.form.get('date_min')
        date_max = request.form.get('date_max')
        result = SQLserver.request('request2.sql', firstDate=date_min, secondDate=date_max)
        table = ItemTableRequest6(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="table">')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')
