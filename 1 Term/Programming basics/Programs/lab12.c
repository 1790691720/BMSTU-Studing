//Main Prog
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100

typedef struct element
{
	char* word;
	int amount;
	struct element* next;
}element_s;

element_s* addElement(char* str)
{
	element_s* temp;
	if ((temp = (element_s*)malloc(sizeof(element_s))) == NULL)
	{
		printf("Memory allocation error. Terminate.\n");
		exit(2);
	}
	temp->word = str;
	temp->amount = 1;
	temp->next = NULL;
	return temp;
}
void findElement(element_s* first, char* word)
{
	element_s* last = NULL;
	for (; first != NULL; first = first->next)
	{
		if (!strcmp(first->word, word))
		{
			first->amount++;
			return;
		}
		if (first->next == NULL)
			last = first;
	}
	last->next = addElement(word);
	return;
}
void output(element_s* first, FILE* file)
{
	while (first != NULL)
	{
		fprintf(file, "%d: %s\n", first->amount, first->word);
		element_s* forDelete = first;
		first = first->next;
		free(forDelete);
	}
}
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("No such arguments. Terminate.\n");
		exit(2);
	}
	FILE* file;
	if ((file = fopen(argv[1], "w+")) == NULL)
	{
		printf("Cannot open file. Terminate");
		exit(3);
	}
	//variables for buffer
	char buffer[BUF_SIZE];
	//variables for list
	element_s* Core_Element = NULL;
	while (scanf("%s", buffer) != EOF && strcmp(buffer, "~"))
	{
		char* temp;

		if ((temp = (char*)malloc(strlen(buffer) * sizeof(char))) == NULL)
		{
			printf("Memory allocation error. Terminate.\n");
			exit(2);
		}
		strcpy(temp, buffer);

		if (Core_Element == NULL)
			Core_Element = addElement(temp);
		else
			findElement(Core_Element, temp);
	}
	output(Core_Element, file);
	fclose(file);
	return 0;
}