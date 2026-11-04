%{
#include "y.tab.h"
%}

%%
[a-zA-Z_] { return ALPHA; }
[0-9]+    { return NUMBER; }
\n        { return ENTER; }
.         { return yytext[0]; }
%%

int yywrap() {
    return 1;
}