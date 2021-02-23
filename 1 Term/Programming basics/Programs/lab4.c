#include <stdio.h>
#include <math.h>

#define acc1 0.01
#define acc2 0.001
#define acc3 0.0001

#define golden_ratio 1.6180339887

double Get_Toward(double acc)
{
	double f1, f2, f3, current;
	f1 = 1;
	f2 = 1;
	f3 = f1 + f2;
	double last = f3 / f2;
	while (result > acc)
	{
		f1 = f2;
		f2 = f3;
		f3 = f1 + f2;
		current = f3 / f2;
		result = fabs(current - last);
		last = current;
	}
	return f3 / f2;
}
int main()
{
	double result;
	result = Get_Toward(acc1);
	printf("Your limit for %.2lf is %lf.\nYour absolute error is %lf.\nYour relative error is %lf.\n\n", acc1, result, fabs(golden_ratio - result), fabs((golden_ratio - result) / golden_ratio));

	result = Get_Toward(acc2);
	printf("Your limit for %.3lf is %lf.\nYour absolute error is %lf.\nYour relative error is %lf.\n\n", acc2, result, fabs(golden_ratio - result), fabs((golden_ratio - result) / golden_ratio));
	result = Get_Toward(acc3);
	printf("Your limit for %.4lf is %lf.\nYour absolute error is %lf.\nYour relative error is %lf.\n\n", acc3, result, fabs(golden_ratio - result), fabs((golden_ratio - result) / golden_ratio));
	return 0;
}
