import json

from flask import Flask, render_template, session

from access import group_validation_decorator, group_permission_decorator
from auth.routes import auth_app
from reports.routes import reports_app
from requests.routes import requests_app
from sql.SQLmaster import SQLmaster

app = Flask(__name__)

dbconfig = json.load(open('./sql/configDataBase.json', 'r'))
app.config['DB_CONFIG'] = dbconfig
app.config['ACCESS_CONFIG']=json.load(open('./configs/access.json', 'r'))
app.config['SECRET_KEY'] = 'Secret'
SQLserver = SQLmaster(dbconfig)

app.register_blueprint(requests_app, url_prefix='/requests')
app.register_blueprint(reports_app, url_prefix='/reports')
app.register_blueprint(auth_app, url_prefix='/auth')



@app.route('/')
@group_permission_decorator
def index():
    return render_template('index.html')


@app.route('/counter')
@group_permission_decorator
def counter():
    count = session.get('counter', None)
    if count is None:
        session['counter'] = 0
    session['counter'] = session['counter'] + 1
    return f"{session['counter']}"


@app.route('/clear_session')
def clear_session():
    session.clear()
    return f"Cleared"


@app.route('/exit')
def exit():
    return render_template('exit.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
