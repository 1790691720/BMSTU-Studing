from flask import Flask, render_template, request, redirect
from pymysql import connect

app = Flask(__name__)


@app.route('/')  # => 127.0.0.1:5001
def index():
    return render_template('index.html')


@app.route('/greeting/<name>')
def GreetingHandle(name):
    return f'Hello {name}'


@app.route('/users/<int:userID>')
def SearchUser(userID: int):
    users = [
        {'_id': 1, 'name': 'ivan1'},
        {'_id': 2, 'name': 'ivan2'},
        {'_id': 3, 'name': 'ivan3'},
    ]

    user = None

    for _user in users:
        if _user['_id'] == userID:
            user = _user
            break
    if user is None:
        return 'Not found1111'
    return user


@app.route('/links234')
def HandleLinks234():
    action = request.args.get('action', None)
    if action == 'search':
        return redirect('/users/1')
    elif action == 'home':
        return redirect('/')
    return render_template('links.html')


@app.route('/form', methods=['GET', 'POST'])
def HandleForm():
    if request.method == 'GET':
        return render_template('forms.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')

        if login and password:
            if login == 'qwe1' and password == 'qqq1':
                return 'OK'

        return 'Invalid'


@app.route('/db/user', methods=['GET', 'POST'])
def SearchUserDataBase():
    if request.method == 'GET':
        return render_template('forms.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')

        dbconfig = {'host': 'localhost', 'port': 3306, 'user': 'root', 'password': "09051945", 'db': 'lab_schema'}

        connection = connect(host='localhost', port=3306, user='root', password='09051945', db='lab_schema')
        cursor = connection.cursor()
        _sql = f"SELECT * FROM customer WHERE idCustomer='{login}' AND City='{password}'"
        cursor.execute(_sql)
        raw_sql = cursor.fetchall()
        connection.close()

        result = []
        for row in raw_sql:
            result.append(
                dict(zip(['idCustomer', 'Name', 'Surname', 'City', 'Telephone', 'TotalSum', 'ContractDate'], row)))

        if not result:
            return 'Not Found'
        return result


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
