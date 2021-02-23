#include <stdio.h>
#include <stdlib.h>

int Get_Int()
{
	int a;
	while (scanf("%d", &a) != 1)
	{
		printf("Incorrect input. Try again: ");
		while (getchar() != '\n');
	}
	return a;
}
char* WhatSay(int age)
{
	if (age >= 10 && age <= 20)
		return "лет(let)";
	else
		switch (age % 10)
		{
			case 1:
				return "год(god)";
				break;
			case 2:
			case 3:
			case 4:
				return "года(goda)";
				break;
			default:
				return "лет(let)";
				break;
		}
}
void Result_Output(int age)
{
	printf("Your age is %d. %s\n", age, WhatSay(age));
	int adulthood = abs(age - 18), pension = abs(age - 60);
	if (age < 18)
	{
		printf("To you until adulthood %d years. %s\n", adulthood, WhatSay(adulthood));
		printf("To you until pension %d years. %s\n", pension, WhatSay(pension));
	}
	else if (age == 18)
	{
		printf("You are aduthood.\n");
		printf("To you until pension %d years. %s\n", pension, WhatSay(pension));
	}
	else if (age < 60)
	{
		printf("You are adult %d years. %s\n", adulthood, WhatSay(adulthood));
		printf("To you until pension %d years. %s\n", pension, WhatSay(pension));
	}
	else if (age == 60)
	{
		printf("You are adult %d years. %s\n", adulthood, WhatSay(adulthood));
		printf("You are retired.\n");
	}
	else
	{
		printf("You are adult %d years. %s\n", adulthood, WhatSay(adulthood));
		printf("You are retired %d years. %s\n", pension, WhatSay(pension));
	}
	
}

int main()
{
	printf("Enter age in range [1; 100]: ");
	int age = Get_Int();
	while (age < 1 || age > 100)
	{
		printf("Age is not in range [1;100]. Enter again: ");
		age = Get_Int();
	}
	Result_Output(age);

	return 0;
}