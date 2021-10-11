import json

from flask import Blueprint, render_template, request
from flask_table import Table, Col

from sql.SQLmaster import SQLmaster

requests_app = Blueprint('requests', __name__, template_folder='templates')

SQLserver = SQLmaster(json.load(open('sql/configDataBase.json', 'r')))


class ItemTableAverageTime(Table):
    idTest = Col('idTest')
    Name = Col('Name')
    AverageTime = Col('AverageTime')
class ItemTableBetweenDate(Table):
    idPlan = Col('idPlan')
    hardwareName = Col('hardwareName')
    datePlan = Col('datePlan')


@requests_app.route('/')
def requests_index():
    return render_template('request_index.html')


@requests_app.route('/averageTime', methods=['GET', 'POST'])
def requests_averageTime():
    if request.method == 'GET':
        return render_template('request_averageTime.html')
    else:
        average_time = request.form.get('averageTime')
        result = SQLserver.request('request1.sql', averageTime=average_time)
        table = ItemTableAverageTime(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="table">')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
        return render_template('request_result_child.html')


@requests_app.route('/betweenDates', methods=['GET', 'POST'])
def requests_betweenDates():
    if request.method == 'GET':
        return render_template('request_betweenDates.html')
    else:
        date_min = request.form.get('date_min')
        date_max = request.form.get('date_max')
        result = SQLserver.request('request2.sql', firstDate=date_min, secondDate=date_max)
        table = ItemTableBetweenDate(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="table">')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')
