import matplotlib.pyplot as plt
import numpy as np
import scipy
from scipy.optimize import fsolve


def composite_simpson(a, b, n, func):
    if n % 2 != 0:
        n = n + 1

    x = np.linspace(a, b, n + 1)
    h = (b - a) / 2

    result = func(x[0])

    for x_cur in x[2:-1:2]:
        result = result + 2 * func(x_cur)
    for x_cur in x[1::2]:
        result = result + 4 * func(x_cur)

    result = result + func(x[-1])
    result = result * h / 3.
    return result


def composite_trapezoid(a, b, n, func):
    if n % 2 != 0:
        n = n + 1

    x = np.linspace(a, b, n + 1)
    h = h = (b - a) / 2

    result = func(x[0])
    for x_cur in x[1:-1:1]:
        result = result + 2 * func(x_cur)
    result = result + func(x[-1])
    result = result * h / 2.

    return result


def error_simpson(a, b, h):
    error = []
    for i in range(len(h)):
        error.append((b - a) * (h[i] ** 4) / 180)
    return error


def error_trapezoid(a, b, h):
    error = []
    for i in range(len(h)):
        error.append((b - a) * (h[i] ** 2) / 12)
    return error


def deritative(x):
    def x_t_root(t, x):
        C = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C = 1.03439984
    t = scipy.optimize.fsolve(func=x_t_root, x0=0, args=x)

    xt = C * (1 - np.cos(2 * t))
    yt = C * np.sin(2 * t)

    return yt / xt


def y_x(x):
    def x_t_root(t, x):
        C = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C = 1.03439984
    t = scipy.optimize.fsolve(func=x_t_root, x0=0, args=x)
    return C * (0.5 - 0.5 * np.cos(2 * t))


def functional(x):
    g = 9.80665
    return np.sqrt((1 + deritative(x) ** 2) / (2 * g * y_x(x)))


if __name__ == '__main__':

    a = 0.001
    b = 2

    h = []
    for i in range(3, 10000):
        h.append((b - a) / i)

    plt.figure(dpi=300)
    plt.grid()
    plt.xlabel('h')
    plt.ylabel('E', rotation=0)
    h_scaling = np.linspace(0.01, 2, 100)
    plt.loglog(h_scaling, h_scaling ** 2, linewidth=3, label=r'$O(h^2)$', color='red')
    plt.loglog(h_scaling, h_scaling ** 4, '-k', linewidth=3, label=r'$O(h^4)$')
    plt.loglog(h, error_simpson(a, b, h), '.', label='composite Simpson')
    plt.loglog(h, error_trapezoid(a, b, h), '.', label='composite Trapezoid')
    plt.legend()
    plt.savefig('.\error.svg')

    plt.show()
