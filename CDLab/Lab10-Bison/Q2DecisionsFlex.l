%{
    #include "Q2DecisionsBison.tab.h"
%}

%%
[0-9]+ return NUMBER;
\n return NL;
"if" return IF;
"else" return ELSE;
"bool"|"char"|"double"|"float"|"int"|"long"|"short"|"void" return DATATYPE;
"=="|"!="|"<="|">="|">"|"<" return RELOP;
"+"|"-" return ADDOP;
"*"|"/"|"%" return MULOP;
[a-zA-Z][a-zA-Z0-9_]* return ID;
. return yytext[0];
%%

int yywrap() {
    return 1;
}