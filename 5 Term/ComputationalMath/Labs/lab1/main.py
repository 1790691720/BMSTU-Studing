#  Copyright (c) 2021. Petrakov Stanislav

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

import BasePart as BasePart
import AdvancedPart as AdvancedPart

# region Source Data
x_nodes = np.array([0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.])
y_nodes = np.array([3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02])

left_border = 0
right_border = 1
# endregion

# region Calc for graphs
# TODO: change 100 to 1000
x = np.linspace(left_border, right_border, 1000)
cubicCoeffs = BasePart.сubic_spline_coeff(x_nodes, y_nodes)
S_x = [BasePart.сubic_spline(x_i, cubicCoeffs, x_nodes) for x_i in x]

number_of_splines = 1000
x_tolerance = []
for k in range(0, number_of_splines):
    x_tolerance.append(AdvancedPart.tolerance_Z(x_nodes))

y_tolerance = []
for k in range(0, number_of_splines):
    y_tolerance.append(AdvancedPart.tolerance_Z(y_nodes))

# Lagrange X tolerance
lagrange_x_tolerance = []
for i in x_tolerance:
    lagrange_x_tolerance.append(AdvancedPart.L(x, i, y_nodes))
lagrange_x_tolerance = AdvancedPart.confidence_spline(lagrange_x_tolerance, 0.9)

# Lagrange Y tolerance
lagrange_y_tolerance = []
for i in y_tolerance:
    lagrange_y_tolerance.append(AdvancedPart.L(x, x_nodes, i))
lagrange_y_tolerance = AdvancedPart.confidence_spline(lagrange_y_tolerance, 0.9)
# Cubic spline X tolerance

cubic_x_tolerance = []
for i in x_tolerance:
    tempCoeffs = BasePart.сubic_spline_coeff(i, y_nodes)
    tempCubic = [BasePart.сubic_spline(x_i, cubicCoeffs, i) for x_i in x]
    cubic_x_tolerance.append(tempCubic)
cubic_x_tolerance = AdvancedPart.confidence_spline(cubic_x_tolerance, 0.9)

# Cubic spline Y tolerance
cubic_y_tolerance = []
for i in x_tolerance:
    tempCoeffs = BasePart.сubic_spline_coeff(x_nodes, i)
    tempCubic = [BasePart.сubic_spline(x_i, cubicCoeffs, i) for x_i in x]
    cubic_y_tolerance.append(tempCubic)
cubic_y_tolerance = AdvancedPart.confidence_spline(cubic_y_tolerance, 0.9)
# endregion

'''
Draw Graphs
'''

# region Base part graph
plt.figure(num=1, dpi=300)
plt.plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
plt.plot(x, S_x, color="purple", linewidth=1.5, linestyle="-", label="S(x)")
plt.legend(loc='best')
plt.grid()
plt.savefig(fname="Base Graph", dpi=300)
plt.show()
# endregion

'''
Advanced part graph
'''

# region X tolerance polynomial
plt.figure(num=2, dpi=300)
plt.plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
plt.plot(x, lagrange_x_tolerance[0], color="red", linewidth=1.5, linestyle="-", label="h_u")
plt.plot(x, lagrange_x_tolerance[2], color="orange", linewidth=1.5, linestyle="-", label="h_l")
plt.plot(x, lagrange_x_tolerance[1], color="violet", linewidth=1.5, linestyle="--", label="h_m")
plt.fill_between(x, lagrange_x_tolerance[0], lagrange_x_tolerance[2], alpha=0.1, color="blue")
plt.legend(loc='lower center')
plt.grid()
plt.savefig(fname="X tolerance polynomial", dpi=300)
plt.show()
# endregion

# region Y tolerance polynomial
plt.figure(num=3, dpi=300)
plt.plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
plt.plot(x, lagrange_y_tolerance[0], color="red", linewidth=1.5, linestyle="-", label="h_u")
plt.plot(x, lagrange_y_tolerance[2], color="orange", linewidth=1.5, linestyle="-", label="h_l")
plt.plot(x, lagrange_y_tolerance[1], color="violet", linewidth=1.5, linestyle="--", label="h_m")
plt.fill_between(x, lagrange_y_tolerance[0], lagrange_y_tolerance[2], alpha=0.1, color="blue")
plt.legend(loc='upper center')
plt.grid()
plt.savefig(fname="Y tolerance polynomial", dpi=300)
plt.show()
# endregion

# region X tolerance cubic
plt.figure(num=4, dpi=300)
plt.plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
plt.plot(x, cubic_x_tolerance[0], color="red", linewidth=1.5, linestyle="-", label="h_u")
plt.plot(x, cubic_x_tolerance[2], color="orange", linewidth=1.5, linestyle="-", label="h_l")
plt.plot(x, cubic_x_tolerance[1], color="violet", linewidth=1.5, linestyle="--", label="h_m")
plt.fill_between(x, cubic_x_tolerance[0], cubic_x_tolerance[2], alpha=0.1, color="blue")
plt.legend(loc='upper center')
plt.grid()
plt.savefig(fname="X tolerance cubic", dpi=300)
plt.show()
# endregion

# region Y tolerance cubic
plt.figure(num=5, dpi=300)
plt.plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
plt.plot(x, cubic_y_tolerance[0], color="red", linewidth=1.5, linestyle="-", label="h_u")
plt.plot(x, cubic_y_tolerance[2], color="orange", linewidth=1.5, linestyle="-", label="h_l")
plt.plot(x, cubic_y_tolerance[1], color="violet", linewidth=1.5, linestyle="--", label="h_m")
plt.fill_between(x, cubic_y_tolerance[0], cubic_y_tolerance[2], alpha=0.1, color="blue")
plt.legend(loc='upper center')
plt.grid()
plt.savefig(fname="Y tolerance cubic", dpi=300)
plt.show()
# endregion
