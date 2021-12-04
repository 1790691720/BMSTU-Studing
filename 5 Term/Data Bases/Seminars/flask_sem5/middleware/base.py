class Middleware:

    def __call__(self, environ, start_response):
        raise NotImplementedError
