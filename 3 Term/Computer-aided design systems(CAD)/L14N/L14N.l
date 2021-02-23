%%
[2468]([13579][24680])*[13579]? ECHO; putchar('\n');
[13579]([24680][13579])*[24680]? ECHO; putchar('\n');
[0-9]+
(\ |\t|\n) {;}
[^0-9] {puts("Error. Non-digital symbol"); return 0;}