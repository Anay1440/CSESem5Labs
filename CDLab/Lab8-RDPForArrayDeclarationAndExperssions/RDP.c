#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Util_PrelimScanner.c"
#include "Util_LA.c"

void IDList();
Token * bufToken;

int checkIfID(char * name) { 
    if ((name[0] == 'i') && (name[1] == 'd'))
        return 1;
    return 0;
}

int checkIfNum(char * name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isdigit(name[i]))
            return 0;
    }
    return 1;
}

void invalid(Token * token) {
    if (token == NULL)
        printf("Unexpected end of code\n");
    else {
        if (checkIfID(token->name)) 
            printf("Error at: %s. Row: %d, Col: %d", getIDName(token->name), token->row, token->col);
        else
            printf("Error at: %s. Row: %d, Col: %d", token->name, token->row, token->col);
    }
    exit(1);
}

void Factor() {
    Token * token = getNextToken();
    if (token == NULL)
        invalid(token);
    if (!(checkIfID(token->name) || checkIfNum(token->name))) 
        invalid(token);
}

int MulOp(Token * token) {
    if ((strcmp(token->name, "*") == 0) || (strcmp(token->name, "/") == 0) || (strcmp(token->name, "%") == 0))
        return 1;
    return 0;
}

int AddOp(Token * token) {
    if ((strcmp(token->name, "+") == 0) || (strcmp(token->name, "-") == 0))
        return 1;
    return 0;
}

void TermPrime() {
    Token * token = getNextToken();
    if (token == NULL)
        invalid(token);
    int res = MulOp(token);
    if (res) {
        Factor();
        TermPrime();
    }
    else bufToken = token;
}

void Term() {
    Factor();
    TermPrime();
}

void SimpleExpressionPrime(Token * token) {
    int res = AddOp(token);
    if (res) {
        Term();
        SimpleExpressionPrime(bufToken);
    }
    else bufToken = token;
}

void SimpleExpression() {
    Term();
    SimpleExpressionPrime(bufToken);
}

int RelOp(Token * token) {
    if ((strcmp(token->name, "==") == 0) || (strcmp(token->name, "!=") == 0) || (strcmp(token->name, "<=") == 0) || (strcmp(token->name, ">=") == 0) || (strcmp(token->name, ">") == 0) || (strcmp(token->name, "<") == 0)) 
        return 1;
    return 0;
}

void ExpressionPrime(Token * token) {
    int res = RelOp(token);
    if (res) 
        SimpleExpression(token);
    else bufToken = token;
}

void Expression() {
    SimpleExpression();
    ExpressionPrime(bufToken);
}

int AssignStatement(Token * token) {
    if (checkIfID(token->name)) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (strcmp(token->name, "=") == 0)
            Expression();
    }
    else return 1;
}

int Statement(Token * token) {
    int res = AssignStatement(token);
    if (res != 1) {
        token = bufToken;
        if ((token == NULL) || (strcmp(token->name, ";") != 0))
            invalid(token);
    }
    return res;
}

void StatementList(Token * token) {
    if (token == NULL) 
        token = getNextToken();
        
    int res = Statement(token);
    if (res != 1)
        StatementList(NULL);
    else
        bufToken = token;
}

Token * IDListPrime() {
    Token * token = getNextToken();
    if (strcmp(token->name, ",") == 0) 
        IDList();
    else if (strcmp(token->name, "[") == 0) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (checkIfNum(token->name)) {
            token = getNextToken();
            if (token == NULL)
                invalid(token);
            if (strcmp(token->name, "]") != 0)
                invalid(token);
            else {
                token = getNextToken();
                if (strcmp(token->name, ",") == 0) 
                    IDList();
                else
                    return token;
            }
        }
        else invalid(token);
    }
    else return token;
    return NULL;
}

void IDList() {
    Token * token = getNextToken();
    if (token == NULL)
        invalid(token);
    if (checkIfID(token->name)) {
        token = IDListPrime();
        if (token != NULL)
            bufToken = token;
    }
    else invalid(token);
}

void Declarations() {
    Token * token = getNextToken();
    if (token == NULL)
        invalid(token);
    if (checkDataType(token->name) != -1) {
        IDList();
        token = bufToken;
        if (strcmp(token->name, ";") == 0)
            Declarations();
    }
    else bufToken = token;
}

int Program() {
    Token * token = getNextToken();
    if (strcmp(getIDName(token->name), "main") == 0) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (strcmp(token->name, "(") == 0) {
            token = getNextToken();
            if (token == NULL)
                invalid(token);
            if (strcmp(token->name, ")") == 0) {
                token = getNextToken();
                if (token == NULL)
                    invalid(token);
                if (strcmp(token->name, "{") == 0) {
                    Declarations();
                    StatementList(bufToken);
                    token = bufToken;
                    if (token == NULL)
                        invalid(token);
                    if (strcmp(token->name, "}") == 0)
                        return 1;
                }
            }
        }
    }
    return 0;
}

void main() {
    char fileName[100];

    // printf("Enter filename to open for token generation ");
	// scanf("%s", fileName);

    strcpy(fileName, "Text.txt");

    preliminaryScanner(fileName);
    initLA("Out.txt");

    int res = Program();

    if (res)
        printf("Valid\n");
    else
        printf("Invalid\n");

}