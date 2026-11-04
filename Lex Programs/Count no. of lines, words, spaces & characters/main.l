%{
#include<stdio.h>
int lc=1, sc=0, wc=0, cc=0;
%}

%%
[\n] {lc++; cc+=yyleng;}
[ \t] {sc++; cc+=yyleng;}
[^\t\n ]+ {wc++; cc+=yyleng;}
%%

int main() {
	printf("Enter the input :\n");
	yylex();
	printf("\nThe number of lines : %d\n", lc);
	printf("The number of spaces : %d\n", sc);
	printf("The number of words : %d\n", wc);
	printf("The number of characters : %d\n", cc);
}

int yywrap() {
	return 1;
}