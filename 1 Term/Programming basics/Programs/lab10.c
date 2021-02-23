#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_BUF 1023

#define LINES_AMOUNT 64

/*
*plines - pointer for line
lines - amount of input lines
*result - pointer for massiv of chars from input
buffer - buffer for curret lines
i - amount of chars current lines
curr - current char
*/

void output(char* res[])
{
	int i = 0;
	putchar('\n');
	while (res[i] != NULL)
	{
		printf("%s", res[i]);
		free(res[i]);
		i++;
		putchar('\n');
	}
}


int main()
{
	char buffer[SIZE_BUF + 1], *plines, curr, * result[LINES_AMOUNT];
	int i = 0, lines = 0;
	while ((curr = getchar()) != '~' && curr != EOF)
	{
		if (!(curr == '\n'))
		{
			if (curr == ' ' || curr == '\t') continue;

			if (i > SIZE_BUF)
			{
				printf("Massiv is overflowed. Terminate.\n");
				exit(1);
			}

			buffer[i] = curr;
			i++;
		}
		else
		{
			buffer[i] = '\0';

			if ((plines = (char*)malloc((i + 1) * sizeof(char))) == NULL)
			{
				printf("Memory allocation error.\n");
				exit(2);
			}
			
			
			strcpy(plines, buffer);

			if (lines > LINES_AMOUNT)
			{
				printf("Massiv is overflowed. Terminate.\n");
				exit(1);
			}

			result[lines] = plines;

			lines++;
			i = 0;

		}
	}
	result[lines] = NULL;
	output(result);
	return 0;
}
