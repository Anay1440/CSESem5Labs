%{
    #include "Q1DeclarationsBison.tab.h"
%}

%%
[0-9]+ return NUMBER; 
\n return NL; 
"bool"|"char"|"double"|"float"|"int"|"long"|"short"|"void" return DATATYPE;
[a-zA-Z][a-zA-Z0-9_]* return ID;
. return yytext[0];
%%

int yywrap() {
    return 1;
}