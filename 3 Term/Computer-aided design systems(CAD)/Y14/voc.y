%{
#include <stdio.h>
int yylex (void);
void yyerror (char const *s);
%}

%token ZERO
%token ONE
%%

input: {printf("Enter the line:\n");}
     | input line;

line: error '\n'  {yyerrok;}
    | exp1 exp0 '\n' {
			if($2 == $1*2) 
				printf("syntax right\n");
		      }
;


exp0: ZERO ZERO {$$+=2;}
	| exp0 ZERO ZERO{$$+=2;}
;
exp1: ONE {$$++;}
	| exp1 ONE {$$++;}
;
 
%%

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

void yyerror(char const *s) {
    fprintf(stderr, "%s\n", s);      
}

int  main (void) {
    return yyparse ();
}
