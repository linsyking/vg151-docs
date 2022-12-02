%{
#include <stdlib.h>
#include <stdio.h>
#include "calc.tab.h"
extern YYSTYPE yylval;
void yyerror(char*);
%}

%%
"+" {
    printf("T_ADD  ");
	return OP_ADD;
}
"-" {
    printf("T_SUB  ");
	return OP_SUB;
}
"*" {
    printf("T_MUL  ");
	return OP_MUL;
}
"/" {
    printf("T_DIV  ");
	return OP_DIV;
}
"^" {
    printf("T_POW  ");
	return OP_POW;
}
"=" {
    printf("T_EQL  ");
	return OP_EQL;
}
"(" {
    printf("T_PRNL  ");
	return SYM_PRNL;
}
")" {
    printf("T_PRNR  ");
	return SYM_PRNR;
}
"sin"|"SIN" {
    printf("T_SIN  ");
	return FUNC_SIN;
}
"cos"|"COS" {
    printf("T_COS  ");
	return FUNC_COS;
}

[0-9]+ {
    printf("T_INT  ");
	sscanf(yytext, "%lf", &yylval);
	return T_INT;
}
[0-9]+(\.?[0-9]*e?-?[0-9]*)?  {
	sscanf(yytext, "%lf", &yylval);
	printf("T_FLOAT  ");
	return T_FLOAT;
}
[a-zA-Z]([a-zA-Z]|[0-9])* {
	strcpy (yylval.index, yytext);
	printf("T_IDEN  ");

	return T_IDEN;
}
\n {
	return EOL;
}
[ \t]+ {}
"quit"|"exit" {
	return CMD_EXT;
}
. {
	yyerror("ERROR: Unrecognized input!");
}

%%

int yywrap()
{
	return 1;
}
