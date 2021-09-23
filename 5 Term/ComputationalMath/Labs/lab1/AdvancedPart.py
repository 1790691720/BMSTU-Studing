#  Copyright (c) 2021. Petrakov Stanislav
import numpy as np


def l_i(i, x, x_nodes):
    result = 1
    for j in range(len(x_nodes)):
        if i != j:
            result *= (x - x_nodes[j]) / (x_nodes[i] - x_nodes[j])

    return result


def L(x, x_nodes, y_nodes):
    result = 0

    for i in range(len(x_nodes)):
        result += y_nodes[i] * l_i(i, x, x_nodes)

    return result


def tolerance_Z(input_nodes):
    return input_nodes + np.random.normal(0, 0.01, len(input_nodes))


def confidence_spline(input_splines, percent):
    result = []
    h_u = []
    h_m = []
    h_l = []

    len_input = len(input_splines)

    h_l_position = int((len_input - (len_input * percent)) / 2) - 1
    h_u_position = len_input - h_l_position - 2

    input_splines = np.sort(input_splines, axis=0)
    
    h_u = input_splines[h_u_position]
    h_l = input_splines[h_l_position]
    h_m = np.mean(input_splines, axis=0)
    return np.array((h_u, h_m, h_l))
