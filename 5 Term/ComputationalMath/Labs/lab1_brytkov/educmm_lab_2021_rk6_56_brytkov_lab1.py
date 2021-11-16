import numpy as np
import matplotlib.pyplot as plt


def qubic_spline_coeff(x_nodes, y_nodes):
    """ Функция, которая посредством решения матричного уравнения вычисляет коэффициенты естественного кубического
    сплайна. """

    h = x_nodes[1:] - x_nodes[:-1]  # от h_1 до h_n-1
    left_diag = np.concatenate((h[:-1], [0]))  # левая диагональ
    general_diag = np.concatenate(([1], (h[1:] + h[:-1]) * 2, [1]))  # главная
    right_diag = np.concatenate(([0], h[1:]))  # правая диагональ

    a = y_nodes  # список коэффициентов а

    matrix_A = np.diag(left_diag, -1) + np.diag(general_diag) + np.diag(right_diag, 1)  # трёхдиагональная матрица А
    matrix_B = np.concatenate(([0], 3 * \
                               (np.divide(np.subtract(a[2:], a[1:-1]), h[1:]) -
                                np.divide(np.subtract(a[1:-1], a[:-2]), h[:-1])), [0]))  # матрица В
    matrix_A_inv = np.linalg.inv(matrix_A)  # обратная матрица А

    c = np.array(matrix_A_inv.dot(matrix_B))  # список коэффициентов с
    b = np.subtract(np.divide(np.subtract(a[1:], a[:-1]), h), (c[1:] + 2 * c[:-1]) * h / 3)  # список коеффицинтов b
    d = np.array((c[1:] - c[:-1]) / h / 3)  # список коэффициентов d
    matrix = []  # матрица коэффициентов [ [b_1, c_1, d_1], ..., [b_n-1, c_n-1, d_n-1]

    n = len(x_nodes)
    for i in range(n - 1):
        matrix.append([b[i], c[i], d[i]])
    return matrix


def implicate_index(x, x_nodes):
    """ Функция, которая возвращает значение кубического сплайна в точке x (qs_coeff обозначает матрицу
    коэффициентов). """
    n = len(x_nodes)
    for i in range(n - 1):
        if x_nodes[i] <= x <= x_nodes[i + 1]:
            index = i
            break
    if x > x_nodes[n - 1]:
        index = n - 2
    if x < x_nodes[0]:
        index = 0
    return index


def qubic_spline(x, qs_coeff, x_nodes, y_nodes):
    """ Функция, которая возвращает значение кубического сплайна в точке x (qs_coeff обозначает матрицу
    коэффициентов). """

    i = implicate_index(x, x_nodes)
    a = y_nodes[i]
    b = qs_coeff[i][0]
    c = qs_coeff[i][1]
    d = qs_coeff[i][2]
    cub = a + b * (x - x_nodes[i]) + c * (x - x_nodes[i]) ** 2 + d * (x - x_nodes[i]) ** 3
    return cub


def d_qubic_spline(x, qs_coeff, x_nodes, y_nodes):
    """ Функция, которая возвращает значение кубического сплайна в точке x (qs_coeff обозначает матрицу
    коэффициентов). """
    i = implicate_index(x, x_nodes)
    b = qs_coeff[i][0]
    c = qs_coeff[i][1]
    d = qs_coeff[i][2]
    d_cub = b + 2 * c * (x - x_nodes[i]) + 3 * d * (x - x_nodes[i]) ** 2
    return d_cub


if __name__ == '__main__':
    x_points = np.array([0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1])
    y_points = np.array([3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02])
    xlabels = 'x'
    ylabels = 'h'

    qs_coeff = qubic_spline_coeff(x_points, y_points)
    left_board = 0
    right_board = 1
    x = np.linspace(left_board, right_board, 1000)
    S_x = [qubic_spline(x_i, qs_coeff, x_points, y_points) for x_i in x]
    d_S_x = [d_qubic_spline(x_i, qs_coeff, x_points, y_points) for x_i in x]

    plt.plot(x, S_x, color="purple", linewidth=1.5, linestyle="-", label="S(x)")
    plt.plot(x_points, y_points, 'o', color="blue")
    plt.xlabel(xlabels)
    plt.ylabel(ylabels)
    plt.legend(loc='upper left')
    plt.grid()
    plt.savefig(fname="QubicSpline.svg", format='svg', dpi=300)
    plt.show()

    plt.plot(x, d_S_x, color="purple", linewidth=1.5, linestyle="-", label="S'(x)")
    plt.plot(x_points, y_points, 'o', color="blue")
    plt.xlabel(xlabels)
    plt.ylabel(ylabels)
    plt.legend(loc='upper left')
    plt.grid()
    plt.savefig(fname="DQubicSpline.svg", format='svg', dpi=300)
    plt.show()