from sql.SQLconnect import SQLconnect
from sql.SQLprovider import SQLProvider


class SQLmaster:
    def __init__(self, dbconfig):
        self.db_connect = SQLconnect(dbconfig)
        self.db_request = SQLProvider(r'.\sql\requests') # Сюда путь до папки с запросами

    def request(self, filename, **kwargs) -> dict:
        cursor = self.db_connect.cursor
        request = self.db_request.get(filename, **kwargs)
        if cursor is None:
            raise ValueError('Cursor is None')
        elif cursor:
            cursor.execute(request)
            resulting = []
            q = []
            for i in cursor.description:
                q.append(i[0])
            resulting.append(q)
            for row in cursor.fetchall():
                resulting.append(row)
            return resulting
