import matplotlib.pyplot as plt

import BasePart


def DrawSourceDataAndConfigPlot(xNodes, yNodes):
    plt.figure(dpi=300)
    plt.scatter(xNodes, yNodes, marker='o', color="blue", label="Source data", zorder=1)  # Source data
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('y', rotation=0)
    return None


if __name__ == '__main__':
    BasePart.compositeSimpson(a=0.001, b=2, n=100, func=BasePart.Functional)


