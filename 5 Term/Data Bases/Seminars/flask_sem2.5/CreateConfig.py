import json

import pymysql

if __name__ == '__main__':
    config = {
        'host': 'localhost',
        'port': 3306,
        'user': 'root',
        'password': "1234",
        'db': 'testing plan'}
    try:
        connection = pymysql.connect(**config)
        print('Connected succesfully.')
        print('Created configDataBase.json.')
        json.dump(config, open('configDataBase.json', 'w+'))

        print("Close connection")
        connection.close()

    except Exception as ex:
        print("Connection refused.")
        print(ex)
