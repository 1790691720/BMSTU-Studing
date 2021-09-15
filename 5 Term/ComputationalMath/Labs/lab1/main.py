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

сubicCoeff = BasePart.сubic_spline_coeff(x_nodes, y_nodes)
x = np.linspace(left_border, right_border, 1000)
S_x=[BasePart.сubic_spline(x, сubicCoeff) for x_i in x]

'''
Рассчёт данных
'''
qs_coeff = сubic_spline_coeff(x_nodes, y_nodes)
x = np.linspace(left_board, right_board, 100)
S_x = [qubic_spline(x_i, qs_coeff, years, gdp_rus) for x_i in x]

'''
Вывод данных
'''
fig, axes = plt.subplots(nrows=1, ncols=1, figsize=(20, 20), dpi=100)
axes.plot(x, S_x, color="purple", linewidth=1.5, linestyle="-", label="S(x)")
axes.plot(x_nodes, y_nodes, 'o', color="red")
axes.set_xlabel(xlabels[0])
axes.set_ylabel(ylabels[0])
axes.legend(loc='upper left')
axes.grid()
fig.tight_layout()
plt.show()
fig.savefig("сubic_spline_graphics.png")
