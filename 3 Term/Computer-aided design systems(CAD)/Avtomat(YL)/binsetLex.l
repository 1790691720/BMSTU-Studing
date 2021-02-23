%option noyywrap
%start C N
%{
	#include <stdio.h>
	char *mes[] = {"Correct", "Incorrect"};
%}
%%
<N>[^01\n] return 1;
<N>[01] BEGIN C;
<N>\n return 0;

<C>[^01\n] return 1;
<C>[01] BEGIN N;
<C>\n return 1;

^[01] BEGIN N;
.|\n return 1;

%%
int main(int argc, char *argv[])
{
int ret = yylex();
printf("%s bin set\n", mes[ret]);
return ret;
}
