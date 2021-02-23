#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
char* colorYear(int year)
{
	switch (year)
	{
	case 0:
		return "green";
	case 1:
		return "red";
	case 2:
		return "yellow";
	case 3:
		return "white"; 
	case 4:
		return "black";
	}
}
char* animalYear(int year)
{
	switch (year)
	{
	case 0:
		return "rat";
	case 1:
		return "bull";
	case 2:
		return "tiger";
	case 3:
		return "rabbit";
	case 4:
		return "dragon";
	case 5:
		return "snake";
	case 6:
		return "horse";
	case 7:
		return "sheep";
	case 8:
		return "monkey";
	case 9:
		return "cock";
	case 10:
		return "dog";
	case 11:
		return "boar";
	}
}
int main()
{
	unsigned long long year;
	char newYear[14];

	do
	{
		if (scanf("%llu", &year) == 1)
		{
			strcpy(newYear, colorYear(((year - 4) % 60) / 12));
			strcat(newYear, " ");
			strcat(newYear, animalYear((year - 4) % 12));
			printf("%s\n", newYear);
		}
		/*else
		{
			printf("Incorrect input");
			break;
		}*/
	} while (getchar() != EOF);
	return 0;
}