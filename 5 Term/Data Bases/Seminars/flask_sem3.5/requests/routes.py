from flask import Blueprint, render_template

requests_app = Blueprint('requests', __name__, template_folder='templates')

@requests_app.route('/')
def requests_index():
    return render_template('request_index.html')

@requests_app.route('/averageTime')
def requests_averageTime():
    return render_template('request_averageTime.html')

@requests_app.route('/betweenDates')
def requests_betweenDates():
    return render_template('request_betweenDates.html')