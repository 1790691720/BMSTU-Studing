#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define AMOUNT 8
void fill_mass(int a[][AMOUNT])
{
	int target[] = { 0,0,1,3 };
	for (int i = 0; i < AMOUNT; i++)
		for (int j = i + 1; j < AMOUNT; j++)
		{
			a[i][j] = target[1 + rand() % 3];
			a[j][i] = target[3 - a[i][j]];
		}
}
void calculate_mass(int a[][AMOUNT], int b[])
{
	for (int i = 0; i < AMOUNT; i++)
		for (int j = 0; j < AMOUNT; j++)
			b[i] = b[i] + a[i][j];
}
void max_mass(int a[], int* max_score, int* max_count)
{
	*max_score = -1;
	for (int i = 0; i < AMOUNT; i++)
	{
		if (a[i] > * max_score)
		{
			*max_score = a[i];
			*max_count = 0;
		}
		if (a[i] == *max_score)
			(*max_count)++;
	}
}
void output(int a[][AMOUNT], int b[], int* max_score, int* max_count)
{
	printf("\t");
	for (int i = 0; i < AMOUNT; i++)
		printf("k%d\t", i + 1);
	printf("Summ\n");
	for (int i = 0; i < AMOUNT; i++)
	{
		printf("k%d\t", i + 1);
		for (int j = 0; j < AMOUNT; j++)
			printf("%d\t", a[i][j]);
		printf("%d\n", b[i]);
	}
	printf("Max score is %d.\n", *max_score);
	printf("Max score has %d teams. There are", *max_count);
	for (int i = 0; i < AMOUNT; i++)
		if (b[i] == *max_score)
			printf(" %d", i + 1);
	printf(".\n");
}

int main()
{
	srand(time(NULL));

	int table[AMOUNT][AMOUNT] = { 0 }, summ_table[AMOUNT] = { 0 };
	int max_score = 0, max_count = 0;

	fill_mass(table);
	calculate_mass(table, summ_table);
	max_mass(summ_table, &max_score, &max_count);
	output(table, summ_table, &max_score, &max_count);

	return 0;
}