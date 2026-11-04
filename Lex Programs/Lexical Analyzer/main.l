%{
#include<stdio.h>
#include<stdlib.h>
%}

DIGIT	[0-9]
ID	[a-zA-Z][a-zA-Z0-9]*

%%
if|then|else|int|while|char	{printf("%s is a keyword.\n", yytext);}
{DIGIT}*			{printf("%s is a number.\n", yytext);}
{DIGIT}+"."{DIGIT}+		{printf("%s is a floating point number.\n", yytext);}
{ID}				{printf("%s is a identifier.\n", yytext);}
[\t\n]+				{/*ignore whitespace*/}
[();{}]				{printf("%s is a separator.\n", yytext);}
[,]				{printf("%s is a delimiter.\n", yytext);}
"="|"+"|"-"|"*"|"/"|"%"|"<"|">"|"<="|">="|"=="|"!=" 		{printf("%s is an operator.\n", yytext);}
%%

int main()
{
	printf("Enter input : \n");
	yylex();
	return 0;
}
int yywrap(void)
{
	return 1;
}