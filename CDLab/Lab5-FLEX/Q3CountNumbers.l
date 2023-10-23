%{
    #include <stdio.h>
    int posIntCount = 0, negIntCount = 0, posFloatCount = 0, negFloatCount = 0;
%}

%%
"-"[0-9]+\.[0-9]+ negFloatCount += 1;
[0-9]+\.[0-9]+ posFloatCount += 1;
"-"[0-9]+ negIntCount += 1;
[0-9]+ posIntCount += 1;
%%

int yywrap() {
    return 1;
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        yylex();
        fclose(yyin);
        printf("\nNumber of positive integers: %d\nNumber of negative integers: %d\nNumber of positive floats: %d\nNumber of negative floats: %d\n", posIntCount, negIntCount, posFloatCount, negFloatCount);
    }
    else printf("Invalid format. Usage: ./Q3 <fileName>\n");
}