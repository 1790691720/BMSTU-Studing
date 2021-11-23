import json

from flask import Blueprint, request, session, render_template, redirect, url_for

from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

basket_app = Blueprint('basket', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/db_config.json', 'r')))


@basket_app.route('/', methods=['GET', 'POST'])
@group_permission_decorator
def basket_index():
    if request.method == 'GET':
        tests = SQLserver.request('basket_allPlans.sql')
        basketId = session.get('basket', [])
        basket = []
        for id in basketId:
            basket.append(SQLserver.request('basket_get_test.sql', idTest=int(id))[0])
            for i in range(len(tests)):
                cur = basket[len(basket) - 1]
                test = tests[i]
                if cur['idTest'] == test['idTest']:
                    tests.pop(i)
                    break
        return render_template('basket_index.html', tests=tests, basket=basket)
    else:
        print(request.form)
        if request.form['WhatRow'] == 'Add':
            idTest = request.form['plan_id']
            b = session.get('basket', [])
            if b is None:
                b = []
            b.append(idTest)
            session['basket'] = b
            return redirect('/basket')
        elif request.form['WhatRow'] == 'Buy':
            if 'basket' in session:
                device = request.form['device']
                SQLserver.update_insert('basket_insert_test_plan.sql', hardwareName=device)
                lastPlan = SQLserver.request('basket_get_last_plan.sql')[0]['idPlan']
                for idTest in session['basket']:
                    SQLserver.update_insert('basket_insert_test_in_plan.sql', idTest=int(idTest), idPlan=lastPlan)

                session.pop('basket')
                return render_template('basket_result.html')
            else:
                redirect('/basket')


@basket_app.route('/clear_basket')
@group_permission_decorator
def clear_basket():
    if 'basket' in session:
        session.pop('basket')
    return redirect('/basket')
