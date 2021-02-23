//Main Prog
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100

typedef struct element
{
	char* word;
	struct element* next;
}element_s;

element_s* initElement(char* str)
{
	element_s* first;
	if ((first = (element_s*)malloc(sizeof(element_s))) == NULL)
	{
		printf("Memory allocation error. Terminate.\n");
		exit(2);
	}
	first->word = str;
	first->next = NULL;
	return first;
}
element_s* addElement(element_s* first, char* str)
{
	element_s* temp;
	if ((temp = (element_s*)malloc(sizeof(element_s))) == NULL)
	{
		printf("Memory allocation error. Terminate.\n");
		exit(2);
	}
	temp->word = str;
	temp->next = first;
	return temp;
}
void output(element_s* first)
{
	for (; first != NULL; first = first->next)
	{
		printf("%s\n", first->word);

	}
}



int main()
{
	//variables for buffer
	char buffer[BUF_SIZE + 1], curr, prev = 'q';
	int i = 0;
	//variables for list
	element_s* Core_Element = NULL;
	while ((curr = getchar()) != EOF && curr != '~')
	{
		if (i != 0 && (curr == ' ' || curr == '\t' || curr == '\n'))
		{

			char* temp;
			buffer[i] = '\0';

			if ((temp = (char*)malloc(strlen(buffer) * sizeof(char))) == NULL)
			{
				printf("Memory allocation error. Terminate.\n");
				exit(2);
			}
			strcpy(temp, buffer);

			
			Core_Element = addElement(Core_Element, temp);
			
			i = 0;
		}
		else
		{
			if ((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z'))
			{
				//is Overflowed buffer?
				if (i == BUF_SIZE)
				{
					printf("Buffer is overflowed. Terminate.\n");
					exit(1);
				}
				buffer[i] = curr;
				i++;
			}
		}
		prev = curr;
	}
	output(Core_Element);
	return 0;
}