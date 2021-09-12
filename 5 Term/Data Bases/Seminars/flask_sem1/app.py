import os
from flask import Flask, render_template
from datetime import datetime

app = Flask(__name__)


@app.route('/')  # => 127.0.0.1:5001
def index():
    return 'Hello from Flask'


@app.route('/greeting')  # => 127.0.0.1:5001/greeting
def greeting_handler():
    return 'Greeting'


@app.route('/info')  # => 127.0.0.1:5001/info
def info_handler():
    return f'Now: {datetime.now()}, PID: {os.getpid()}'


@app.route('/home')  # => 127.0.0.1:5001/home
def homepage_handler():
    return render_template('index.html')


@app.route('/home_dynamic')  # => 127.0.0.1:5001/home_dynamic
def homepage_dynamic_handler():
    context = {
        'name': 'John',
        'list_items': ['a', 'b', 'c'],
        'today': datetime.now()
    }
    return render_template('dynamic.html', **context)


@app.route('/child')  # => 127.0.0.1:5001/child
def child_handler():
    return render_template('child.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
