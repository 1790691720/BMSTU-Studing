%{
#include <stdio.h>
#include <string.h>


int intPart=0, drbPart=0, ePart=0;
void convertP(int intPart, int drbPart, int ePart);
void convertM(int intPart, int drbPart, int ePart);
%}

%start list
%token CEL DRB CELM STP ER

%%
list:	 
	|list drob
;


drob:    CEL DRB STP	
	{
		intPart=$1; 
		drbPart=$2; 
		ePart=$3; 
		convertP(intPart, drbPart, ePart);  
	}
		
 
	|CELM DRB STP		
	{
		intPart=$1; 
		drbPart=$2; 
		ePart=$3; 
		convertM(intPart, drbPart, ePart);  
	}
;

%%

int yyerror()
{
	puts("ERROR");
}

int yywrap()
{
	return 0;
}

int gcd(int a, int b) {
	int c;
	while (b) {
		c = a % b;
		a = b;
		b = c;
	}
	if (a < 0)
		return (-a);
	else
		return a;
}

void convertP(int intPart, int drbPart, int ePart)
{
	//Calc length of drb part
	int drbLen = 0;
	int temp = drbPart;
	do {
		drbLen++;
		temp /= 10;
	} while (temp);

	//calc numenator
	int drbE = 1;
	for (int i = 0; i < drbLen; i++)
		drbE *= 10;
	int num = intPart * drbE + drbPart;

	//calc den 1.56e6
	int den = 1;
	//number = num * 10 ^ (ePart - drbLen)
	if (ePart - drbLen >= 0)
		for (int i = 0; i < (ePart - drbLen); i++)
			num *= 10;
	else
		for (int i = 0; i < (-ePart + drbLen); i++)
			den *= 10;

	int commonDivider = gcd(num, den);
	num /= commonDivider;
	den /= commonDivider;
	printf("%d/%d\n", num, den);
}

void convertM(int intPart, int drbPart, int ePart)
{
	printf("-");
	convertP(intPart, drbPart, ePart);
}

int main()
{
	yyparse();
}
