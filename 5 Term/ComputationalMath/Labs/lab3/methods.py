from scipy.optimize import fsolve


def EulerMethod(tStart, tMax, f, h, mode, I):
    m = int((tMax - tStart) / h)

    v = [mode['c']]
    u = [mode['b'] * v[0]]

    for i in range(m):
        v.append(v[i] + h * f[0](v[i], u[i], I))
        u.append(u[i] + h * f[1](v[i], u[i], mode))

        if v[i + 1] >= 30:
            v[i + 1] = mode['c']
            u[i + 1] += mode['d']

    return [v, u]


def ImplicitEulerMethod(tStart, tMax, f, h, mode, I):
    m = int((tMax - tStart) / h)

    def fsolveForV(v2, vi, ui, f, h, I):
        return v2 - vi - h * f[0](vi, ui, I)

    def fsolveForU(u2, vi, ui, f, h, mode):
        return u2 - ui - h * f[1](vi, ui, mode)

    v = [mode['c']]
    u = [mode['b'] * v[0]]

    for i in range(m):
        v.append(fsolve(fsolveForV, v[i], args=(v[i], u[i], f, h, I))[0])
        u.append(fsolve(fsolveForU, u[i], args=(v[i], u[i], f, h, mode))[0])

        if v[i + 1] >= 30:
            v[i + 1] = mode['c']
            u[i + 1] += mode['d']

    return [v, u]


def RungeKuttaMethod(tStart, tMax, f, h, mode, I):
    m = int((tMax - tStart) / h)

    v = [mode['c']]
    u = [mode['b'] * v[0]]

    for i in range(m):
        k_v1 = h * f[0](v[i], u[i], I)
        k_u1 = h * f[1](v[i], u[i], mode)

        k_v2 = h * f[0](v[i] + (k_v1 / 2), u[i] + (h / 2), I)
        k_u2 = h * f[1](v[i] + (h / 2), u[i] + (k_u1 / 2), mode)

        k_v3 = h * f[0](v[i] + (k_v2 / 2), u[i] + (h / 2), I)
        k_u3 = h * f[1](v[i] + (h / 2), u[i] + (k_u2 / 2), mode)

        k_v4 = h * f[0](v[i] + k_v3, u[i] + h, I)
        k_u4 = h * f[1](v[i] + h, u[i] + k_u3, mode)

        v.append(v[i] + (1 / 6) * (k_v1 + 2 * k_v2 + 2 * k_v3 + k_v4))
        u.append(u[i] + (1 / 6) * (k_u1 + 2 * k_u2 + 2 * k_u3 + k_u4))

        if v[i + 1] >= 30:
            v[i + 1] = mode['c']
            u[i + 1] += mode['d']

    return [v, u]
