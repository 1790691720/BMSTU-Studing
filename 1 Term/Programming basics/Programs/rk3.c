#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0
/*
exits:
1: invalid arguments
2: Can't open file
3: memory allocation error
*/

typedef struct element {
	char* str;
	struct element* next;
}element_s;

element_s* Head = NULL;

void tempoutput();
void output();
void addElement(char* word);
void input(FILE* filename);
_Bool findElement(char c);
void deleteElement(element_s** prev, element_s** curr);

void tempoutput()
{
	printf("Temp output:\n");
	if (Head == NULL)
	{
		printf("Empty list.\n\n\n");
		return;
	}
	element_s* temp;
	for (temp = Head; temp != NULL; temp = temp->next)
		printf("%s\n", temp->str);
	printf("\n\n");
}
void output()
{
	printf("Result output:\n");
	if (NULL == Head)
	{
		printf("Empty list.\n\n\n");
		return;
	}
	element_s* temp;
	while (NULL != Head)
	{
		printf("%s\n", Head->str);
		temp = Head;
		Head = Head->next;
		free(temp);
	}
}
void input(FILE* filename)
{
	char buffer[BUFFER_SIZE];
	char* temp;
	while (fscanf(filename, "%s", buffer) != EOF)
	{
		if (NULL == (temp = (char*)malloc(sizeof(char) * strlen(buffer))))
			exit(3);
		strcpy(temp, buffer);
		addElement(temp);
	}
}
void addElement(char* word)
{
	element_s* temp;
	if (NULL == (temp = (element_s*)malloc(sizeof(element_s))))
		exit(3);
	temp->str = word;
	temp->next = Head;
	Head = temp;
}
_Bool findElement(char c)
{
	element_s* curr = Head, * prev = Head;
	_Bool isFounded =FALSE;
	while (NULL != curr)
	{
		if (strchr(curr->str, c))
		{
			isFounded = TRUE;
			deleteElement(&prev, &curr);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return isFounded;
}
void deleteElement(element_s** prev, element_s** curr)
{
	printf("Found element: %s. Deleting...\n", (*curr)->str);
	if ((*curr) == Head)
	{
		Head = Head->next;
		free(*curr);
		*curr = Head;
		*prev = Head;
		return;
	}
	else
	{
		(*prev)->next = (*curr)->next;
		free(*curr);
		*curr = (*prev)->next;
	}
}
int main(int argc, char* argv[])
{
	//Preparation
	if (argc != 2)
		exit(1);
	FILE* filename;
	if (NULL == (filename = fopen(argv[1], "r")))
		exit(2);
	//All preparation ready
	input(filename);
	fclose(filename);
	//If the list is empty, then nothing
	if (NULL != Head)
	{
		//temp output
		tempoutput();

		//Processing
		char curr;
		while (EOF != (curr = getchar()) && NULL != Head && '~' != curr)
			if (' ' != curr && '\n' != curr && '\t' != curr)
				if (Head != NULL)
				{
					printf("Searches for elements with symbol '%c'. After search, print list.\n", curr);
					if(findElement(curr))
						tempoutput();
					else
						printf("Not found.\n\n\n");
				}
	}
	//Output
	output();
	return 0;
}