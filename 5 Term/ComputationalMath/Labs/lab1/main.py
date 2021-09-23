#  Copyright (c) 2021. Petrakov Stanislav

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

import BasePart as BasePart
import AdvancedPart as AdvancedPart

'''
Start data
'''

x_nodes = np.array([0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.])
y_nodes = np.array([3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02])

left_border = 0
right_border = 1

'''
Calc for graphs

'''
cubicCoeffs = BasePart.сubic_spline_coeff(x_nodes, y_nodes)
x = np.linspace(left_border, right_border, 1000)

S_x = [BasePart.сubic_spline(x_i, cubicCoeffs, x_nodes) for x_i in x]


x_tolerance = []
for k in range(0, 1000):
    x_tolerance.append(AdvancedPart.tolerance_Z(x_nodes))

y_tolerance = []
for k in range(0, 1000):
    y_tolerance.append(AdvancedPart.tolerance_Z(x_nodes))


'''
Draw Graphs
'''

fig, axes = plt.subplots(nrows=5, ncols=1, figsize=(20, 50), dpi=150)

# Draw source graph for all plots and set grid,legend
for i in range(5):
    axes[i].set_xticks(np.arange(0, 1.1, 0.1))
    axes[i].set_yticks(np.arange(3, 4.1, 0.1))
    axes[i].plot(x_nodes, y_nodes, color="blue", linewidth=1.5, linestyle="-", label="f(x)")  # Source data
    axes[i].plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
    axes[i].legend(loc='upper right')
    axes[i].grid()

# Base part graph

axes[0].plot(x, S_x, color="purple", linewidth=1.5, linestyle="-", label="S(x)")

# Advanced part graph

# X tolerance polynomial
axes[1].plot(x, AdvancedPart.Newton_poly(x, x_nodes, y_nodes), color="purple", linewidth=1.5, linestyle="-", label="S(x)")

# y tolerance polynomial

axes[2].plot(x, AdvancedPart.L(x, x_nodes, y_nodes), color="purple", linewidth=1.5, linestyle="-", label="S(x)")
# X tolerance cubic


# y tolerance cubic

# Draw all plots
plt.show()
