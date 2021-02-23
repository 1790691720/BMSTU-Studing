%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(char const *s);
%}

%glr-parser
%token ZERO
%token ONE
%%

input: {printf("Enter the line:\n");}
     | input line;

line : '\n' {printf("Empty line\n");}
  | error '\n'  {yyerrok;}
  | palindrom '\n' {printf("syntax right\n");}

palindrom: ZERO palindrom ZERO
| ONE palindrom ONE
| ZERO
| ONE
;
%%

int main()
{
	return yyparse();
}

void yyerror(char const *s)
{
	fprintf(stderr,"%s\n", s);      
}

int yylex(void) {
	int c;
	c = getchar();
	
	switch (c) {
		case '0': return ZERO;
		case '1': return ONE;
		case EOF: return 0;
		default: return c;
    }

}
