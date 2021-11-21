import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import fsolve

I = 5


def euler(x_0, t_n, f, h, a, b, c, d):
    m = int((t_n - x_0) / h)

    v = [c]
    u = [b * v[0]]

    for i in range(m):
        v.append(v[i] + h * f[0](v[i], u[i], I))
        u.append(u[i] + h * f[1](v[i], u[i], a, b, c, d))

        if v[i + 1] >= 30:
            v[i + 1] = c
            u[i + 1] += d

    return [v, u]


def implicit_euler(x_0, t_n, f, h, a, b, c, d):
    m = int((t_n - x_0) / h)

    def equation_v(v2, vi, ui, f, h, I):
        return v2 - vi - h * f[0](vi, ui, I)

    def equation_u(u2, vi, ui, f, h, a, b, c, d):
        return u2 - ui - h * f[1](vi, ui, a, b, c, d)

    v = [c]
    u = [b * v[0]]

    for i in range(m):
        v.append(fsolve(equation_v, v[i], args=(v[i], u[i], f, h, I))[0])
        u.append(fsolve(equation_u, u[i], args=(v[i], u[i], f, h, a, b, c, d))[0])

        if v[i + 1] >= 30:
            v[i + 1] = c
            u[i + 1] += d

    return [v, u]


def runge_kutta(x_0, t_n, f, h, a, b, c, d):
    m = int((t_n - x_0) / h)

    v = [c]
    u = [b * v[0]]

    for i in range(m):
        k_v1 = h * f[0](v[i], u[i], I)
        k_u1 = h * f[1](v[i], u[i], a, b, c, d)

        k_v2 = h * f[0](v[i] + (k_v1 / 2), u[i] + (h / 2), I)
        k_u2 = h * f[1](v[i] + (h / 2), u[i] + (k_u1 / 2), a, b, c, d)

        k_v3 = h * f[0](v[i] + (k_v2 / 2), u[i] + (h / 2), I)
        k_u3 = h * f[1](v[i] + (h / 2), u[i] + (k_u2 / 2), a, b, c, d)

        k_v4 = h * f[0](v[i] + k_v3, u[i] + h, I)
        k_u4 = h * f[1](v[i] + h, u[i] + k_u3, a, b, c, d)

        v.append(v[i] + (1 / 6) * (k_v1 + 2 * k_v2 + 2 * k_v3 + k_v4))
        u.append(u[i] + (1 / 6) * (k_u1 + 2 * k_u2 + 2 * k_u3 + k_u4))

        if v[i + 1] >= 30:
            v[i + 1] = c
            u[i + 1] += d

    return [v, u]


def f_1(v, u, I):
    return 0.04 * v * v + 5 * v + 140 - u + I


def f_2(v, u, a, b, c, d):
    return a * (b * v - u)


if __name__ == '__main__':
    h = 0.5
    x_0 = 0
    t_n = 100

    modes = [
        [0.02,
         0.2,
         -65,
         6
         ],
        [
            0.02,
            0.25,
            -65,
            6
        ],
        [
            0.02,
            0.2,
            -50,
            2
        ],
        [
            0.1,
            0.2,
            -65,
            2
        ]
    ]

    modeNames = [
        "TS",
        "PS",
        "Ch",
        "FS"
    ]

    f = [f_1, f_2]
    t = np.linspace(x_0, t_n, int((t_n - x_0) / h) + 1)

    for i in range(4):
        v_1 = euler(x_0, t_n, f, h, modes[i][0], modes[i][1], modes[i][2], modes[i][3])[0]
        v_2 = implicit_euler(x_0, t_n, f, h, modes[i][0], modes[i][1], modes[i][2], modes[i][3])[0]
        v_3 = runge_kutta(x_0, t_n, f, h, modes[i][0], modes[i][1], modes[i][2], modes[i][3])[0]

        plt.xlabel('t')
        plt.ylabel('v')
        plt.grid()

        plt.plot(t, v_1, linewidth=2, label="Метод эйлера", linestyle="-", color="green")

        plt.plot(t, v_2, linewidth=1.0, label="Неявный метод Эйлера", linestyle="--", color="magenta")

        plt.plot(t, v_3, linewidth=1.0, label="Метод Рунге-Кутта", linestyle="-", color="red")
        plt.legend(loc='best')
        plt.savefig(f'.\Mode{modeNames[i]}.svg')
        plt.show()
