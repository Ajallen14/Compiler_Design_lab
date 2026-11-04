%{
int v=0, c=0;
%}

%%
[aeiouAEIOU] {v++;}
[a-zA-Z] {c++;}
%%

int yywrap() {}

int main()
{
	printf("Enter the string of vowels and consonents : ");
	yylex();
	printf("Number of vowels : %d\n", v);
	printf("Number of consonents : %d\n", c);
	return 0;
}