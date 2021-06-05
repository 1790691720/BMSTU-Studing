from database import UserDatabase
from pymysql.err import ProgrammingError
from pymysql.err import OperationalError


# серым подсвечивается то, что не используется
# хинты - подсказывают, что предствляет собой список


def work_with_db(dbconfig, _SQL, schema, _SQL2):
    with UserDatabase(dbconfig) as cursor:
        if cursor is None:
            raise ValueError('Cursor cannot be created')
        elif cursor:
            cursor.execute(_SQL)
            result = []
            for str in cursor.fetchall():
                result.append(dict(zip(schema, str)))
            print(result)
            # cursor.execute(_SQL2)


if __name__ == '__main__':
    dbconfig = {'host': 'localhost', 'port': 3306, 'user': 'root', 'password':"", 'db': 'Lab1'}
    _SQL = """ SELECT Name,Author FROM Book"""
    _SQL2 = """UPDATE Book SET Price = 15 WHERE Name = 'JoJo'"""
    schema = ['Name', 'Author']
    work_with_db(dbconfig, _SQL, schema, _SQL2)


