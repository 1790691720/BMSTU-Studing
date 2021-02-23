#include <stdio.h>

int main()
{
	int chars = 0, lines = 0, words = 0, SpecialChar = 0, digits = 0, other = 0, letters = 0, OperateChar = 0;
	int curr = 0, prev = 0;
	while ((curr = getchar()) != EOF)
	{
		chars++;

		if (curr == '\n')
			lines++;
		if ((prev != '\t' && prev != '\n' && prev != ' ') &&
			(curr == '\t' || curr == '\n' || curr == ' '))
			words++;
	if (curr >= 0 && curr <= 31)
			SpecialChar++;
		else if ((curr >= 'A' && curr <= 'Z') || (curr >= 'a' && curr <= 'z'))
			letters++;
		else if (curr >= '0' && curr <= '9')
			digits++;
		else if ((curr >= '!' && curr <= '/') || (curr >= ':' && curr <= '@') ||
			(curr >= '[' && curr <= '`') || (curr >= '{' && curr <= '~'))
			OperateChar++;
		else
			other++;

		prev = curr;

		putchar(curr);
	}
	printf("\nChars: %d.\n", chars);
	printf("Letters: %d.\n", letters);
	printf("Lines: %d.\n", lines);
	printf("Words: %d.\n", words);
	printf("Special Chars: %d.\n", SpecialChar);
	printf("Operate Chars: %d.\n", OperateChar);
	printf("Digits: %d.\n", digits);
	printf("Other: %d.\n", other);
}