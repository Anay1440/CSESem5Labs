%{
    #include <stdio.h>
    int charCount = 0, lineCount = 1, blanksCount = 0, wordsCount = 1;
%}

%%
\n {lineCount += 1; charCount += 1; wordsCount += 1;}
\t {blanksCount += 4; charCount += 1; wordsCount += 1;}
" \n" {lineCount += 1; charCount += 2; wordsCount += 1;}
" " {blanksCount += 1; charCount += 1; wordsCount += 1;}
. charCount += 1;
%%

int yywrap() {
    return 1;
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        yylex();
        fclose(yyin);
        printf("\nNumber of words: %d\nNumber of chars: %d\nNumber of lines: %d\nNumber of blanks: %d\n", wordsCount, charCount, lineCount, blanksCount);
    }
    else printf("Invalid format. Usage: ./Q2 <fileName>\n");
}