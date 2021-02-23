DOT  "."
%{
#include"y.tab.h"
%}
%%

^[-]([1-9][0-9]*|[0])/{DOT}	{yylval=atoi(yytext); return CELM;}
^[+]?(([1-9][0-9]*)|[0])/{DOT}	{yylval=atoi(yytext); return CEL;}
\.([0-9]*)/[eE]			{yylval=atoi(yytext+1); return DRB;}
[eE][-+][0-9]{1,2}$		{yylval=atoi(yytext+1); return STP;}
([a-zA-z ]*[0-9]*)*		{return ER;}
\n |
.  ;
