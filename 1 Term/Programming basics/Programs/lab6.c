#include <stdio.h>
#include <stdlib.h>

#define FRACTIONAL_LENGTH 10
#define ACCURANCY 0.000001

void Convert(double number, int radix);
void Convert_Integer(int number, int radix);
void Convert_Fractional(double number, int radix);

int Get_Int()
{
	int a;
	while (scanf("%d", &a) != 1)
	{
		while (getchar() != '\n');
		printf("Incorrect input. Try again: ");
	}
	return a;
}
double Get_Double()
{
	double a;
	while (scanf("%lf", &a) != 1)
	{
		while (getchar() != '\n');
		printf("Incorrect input. Try again: ");
	}
	return a;
}
void Convert(double number, int radix)
{
	if (number < 0)
	{
		printf("-");
		number = -number;
	}
	if ((int)number == 0)
		printf("0");
	else
		Convert_Integer((int)number, radix);
	if ((number - (int)number) != 0)
		Convert_Fractional(number - (int)number, radix);
}
void Convert_Integer(int number, int radix)
{
	if (number == 0)
		return;
	int digit = number % radix;
	Convert_Integer(number / radix, radix);
	printf("%X", digit);
}
void Convert_Fractional(double number, int radix)
{
	int length = 0;
	printf(".");
	while (!(number < ACCURANCY) && length < FRACTIONAL_LENGTH)
	{
		number = number * radix;
		printf("%X", (int)number);
		number = number - (int)number;
		length++;
	}
}
int main()
{
	int radix;
	printf("Enter radix in range [2;16]: ");
	radix = Get_Int();
	while (radix > 16 || radix < 2)
	{
		printf("Radix is not in range [2;16]. Enter again: ");
		radix = Get_Int();
	}
	
	double initial_number;
	printf("Enter number to convert it to %d radix: ", radix);
	initial_number = Get_Double();
	
	printf("Your number in %d radix is: ", radix);
	Convert(initial_number, radix);

	return 0;
}