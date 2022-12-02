%{
#include <iostream>
#include <cmath>
#include "mem.h"

extern std::map<std::string, double> variable_map;
extern unsigned int var_counter;

int yylex(void);
void yyerror(char *);

%}

%union{
    char index[100];
    double num;
}

%token<num> T_FLOAT T_INT
%token<num> OP_POW OP_DIV OP_MUL OP_ADD OP_SUB OP_EQL
%token<num> EOL
%token<num> SYM_PRNL SYM_PRNR
%token<num> FUNC_SIN FUNC_COS
%token<num> CMD_EXT
%token<index> T_IDEN

%type<num> strt
%type<num> stmt
%type<num> expr
%type<num> term
%type<num> unary
%type<num> pow
%type<num> factor

%right OP_EQL
%left OP_ADD OP_SUB
%left OP_MUL OP_DIV
%left OP_POW

%%

strt: strt stmt EOL { std::cout << $2 << "\n"; }
	| strt EOL { std::cout << "\n"; }
	| strt CMD_EXT { std::cout << ">> Bye!\n"; exit(0); }
	| {}
;


stmt: T_IDEN OP_EQL expr           { $$ = $3; set_variable($1, $3);}
    | expr                         { $$ = $1; }
;


expr: expr OP_ADD term          { $$ = $1 + $3; }
    | expr OP_SUB term         { $$ = $1 - $3; }
    | term  { $$ = $1; }
;

term: term OP_MUL unary     { $$ = $1 * $3; }
    | term OP_DIV unary       { $$ = $1 / $3; }
    | unary                     { $$ = $1; }
;

unary: OP_SUB unary            { $$ = $2 * -1; }
    | pow                       { $$ = $1; }
;

pow: factor OP_POW pow           { $$ = std::pow($1,$3); }
    | factor                    { $$ = $1; }
;

factor: T_IDEN                                      { $$ = get_variable($1); }
    | T_INT                                         { $$ = $1; }
    | T_FLOAT                                       { $$ = $1; }
    | SYM_PRNL expr SYM_PRNR                        { $$ = ($2); }
    | FUNC_SIN SYM_PRNL expr SYM_PRNR               { $$ = std::sin($3); }
    | FUNC_COS SYM_PRNL expr SYM_PRNR               { $$ = std::cos($3); }
;


%%
void yyerror(char *s)
{
	std::cout << ">> %s\n", s;
}
int main()
{
	yyparse();
	return 0;
}
