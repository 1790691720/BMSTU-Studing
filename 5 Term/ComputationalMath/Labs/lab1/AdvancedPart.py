import numpy as np


def GenerateSetOfErroneousData(inputData, amount, mu, sigma):
    result = []
    for i in range(amount):
        result.append(inputData + np.random.normal(mu, sigma, len(inputData)))
    return result


def BasicLagrangePolynomial(i, x, xNodes):
    result = 1.

    for j in range(len(xNodes)):
        if i != j:
            result *= (x - xNodes[j]) / (xNodes[i] - xNodes[j])

    return result


def LagrangePolynomial(x, xNodes, yNodes):
    result = 0

    for i in range(len(xNodes)):
        result += yNodes[i] * BasicLagrangePolynomial(i, x, xNodes)

    return result


def DeterminationOfConfidenceCurves(inputSplines, percent):
    lenInput = len(inputSplines)

    h_lPosition = int((lenInput - (lenInput * percent)) / 2) - 1
    h_uPosition = lenInput - h_lPosition - 2

    inputSplines = np.sort(inputSplines, axis=0)

    h_u = inputSplines[h_uPosition]
    h_l = inputSplines[h_lPosition]
    h_m = np.mean(inputSplines, axis=0)
    return np.array((h_u, h_m, h_l))
