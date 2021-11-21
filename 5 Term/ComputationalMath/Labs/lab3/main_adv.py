import matplotlib.pyplot as plt
import numpy as np

from generators import generateNodes, generateW, generateI


def nextStep(vCur, uCur, step, node, I):
    v = vCur + step * (0.04 * vCur ** 2 + 5 * vCur + 140 - uCur + I)
    u = uCur + step * (node['a'] * (node['b'] * vCur - uCur))
    return v, u


if __name__ == '__main__':
    numberActive = 800
    numberPassive = 200
    numberAll = numberActive + numberPassive

    nodes = generateNodes(numberActive, numberPassive)
    # start conditions
    vCur = []
    uCur = []

    for i in range(numberAll):
        vCur.append(-65.)
        uCur.append(vCur[i] * nodes[i]['b'])

    W = generateW(numberActive, numberPassive)
    I = generateI(numberActive, numberPassive)
    tStart = 0
    tEnd = 1000
    h = 0.5
    resultX = []
    resultY = []
    # main cycle
    for tCur in np.arange(start=tStart, stop=tEnd, step=h):
        active = []
        for i in range(numberAll):

            if vCur[i] >= 30:
                vCur[i] = nodes[i]['c']
                uCur[i] = uCur[i] + nodes[i]['d']
                resultX.append(tCur)
                resultY.append(i)
                active.append(True)
            else:
                active.append(False)

        Icur = I + np.sum(W[:, active], axis=1)
        for i in range(numberAll):
            vCur[i], uCur[i] = nextStep(vCur[i], uCur[i], h, nodes[i], Icur[i])

    plt.figure(figsize=(14, 7))
    plt.grid()
    plt.xlabel('t')
    plt.ylabel('n', rotation=0)
    plt.scatter(resultX, resultY, marker='.')
    plt.savefig('.\Plots\GraphNeural.svg', format='svg')
    plt.show()
