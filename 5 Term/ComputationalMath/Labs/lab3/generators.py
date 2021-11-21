import numpy as np


def generateNodes(numberActive, numberPassive):
    nodes = []

    a = 0.02
    b = 0.2
    c = -65. + 15. * (np.random.uniform(size=numberActive) ** 2.)
    d = 8. - 6. * (np.random.uniform(size=numberActive) ** 2.)
    for i in range(numberActive):
        nodes.append({
            'a': a,
            'b': b,
            'c': c[i],
            'd': d[i]
        }
        )

    a = 0.02 + 0.08 * np.random.uniform(size=numberPassive)
    b = 0.25 - 0.05 * np.random.uniform(size=numberPassive)
    c = -65.
    d = 2.

    for i in range(numberPassive):
        nodes.append({
            'a': a[i],
            'b': b[i],
            'c': c,
            'd': d
        })
    return nodes


def generateW(numberActive, numberPassive):
    activeNeurons = 0.5 * np.random.uniform(size=(numberActive + numberPassive, numberActive))
    passiveNeurons = -np.random.uniform(size=(numberActive + numberPassive, numberPassive))
    result = np.hstack((activeNeurons, passiveNeurons))

    return result


def generateI(numberActive, numberPassive):
    result = np.concatenate((5. * np.random.uniform(size=numberActive), 2. * np.random.uniform(size=numberPassive)),
                            axis=None)
    return result
