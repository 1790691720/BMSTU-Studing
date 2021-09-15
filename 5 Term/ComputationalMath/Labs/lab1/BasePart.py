#  Copyright (c) 2021. Petrakov Stanislav

import numpy as np


def сubic_spline_coeff(x_nodes, y_nodes):
    h = x_nodes[1:len(x_nodes)] - x_nodes[0:len(x_nodes) - 1]  # store from h_1 to h_n-1

    up_diag = np.concatenate(([0], h[1:]))
    down_diag = np.concatenate((h[:-1], [0]))
    general_diag = np.concatenate(([1], (h[1:] + h[0:-1]) * 2, [1]))

    a = y_nodes  # coef a

    matrix_A = np.diag(down_diag, -1) + np.diag(general_diag) + np.diag(up_diag, 1)
    matrix_B = np.concatenate(([0], 3 * np.subtract(np.divide(np.subtract(a[2:], a[1:-1]), h[1:]),
                                                    np.divide(np.subtract(a[1:-1], a[:-2]), h[:-1])), [0]))

    c = np.linalg.inv(matrix_A).dot(matrix_B)  # coef c
    d = np.divide(np.subtract(c[1:], c[:-1]), 3 * h)  # coef d
    b = np.subtract(np.divide(np.subtract(a[1:], a[:-1]), h), np.multiply(c[1:] + 2 * c[:-1], h) / 3)  # coef b

    result_matrix = []
    for i in range(len(x_nodes) - 1):
        result_matrix.append([a[i], b[i], c[i], d[i], x_nodes[i]])

    return result_matrix


def сubic_spline(x, qubicSplineCoeff):
    index = list.index(x)
    a = qubicSplineCoeff[index][0]
    b = qubicSplineCoeff[index][1]
    c = qubicSplineCoeff[index][2]
    d = qubicSplineCoeff[index][3]
    xi = qubicSplineCoeff[index][4]

    return a + b * (x - xi) + c * ((x - xi) ** 2) + d * ((x - xi) ** 3)


def d_сubic_spline(x, qs_coeff):
    index = list.index(x)
    a = qubicSplineCoeff[index][0]
    b = qubicSplineCoeff[index][1]
    c = qubicSplineCoeff[index][2]
    d = qubicSplineCoeff[index][3]
    xi = qubicSplineCoeff[index][4]

    return b + 2 * c * (x - xi) + 3 * d * (x - xi)**2

def index_for_qubicSpline(x):
    n = len(x_nodes)
    for i in range(n - 1):
        if (x >= x_nodes[i] and x <= x_nodes[i + 1]):
            index = i
            break
    if (x > x_nodes[n - 1]):
        index = n - 2
    if (x < x_nodes[0]):
        index = 0
    return index