%{
    #include <stdio.h>
    int scanCount = 0, printCount = 0;
%}

%%
"scanf" {fputs("READ", yyout); scanCount += 1;}
"printf" {fputs("WRITE", yyout); printCount += 1;}
%%

int yywrap() {
    return 1;
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        yyout = fopen("Q4Output.txt", "w");
        yylex();
        fclose(yyin);
        printf("\nOutput file created\n");
    }
    else printf("Invalid format. Usage: ./Q4 <fileName>\n");
}