from dbcm import UseDataBase
import json


def work(dbconfig, _SQL, schema):
    with UseDataBase as cursor:
        cursor.execute(_SQL)
        result = []
        for str in cursor.fetchall():
            result.append(dict(zip(schema, str)))
            print(result)


if __name__ == '__main__':

    _SQL = """SELECT idCustomer, Telephone
FROM customer
WHERE Telephone LIKE '%465%'
"""

    config = {
        'db': 'a',
        'schema': 'kek'
    }

    json.dump(config, open('config.json', 'w+'))
    restore_config = json.load(open('config.json', 'r'))
    print(restore_config)
