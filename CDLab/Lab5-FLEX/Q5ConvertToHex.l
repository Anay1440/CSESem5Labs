%{
    #include <stdio.h>
%}

%%
[0-9]+ {int n = atoi(yytext); char hexNum[20]; sprintf(hexNum, "0x%X", n); fputs(hexNum, yyout);}
%%

int yywrap() {
    return 1;
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        yyout = fopen("Q5Output.txt", "w");
        yylex();
        fclose(yyin);
        printf("\nOutput file created\n");
    }
    else printf("Invalid format. Usage: ./Q5 <fileName>\n");
}