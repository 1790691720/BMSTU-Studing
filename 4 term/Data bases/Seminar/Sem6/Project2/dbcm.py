from pymysql import connect
from pymysql.err import InterfaceError


class UseDataBase:
    def __init__(self, config):
        self.config = config

    def __enter__(self):
        try:
            self.conn = connect(**self.config)
            self.cursor = self.conn.cursor()
            return self.cursor
        except InterfaceError as err:
            return err

    def __exit__(self, exec_type, exec_value, exec_trace):
        self.conn.commit()
        self.cursor.close()
        self.conn.close()
