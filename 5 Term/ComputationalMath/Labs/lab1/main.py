import matplotlib.pyplot as plt
import numpy as np

import AdvancedPart as Advanced
import BasePart as Base


def DrawSourceDataAndConfigPlot(xNodes, yNodes):
    plt.figure(dpi=300)
    plt.scatter(xNodes, yNodes, marker='o', color="blue", label="Source data", zorder=1)  # Source data
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('y', rotation=0)
    return None


# region Source Data
xNodes = np.array([0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.])
yNodes = np.array([3.37, 3.95, 3.73, 3.59, 3.15, 3.15, 3.05, 3.86, 3.60, 3.70, 3.02])

leftBorder = 0
rightBorder = 1

x = np.linspace(leftBorder, rightBorder, 1000)

numberOfSplines = 1000

mu = 0
sigma = 0.01

percent = 0.9

np.random.seed(0)
# endregion

# region Calculates

# Calculate cubic spline for base part of lab
basePartCubicSpline = Base.CubicSpline(x, xNodes, yNodes)
baseDPartCubicSpline = Base.DCubicSpline(x, xNodes, yNodes)

# Calculate Erroneous data for 3(a)
xErroneousData = Advanced.GenerateSetOfErroneousData(xNodes, numberOfSplines, mu, sigma)
yErroneousData = Advanced.GenerateSetOfErroneousData(yNodes, numberOfSplines, mu, sigma)

# Calculate Lagrange polynomials and cubic splines with errors

# X erroneous data
errorLagrangianPolynomialsOnX = []
errorCubicSplinesOnX = []

for errorDataSet in xErroneousData:
    errorLagrangianPolynomialsOnX.append(Advanced.LagrangePolynomial(x, errorDataSet, yNodes))
    errorCubicSplinesOnX.append(Base.CubicSpline(x, errorDataSet, yNodes))

# Y erroneous data
errorLagrangianPolynomialsOnY = []
errorCubicSplinesOnY = []

for errorDataSet in yErroneousData:
    errorLagrangianPolynomialsOnY.append(Advanced.LagrangePolynomial(x, xNodes, errorDataSet))
    errorCubicSplinesOnY.append(Base.CubicSpline(x, xNodes, errorDataSet))

# Calculate confidence curves
ConfidenceCurvesLagrangeByX = Advanced.DeterminationOfConfidenceCurves(errorLagrangianPolynomialsOnX, percent)
ConfidenceCurvesLagrangeByY = Advanced.DeterminationOfConfidenceCurves(errorLagrangianPolynomialsOnY, percent)

ConfidenceCurvesCubicSplineByX = Advanced.DeterminationOfConfidenceCurves(errorCubicSplinesOnX, percent)
ConfidenceCurvesCubicSplineByY = Advanced.DeterminationOfConfidenceCurves(errorCubicSplinesOnY, percent)
# endregion

# region Graphs

# Base part S(x)
DrawSourceDataAndConfigPlot(xNodes, yNodes)
plt.plot(x, basePartCubicSpline, color='purple', label="S(x)", zorder=0)
plt.legend(loc='best')
plt.savefig(fname=".\Plots\BasicCubicSpline.svg", format='svg', dpi=300)
plt.show()

# Base part S'(x)
plt.figure(dpi=300)
plt.grid()
plt.xlabel('x')
plt.ylabel('y', rotation=0)
plt.plot(x, baseDPartCubicSpline, color='orange', label='S\'(x)', zorder=0)
plt.legend(loc='best')
plt.savefig(fname=".\Plots\BasicDCubicSpline.svg", format='svg', dpi=300)
plt.show()

# Advanced part

# Lagrange polynomial
DrawSourceDataAndConfigPlot(xNodes, yNodes)
plt.plot(x, Advanced.LagrangePolynomial(x, xNodes, yNodes), color='purple', label="L(x)", zorder=0)
plt.legend(loc='best')
plt.savefig(fname=".\Plots\LagrangePolynomial.svg", format='svg', dpi=300)
plt.show()

# Set of Lagrange polynomials
DrawSourceDataAndConfigPlot(xNodes, yNodes)
for ySet in errorLagrangianPolynomialsOnX:
    plt.plot(x, ySet, linewidth=0.5, zorder=0)

plt.legend(loc='best')
plt.savefig(fname=".\Plots\SetOfLagrangePolynomials.svg", format='svg', dpi=300)
plt.show()

# Confidence curve of erroneous data set Lagrange X
DrawSourceDataAndConfigPlot(xNodes, yNodes)

plt.plot(x, ConfidenceCurvesLagrangeByX[0], color="red", linewidth=.5, linestyle="-", label="h_u", zorder=0)
plt.plot(x, ConfidenceCurvesLagrangeByX[2], color="orange", linewidth=.5, linestyle="-", label="h_l", zorder=0)
plt.plot(x, ConfidenceCurvesLagrangeByX[1], color="violet", linewidth=.5, linestyle="--", label="h_m", zorder=0)
plt.fill_between(x, ConfidenceCurvesLagrangeByX[0], ConfidenceCurvesLagrangeByX[2], alpha=0.1, color="blue", zorder=0)

plt.legend(loc='best')
plt.savefig(fname=".\Plots\ConfidenceCurveLagrangeX.svg", format='svg', dpi=300)
plt.show()

# Confidence curve of erroneous data set Lagrange Y
DrawSourceDataAndConfigPlot(xNodes, yNodes)

plt.plot(x, ConfidenceCurvesLagrangeByY[0], color="red", linewidth=.5, linestyle="-", label="h_u", zorder=0)
plt.plot(x, ConfidenceCurvesLagrangeByY[2], color="orange", linewidth=.5, linestyle="-", label="h_l", zorder=0)
plt.plot(x, ConfidenceCurvesLagrangeByY[1], color="violet", linewidth=.5, linestyle="--", label="h_m", zorder=0)
plt.fill_between(x, ConfidenceCurvesLagrangeByY[0], ConfidenceCurvesLagrangeByY[2], alpha=0.1, color="blue", zorder=0)

plt.legend(loc='best')
plt.savefig(fname=".\Plots\ConfidenceCurveLagrangeY.svg", format='svg', dpi=300)
plt.show()

# Set of Cubic splines
DrawSourceDataAndConfigPlot(xNodes, yNodes)
for ySet in errorCubicSplinesOnX:
    plt.plot(x, ySet, linewidth=0.5, zorder=0)

plt.legend(loc='best')
plt.savefig(fname=".\Plots\SetOfCubicSplines.svg", format='svg', dpi=300)
plt.show()

# Confidence curve of erroneous data set cubic Spline X
DrawSourceDataAndConfigPlot(xNodes, yNodes)

plt.plot(x, ConfidenceCurvesCubicSplineByX[0], color="red", linewidth=.5, linestyle="-", label="h_u", zorder=0)
plt.plot(x, ConfidenceCurvesCubicSplineByX[2], color="orange", linewidth=.5, linestyle="-", label="h_l", zorder=0)
plt.plot(x, ConfidenceCurvesCubicSplineByX[1], color="violet", linewidth=.5, linestyle="--", label="h_m", zorder=0)
plt.fill_between(x, ConfidenceCurvesCubicSplineByX[0], ConfidenceCurvesCubicSplineByX[2], alpha=0.1, color="blue",
                 zorder=0)

plt.legend(loc='best')
plt.savefig(fname=".\Plots\ConfidenceCurveCubicSplineX.svg", format='svg', dpi=300)
plt.show()

# Confidence curve of erroneous data set cubic Spline Y
DrawSourceDataAndConfigPlot(xNodes, yNodes)

plt.plot(x, ConfidenceCurvesCubicSplineByY[0], color="red", linewidth=.5, linestyle="-", label="h_u", zorder=0)
plt.plot(x, ConfidenceCurvesCubicSplineByY[2], color="orange", linewidth=.5, linestyle="-", label="h_l", zorder=0)
plt.plot(x, ConfidenceCurvesCubicSplineByY[1], color="violet", linewidth=.5, linestyle="--", label="h_m", zorder=0)
plt.fill_between(x, ConfidenceCurvesCubicSplineByY[0], ConfidenceCurvesCubicSplineByY[2], alpha=0.1, color="blue",
                 zorder=0)

plt.legend(loc='best')
plt.savefig(fname=".\Plots\ConfidenceCurveCubicSplineY.svg", format='svg', dpi=300)
plt.show()

# endregion
