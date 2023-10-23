%{
    #include <stdio.h>
%}

%%
"//"[ \ta-zA-z0-9_.]+\n fputs(yytext, yyout);
"/*"[ \t\na-zA-z0-9_.]+"*/" fputs(yytext, yyout);
[A-Z] {for(int i = 0; yytext[i] != '\0'; i++) fputc((yytext[i]) + 32, yyout);}
%%

int yywrap() {
    return 1;
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        yyout = fopen("Q6Output.txt", "w");
        yylex();
        fclose(yyin);
        printf("\nOutput file created\n");
    }
    else printf("Invalid format. Usage: ./Q6 <fileName>\n");
}