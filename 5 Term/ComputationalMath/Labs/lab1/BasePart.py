import numpy as np


def CubicSplineCoefficients(xNodes, yNodes):
    a = yNodes  # coef a

    h = xNodes[1:len(xNodes)] - xNodes[0:len(xNodes) - 1]  # store from h_1 to h_n-1

    upperDiagonal = np.concatenate(([0], h[1:]))
    bottomDiagonal = np.concatenate((h[:-1], [0]))
    mainDiagonal = np.concatenate(([1], (h[1:] + h[0:-1]) * 2, [1]))

    matrixA = np.diag(bottomDiagonal, -1) + np.diag(mainDiagonal) + np.diag(upperDiagonal, 1)

    matrixB = np.concatenate(([0], 3 * np.subtract(np.divide(np.subtract(a[2:], a[1:-1]), h[1:]),
                                                   np.divide(np.subtract(a[1:-1], a[:-2]), h[:-1])), [0]))

    c = np.linalg.inv(matrixA).dot(matrixB)  # coef c
    d = np.divide(np.subtract(c[1:], c[:-1]), 3 * h)  # coef d
    b = np.subtract(np.divide(np.subtract(a[1:], a[:-1]), h), np.multiply(c[1:] + 2 * c[:-1], h) / 3)  # coef b

    resultMatrix = []
    for i in range(len(xNodes) - 1):
        resultMatrix.append([a[i], b[i], c[i], d[i]])

    return resultMatrix


def IndexForCubicSpline(x, xNodes):
    n = len(xNodes)

    for i in range(n - 1):
        if xNodes[i] <= x <= xNodes[i + 1]:
            return i

    if xNodes[n - 1] < x:
        return n - 2
    if xNodes[0] > x:
        return 0


def CubicSpline(x, xNodes, yNodes):
    cubicSplineCoefficients = CubicSplineCoefficients(xNodes, yNodes)
    result = np.zeros(shape=(len(x)))

    for i in range(len(x)):
        index = IndexForCubicSpline(x[i], xNodes)
        a = cubicSplineCoefficients[index][0]
        b = cubicSplineCoefficients[index][1]
        c = cubicSplineCoefficients[index][2]
        d = cubicSplineCoefficients[index][3]
        xi = xNodes[index]
        result[i] = a + b * (x[i] - xi) + c * ((x[i] - xi) ** 2) + d * ((x[i] - xi) ** 3)

    return result


def DCubicSpline(x, xNodes, yNodes):
    cubicSplineCoefficients = CubicSplineCoefficients(xNodes, yNodes)
    result = np.zeros(shape=(len(x)))

    for i in range(len(x)):
        index = IndexForCubicSpline(x[i], xNodes)
        b = cubicSplineCoefficients[index][1]
        c = cubicSplineCoefficients[index][2]
        d = cubicSplineCoefficients[index][3]
        xi = xNodes[index]
        result[i] = b + 2 * c * (x[i] - xi) + 3 * d * (x[i] - xi) ** 2
    return result
