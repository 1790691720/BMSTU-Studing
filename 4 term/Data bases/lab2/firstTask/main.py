from database import UserDatabase


# серым подсвечивается то, что не используется
# хинты - подсказывают, что предствляет собой список


def work_with_db(dbconfig, _SQL):
    with UserDatabase(dbconfig) as cursor:
        if cursor is None:
            raise ValueError('Cursor is None')
        elif cursor:
            cursor.execute(_SQL)
            resulting = []
            q = []
            for i in cursor.description:
                q.append(i[0])
            resulting.append(q)
            for row in cursor.fetchall():
                resulting.append(row)
            return resulting


if __name__ == '__main__':
    dbconfig = {'host': 'localhost', 'port': 3306, 'user': 'root', 'password': "09051945", 'db': 'lab_schema'}
    _SQL = """ SELECT * FROM customer"""
    result = work_with_db(dbconfig, _SQL)
    if result is not None:
        f = open("out.txt", 'w')
        for i in result:
            for j in i:
                f.write(str(j))
                f.write('\t')
            f.write('\n')
