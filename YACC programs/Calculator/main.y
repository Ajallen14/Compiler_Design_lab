%{
  #include <stdio.h>
  #include <stdlib.h>

  int yylex(void);
  int yyerror(const char *s);
%}

%token NUM
%left '+' '-'
%left '*' '/'
%left UMINUS


%%
start:
     expr {
      printf("Result = %d\n", $1);
     }
     ;
expr:
    expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr {
      if ($3 == 0) {
        printf("Error: Division by Zero\n");
        exit(1);
      }
      $$ = $1 / $3;
    }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')' { $$ = $2; }
    | NUM { $$ = $1; }
    ;
%%

int main() {
  printf("Enter expression: ");
  yyparse();
  return 0;
}

int yyerror(const char *s) {
  printf("Error: %s\n", s);
  return 0;
}