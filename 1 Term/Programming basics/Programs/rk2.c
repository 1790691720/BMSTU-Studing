//Boundary control No. 2

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZEM 10
//main i=j
//secondary i+j=SIZEM-1
void fill_mass(int a[][SIZEM])
{
	for (int i = 0; i < SIZEM; i++)
		for (int j = 0; j < SIZEM; j++)
			a[i][j] = rand() % 10 + 1; // [1;10]
}
void output_mass(int a[][SIZEM])
{
	for (int i = 0; i < SIZEM; i++, printf("\n"))
		for (int j = 0; j < SIZEM; j++)
			printf("%2d ", a[i][j]);
	printf("\n");
}
void reverse_up_down(int a[][SIZEM])
{
	for (int i = 0; i < SIZEM / 2; i++)//Only upper part
		for (int j = (i + 1); j < (SIZEM - (i + 1)); j++)//above the main, above the side
		{
			//swap
			int temp = a[i][j];
			a[i][j] = a[SIZEM - (i + 1)][SIZEM - (j + 1)];
			a[SIZEM - (i + 1)][SIZEM - (j + 1)] = temp;
		}
}
void zeroing_left_right(int a[][SIZEM])
{
	for (int j = 0; j < SIZEM / 2; j++)//Only left part
		for (int i = j + 1; i < (SIZEM - (j + 1)); i++)//Under the main, above the side
		{
			a[i][j] = 0;
			a[i][SIZEM - j - 1] = 0;//mirror in the center
		}
}

int main()
{
	srand(time(NULL));
	int table[SIZEM][SIZEM];

	fill_mass(table);
	output_mass(table);

	reverse_up_down(table);
	output_mass(table);

	zeroing_left_right(table);
	output_mass(table);
	return 0;
}