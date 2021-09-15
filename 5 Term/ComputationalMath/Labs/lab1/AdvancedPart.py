#  Copyright (c) 2021. Petrakov Stanislav

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
