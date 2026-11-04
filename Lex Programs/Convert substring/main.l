%{
int i=0;
%}

%%
[a-zA-Z]* {for(i=0; i<=yyleng; i++)
	{
		if((yytext[i]=='a')&&(yytext[i+1])&&(yytext[i+2]=='c'))
		{
			yytext[i]='A';
			yytext[i+1]='B';
			yytext[i+2]='C';
		}
	}
	printf("%s",yytext);
	}

%%

int main()
{
	yylex();
}

int yywrap()
{
	return 1;
}