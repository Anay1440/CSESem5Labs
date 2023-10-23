%{
    #include <stdio.h>
    int vowelsCount = 0, consonantCount = 0;
%}

%%
[aeiouAEIOU] vowelsCount += 1;
[a-zA-Z] consonantCount += 1;
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a sentence. Enter Ctrl-D at the end. ");
    yylex();
    printf("\nNumber of vowels: %d\nNumber of consonants: %d\n", vowelsCount, consonantCount);
}