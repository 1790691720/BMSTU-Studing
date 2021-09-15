#  Copyright (c) 2021. Petrakov Stanislav

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

import BasePart as BasePart

'''
Start data
'''

x_nodes = np.array([0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1])
y_nodes = np.array([3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02])

left_border = 0
right_border = 1

'''
Calc for graphs

'''
cubicCoeffs = BasePart.сubic_spline_coeff(x_nodes, y_nodes)
x = np.linspace(left_border, right_border, 1000)

S_x = [BasePart.сubic_spline(x_i, cubicCoeffs, x_nodes) for x_i in x]

'''
Output Graphs
'''

fig, axes = plt.subplots(nrows=2, ncols=1, figsize=(10, 20), dpi=300)
axes[0].set_xticks(np.arange(0, 1.1, 0.1))
axes[0].set_yticks(np.arange(3, 4.1, 0.1))
axes[0].plot(x_nodes, y_nodes, color="blue", linewidth=1.5, linestyle="-", label="f(x)")  # Source data
axes[0].plot(x_nodes, y_nodes, 'o', color="blue", linewidth=1.5)  # Source data
axes[0].plot(x,S_x,color="purple", linewidth=1.5, linestyle="-", label="S(x)")
axes[0].legend(loc='upper right')
axes[0].grid()
plt.show()
