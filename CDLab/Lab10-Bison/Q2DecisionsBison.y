%{
    #include <stdio.h>
    #include <stdlib.h>
    extern FILE *yyin;
%}

%token NUMBER ID NL DATATYPE ADDOP RELOP MULOP IF ELSE

%%
s : decisionStatement {printf("Valid\n"); exit(0);}
;
statementList : statement' 'statementList | /* epsilon */
;
statement : assignStatement';' | decisionStatement';'
;
assignStatement : ID '=' expn
;
expn : simpleExpn' 'ePrime
;
ePrime : RELOP' 'simpleExpn | /* epsilon */
;
simpleExpn : term' 'sePrime
;
sePrime : ADDOP' 'term' 'sePrime | /* epsilon */
;
term : factor' 'tPrime
;
tPrime : MULOP' 'factor' 'tPrime | /* epsilon */
;
factor : ID | NUMBER
;
decisionStatement : IF '('expn')''{'statementList'}'dPrime
;
dPrime : ELSE '{'statementList'}' | /* epsilon */
;
%%

int yyerror(char *msg) {
    printf("Invalid Expression\n");
    exit(0);
}

void main (int argc, char * argv[]) {
    /* 
        How to compile and execute:
        $ bison -d Q2DecisionsBison.y
        $ flex Q2DecisionsFlex.l
        $ gcc lex.yy.c -o Q1 Q2DecisionsBison.tab.c
    */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        printf("Enter the expression\n");
        yyparse();
        fclose(yyin);
    }
    else printf("Invalid format. Usage: ./Q2 <fileName>\n");
}