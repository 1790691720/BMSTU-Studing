#include <stdio.h>
#include <math.h>

#define IDEAL 3.16076186115975

double func(double x)
{
	return cos(0.5 * x) - x * x + 10;
}
double root(double left, double right, double accuracy)
{
	double MiddleRoot, middle;
	int i = 0;
	do
	{
		middle = (left + right) / 2;
		MiddleRoot = func(middle);
		if (MiddleRoot * func(left) > 0)
			left = middle;
		else
			right = middle;
		i++;
	} while (fabs(MiddleRoot) > accuracy);
	printf("Iteration: %d. ", i);
	return middle;
}
int main()
{
	double result, abs_err;
	for (double i = 0.1; i >= 0.000001; i = i / 10)
	{
		result = root(0, 8, i);
		printf("Accuracy is %lf. ", i);
		printf("Your root is %lf.\n", result);
		abs_err = fabs(IDEAL - result);
		printf("Absolute error: %lf. Relative error: %lf%%.\n\n", abs_err, 100 * (abs_err / IDEAL));
	}
	return 0;
}
//y=cos(0.5*x)	- x*x + 10
//[0;8]