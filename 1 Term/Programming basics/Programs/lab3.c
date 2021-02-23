/*
	Program for calculating roots of the quadratic equation
*/
#include <stdio.h>
#include </usr/include/math.h>
double Get_Double(void)
{
	double a;
	while(1)
	{
		if(scanf("%lf", &a)!=0 && getchar()=='\n') return a;
		while(getchar()!='\n');
		printf("Incorrect Input. Try again: ");		
	}
}
void One_Root(double a, double b, double c)
{
	printf("Your equation has one root: %lf.\n", -b/(2*a));
	return;
}
void Two_Real_Roots(double a, double b, double c)
{
	double x1, x2, D;
	D=b*b-4*a*c;
	x1=(-b+sqrt(D))/(2*a);
	x2=(-b-sqrt(D))/(2*a);
	printf("Your equation has two roots: %lf and %lf.\n",x1,x2);
	return;
}
void Two_Imaginary_Roots(double a, double b, double c)
{
	double x1, D;
	D=b*b-4*a*c;
	D=sqrt(-D)/(2*a);
	x1=-b/(2*a);
	printf("Your equation has two imaginary roots: %lf+%lfi and %lf-%lfi.\n", x1, D, x1, D);
	return;
}
void Input_Factors(double* a, double* b, double *c)
{
	printf("Enter factor A: ");
	*a=Get_Double();
	while(*a==0)
	{
		printf("Your entered factor equal zero. Try again: ");
		*a=Get_Double();
	}

	printf("Enter factor B: ");
	*b=Get_Double();
	printf("Enter factor C: ");
	*c=Get_Double();
	return;
}

int main()
{
	double a, b, c, D;
	//Get Factors
	Input_Factors(&a, &b, &c);
	//Calculating discriminant
	D=b*b-4*a*c;
	
	if(D==0)
		One_Root(a, b, c);

	else if(D>0)
		Two_Real_Roots(a, b, c);

	else if(D<0)
		Two_Imaginary_Roots(a, b, c);

	else
		printf("Something go wrong. :(\n");

	return 0;
}
