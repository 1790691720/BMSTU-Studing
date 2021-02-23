%{
#include<stdio.h>
int yylex();
int yyerror(char* s);
%}

%%

S:	'\n'
	| error '\n' {yyerrok;}
	| p'\n' {puts("Correct binset");};

p:	'1' q
	| '0' q
;
q:	'1' p
	| '0' p
	|
;

%%

int yylex()
{
	return(getchar());
}

int yyerror(char* s)
{
	printf("%s\n", s);
	return(1);
}

int main(int argc, char* argv[])
{

	return yyparse();
}
