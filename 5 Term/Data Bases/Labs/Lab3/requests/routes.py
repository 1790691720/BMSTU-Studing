import json

from flask import Blueprint, render_template, request
from flask_table import Table, Col

from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

requests_app = Blueprint('requests', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/db_config.json', 'r')))


class ItemTableAverageTime(Table):
    idTest = Col('Номер теста')
    Name = Col('Имя')
    AverageTime = Col('Среднее время выполнения')


class ItemTableBetweenDate(Table):
    idPlan = Col('Номер плана')
    hardwareName = Col('Устройство')
    datePlan = Col('Дата')


def request_execute(table):
    HTMLtable = table.__html__()
    file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')

    file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')
    if HTMLtable == "<p>No Items</p>":
        file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
    else:
        file.write(HTMLtable)
    file.write('</div>{% endblock %}')
    file.close()


@requests_app.route('/')
@group_permission_decorator
def requests_index():
    return render_template('request_index.html')


@requests_app.route('/averageTime', methods=['GET', 'POST'])
@group_permission_decorator
def requests_averageTime():
    if request.method == 'GET':
        return render_template('request_averageTime.html')
    else:
        average_time = request.form.get('averageTime')
        result = SQLserver.request('request1.sql', averageTime=average_time)
        table = ItemTableAverageTime(result)
        request_execute(table)
        return render_template('request_result_child.html', url_back='./averageTime',
                               title=f'Тесты, время выполнения которых больше чем {average_time}')


@requests_app.route('/betweenDates', methods=['GET', 'POST'])
@group_permission_decorator
def requests_betweenDates():
    if request.method == 'GET':
        return render_template('request_betweenDates.html')
    else:
        date_min = request.form.get('date_min')
        date_max = request.form.get('date_max')
        result = SQLserver.request('request2.sql', firstDate=date_min, secondDate=date_max)
        table = ItemTableBetweenDate(result)
        request_execute(table)
    return render_template('request_result_child.html', url_back='./betweenDates',
                           title=f'Планы тестирования между {date_min} и {date_max}')
