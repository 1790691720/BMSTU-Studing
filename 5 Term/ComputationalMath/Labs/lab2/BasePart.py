import numpy as np
import scipy
from scipy.misc import derivative
from scipy.optimize import fsolve


def compositeSimpson(a: float, b: float, n: int, func) -> float:
    if n % 2 != 0:
        n = n + 1

    x = np.linspace(a, b, n + 1)
    h: float = abs(a - b) / 2

    result: float = func(x[0])
    for xIn in x[2:-1:2]:
        result = result + 2 * func(xIn)
    for xIn in x[1::2]:
        result = result + 4 * func(xIn)
    result = result + func(x[-1])
    result = result * h / 3.
    return result


def compositeTrapezoid(a: float, b: float, n: int, func) -> float:
    if n % 2 != 0:
        n = n + 1

    x = np.linspace(a, b, n + 1)
    h: float = abs(a - b) / 2

    result: float = func(x[0])
    for xIn in x[1:-1:1]:
        result = result + 2 * func(xIn)
    result = result + func(x[-1])
    result = result * h / 2.

    return result


def yFromX(x: float) -> float:
    def xFromTForRoot(t: float, x: float) -> float:
        C: float = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C: float = 1.03439984
    t = scipy.optimize.fsolve(func=xFromTForRoot, x0=0, args=x)
    return C * (0.5 - 0.5 * np.cos(2 * t))


def FunctionalSciPy(x: float) -> float:
    g: float = 9.80665
    return np.sqrt((1 + derivative(func=yFromX, x0=x, n=1, dx=0.0000001) ** 2) / (2 * g * yFromX(x)))


def yFromX(x: float) -> float:
    def xFromTForRoot(t: float, x: float) -> float:
        C: float = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C: float = 1.03439984
    t = scipy.optimize.fsolve(func=xFromTForRoot, x0=0, args=x)
    return C * (0.5 - 0.5 * np.cos(2 * t))


def deritativeParametr(x: float) -> float:
    def xFromTForRoot(t: float, x: float) -> float:
        C: float = 1.03439984
        return C * (t - 0.5 * np.sin(2 * t)) - x

    C: float = 1.03439984
    t: float = scipy.optimize.fsolve(func=xFromTForRoot, x0=0, args=x)

    xt: float = - C * np.cos(2 * t)
    yt: float = - C * np.sin(2 * t)

    return yt / xt


def FunctionalParametr(x: float) -> float:
    g: float = 9.80665
    return np.sqrt((1 + deritativeParametr(x) ** 2) / (2 * g * yFromX(x)))
