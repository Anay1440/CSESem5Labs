%{
    #include <stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* printf(" Identifier");
%%

int yywrap() { 
    return 1;
}

int main() {
    char inp[20];
    printf("Input word ");
    scanf("%s", inp);
    yylex();
}