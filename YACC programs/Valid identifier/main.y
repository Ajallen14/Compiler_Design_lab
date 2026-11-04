%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token ALPHA NUMBER ENTER

%%
var  : v ENTER { printf("Valid Variable\n"); exit(0); }
     ;

v    : ALPHA exp1
     ;

exp1 : ALPHA exp1
     | NUMBER exp1
     | 
     ;
%%

void yyerror(const char *s) {
    printf("Invalid Variable: %s\n", s);
}

int main() {
    printf("Enter the expression: ");
    yyparse();
    return 0;
}