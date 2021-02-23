#include <stdio.h>


int main()
{
	double Radius=0, Result=0;

	double pi=3.14159265359;
	printf("Hi! Enter the radius of the circle to calculate its length: ");
	while(scanf("%lf", &Radius) == 0 || getchar()!='\n')
	{
		while(getchar()!='\n'); // Чистим буфер
		printf("Incorrect input. Try again: ");
	}
	Result=2*pi*Radius;
	printf("\nYour result of cirle's length for Radius %lf ,when pi = %lf, is %lf. \n", Radius, pi, Result);
	
	return 0;
}
