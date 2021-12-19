import statistics as st

import matplotlib.pyplot as plt
import numpy as np


def normalize(A):
    m = len(A)
    center_a = (np.eye(m) - 1. / m * np.ones((m, m))) @ A
    return center_a


def psa(A):
    self_numbers, self_vectors = np.linalg.eig(A.T @ A)


    for i in range(len(self_numbers)):
        self_numbers[i] = np.sqrt(1. / (len(A) - 1.)) * np.sqrt(self_numbers[i])

    return self_vectors.T, self_numbers


def read():
    with open('wdbc.data', 'r') as f:
        full_data = [[num for num in line.split(',')] for line in f]

    scatter = []
    for row in full_data:
        if row[1] == 'B':
            scatter.append((0, 1, 0))
        else:
            scatter.append((0.5, 0, 1))

    matrix = []
    for row in full_data:
        matrix.append([float(row[i]) for i in range(2, len(full_data[0]))])

    return matrix, scatter


if __name__ == '__main__':
    matrix, scatter = read()
    matrix = normalize(matrix)

    main_comp, std_deviation = psa(matrix)

    # draw standart deviation
    plt.figure(figsize=(14, 7))
    plt.plot(1. + np.arange(len(std_deviation)), std_deviation, 'o--')
    plt.xlabel(r'$i$')
    plt.ylabel(r'$\sqrt{\nu} \sigma_i$')
    plt.grid()
    plt.show()

    # draw data
    main_comp_2 = main_comp[:2]
    A = matrix @ main_comp_2.T
    principal_comps = main_comp_2 @ main_comp_2.T

    x_bar = [np.mean(A[:, 0]), np.mean(A[:, 1])]
    sigmas_bar = [st.stdev(A[:, 0]), st.stdev(A[:, 1])]
    A_bar = (A - x_bar) / sigmas_bar

    plt.figure(figsize=(14, 7))

    plt.scatter(A_bar[:, 0], A_bar[:, 1], c=scatter, s=3)
    plt.plot([0], [0], 'ro', markersize=5)

    max_val = np.max(np.abs(A_bar))
    for principal_comp in principal_comps:
        plt.plot([0, max_val * principal_comp[0]], [0, max_val * principal_comp[1]], linewidth=3)

    plt.xlabel(r'$x_1$')
    plt.ylabel(r'$x_2$')
    plt.grid()
    plt.show()
