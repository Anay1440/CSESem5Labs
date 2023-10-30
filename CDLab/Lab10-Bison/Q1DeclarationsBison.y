%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%token NUMBER ID NL DATATYPE

%%
s : declarationStatement {printf("Valid Expression\n"); exit(0);}
;
declarationStatement : DATATYPE' 'idlist';'
;
idlist : ID | ID',' idlist | ID'['NUMBER']'',' idlist | ID'['NUMBER']'
;
%%

int yyerror(char *msg) {
    printf("Invalid Expression\n");
    exit(0);
}

void main () {
    /* 
        How to compile and execute:
        $ bison -d Q1DeclarationsBison.y
        $ flex Q1DeclarationsFlex.l
        $ gcc lex.yy.c -o Q1 Q1DeclarationsBison.tab.c
    */
    printf("Enter the expression\n");
    yyparse();
}