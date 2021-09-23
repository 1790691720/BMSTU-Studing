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
# TODO: change 100 to 1000
x = np.linspace(left_border, right_border, 1000)

S_x = [BasePart.сubic_spline(x_i, cubicCoeffs, x_nodes) for x_i in x]

number_of_splines = 1000
x_tolerance = []
for k in range(0, number_of_splines):
    x_tolerance.append(AdvancedPart.tolerance_Z(x_nodes))

y_tolerance = []
for k in range(0, number_of_splines):
    y_tolerance.append(AdvancedPart.tolerance_Z(x_nodes))
# Lagrange X
lagrange_x_tolerance = []
for i in x_tolerance:
    lagrange_x_tolerance.append(AdvancedPart.L(x, i, y_nodes))
lagrange_x_tolerance = AdvancedPart.confidence_spline(lagrange_x_tolerance, 0.9)

'''
Draw Graphs
'''

fig, axes = plt.subplots(nrows=2, ncols=1, figsize=(20, 50), dpi=150)

# Base part graph
axes[0].set_xticks(np.arange(0, 1.1, 0.1))
axes[0].set_yticks(np.arange(3, 4.1, 0.1))
axes[0].plot(x_nodes, y_nodes, color="blue", linewidth=1.5, linestyle="-", label="f(x)")  # Source data
axes[0].plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
axes[0].legend(loc='best')
axes[0].grid()

axes[0].plot(x, S_x, color="purple", linewidth=1.5, linestyle="-", label="S(x)")

# Advanced part graph

# X tolerance polynomial
axes[1].plot(x_nodes, y_nodes, color="blue", linewidth=1.5, linestyle="-", label="f(x)")  # Source data
axes[1].plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
axes[0].legend(loc='best')
axes[0].grid()

axes[1].plot(x, lagrange_x_tolerance[0], color="red", linewidth=1.5, linestyle="-", label="h_u")
axes[1].plot(x, lagrange_x_tolerance[2], color="orange", linewidth=1.5, linestyle="-", label="h_l")
axes[1].plot(x, lagrange_x_tolerance[1], color="violet", linewidth=1.5, linestyle="--", label="h_m")
axes[1].fill_between(x, lagrange_x_tolerance[0], lagrange_x_tolerance[2],alpha=0.1, color="blue")
# y tolerance polynomial


# X tolerance cubic


# y tolerance cubic

# Draw all plots
plt.show()
