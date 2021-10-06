import json

from dbcm import UserDatabase


def work_with_db(dbconfig, _SQL, addtion):
    with UserDatabase(dbconfig) as cursor:
        if cursor is None:
            raise ValueError('Cursor is None')
        elif cursor:
            cursor.execute(_SQL, addtion)
            resulting = []
            q = []
            for i in cursor.description:
                q.append(i[0])
            resulting.append(q)
            for row in cursor.fetchall():
                resulting.append(row)
            return resulting


if __name__ == '__main__':
    configDataBase = json.load(open('configDataBase.json', 'r'))

    AverageTime = int(input("Enter average time test: "))

    _SQL_1_ = """SELECT * 
FROM test_list
WHERE AverageTime > (%s)"""
    _SQL_1_Additions = (AverageTime)

    result = work_with_db(configDataBase, _SQL_1_, _SQL_1_Additions)
    print(result)
