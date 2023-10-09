#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Util_PrelimScanner.c"
#include "Util_LA.c"

void IDList();
void StatementList(Token *);
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

void TermPrime() { // Changes bufToken
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

void SimpleExpressionPrime(Token * token) { // Changes bufToken
    int res = AddOp(token);
    if (res) {
        Term();
        SimpleExpressionPrime(bufToken);
    }
    else bufToken = token;
}

void SimpleExpression() { // Changes bufToken
    Term();
    SimpleExpressionPrime(bufToken);
}

int RelOp(Token * token) {
    if ((strcmp(token->name, "==") == 0) || (strcmp(token->name, "!=") == 0) || (strcmp(token->name, "<=") == 0) || (strcmp(token->name, ">=") == 0) || (strcmp(token->name, ">") == 0) || (strcmp(token->name, "<") == 0)) 
        return 1;
    return 0;
}

void ExpressionPrime(Token * token) { // Changes bufToken
    int res = RelOp(token);
    if (res) 
        SimpleExpression(token);
    else bufToken = token;
}

void Expression() { // Changes bufToken
    SimpleExpression();
    ExpressionPrime(bufToken);
}

int AssignStatement(Token * token) { // Changes bufToken. Returns 1 if epsilon
    if (checkIfID(token->name)) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (strcmp(token->name, "=") == 0)
            Expression();
    }
    else return 1;
}

void DecisionStatementPrime() { // Changes bufToken
    Token * token = getNextToken();
    if (strcmp(token->name, "else") == 0) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (strcmp(token->name, "{") == 0) {
            StatementList(NULL);
            token = bufToken;
            if (strcmp(token->name, "}") != 0) 
                invalid(token);
        }
    }
    else bufToken = token;
}

int DecisionStatement(Token * token) { // Changes bufToken
    if (strcmp(token->name, "if") == 0) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (strcmp(token->name, "(") == 0) {
            Expression();
            token = bufToken;
            if (strcmp(token->name, "{") == 0) {
                StatementList(NULL);
                token = bufToken;
                if (strcmp(token->name, "}") == 0) 
                    DecisionStatementPrime();
            }
            else invalid(token);
        }
        else invalid(token);
    }
    else return 1;
}

int LoopingStatement(Token * token) { 
    if (strcmp(token->name, "while") == 0) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (strcmp(token->name, "(") == 0) {
            Expression();
            token = bufToken;
            if (strcmp(token->name, "{") == 0) {
                StatementList(NULL);
                token = bufToken;
                if (strcmp(token->name, "}") != 0) 
                    invalid(token);
            }
            else invalid(token);
        }
        else invalid(token);
    }
    else if (strcmp(token->name, "for") == 0) {
        token = getNextToken();
        if (token == NULL)
            invalid(token);
        if (strcmp(token->name, "(") == 0) {
            token = getNextToken();
            int res = AssignStatement(token);
            if (res == 1)
                invalid(token);
            token = bufToken;
            Expression();
            token = bufToken;
            if (strcmp(token->name, ";") != 0)
                invalid(token);
            token = getNextToken();
            res = AssignStatement(token);
            if (res == 1)
                invalid(token);
            token = bufToken;
            if (strcmp(token->name, ")") != 0)
                invalid(token);
            token = getNextToken();
            if (strcmp(token->name, "{") == 0) {
                StatementList(NULL);
                token = bufToken;
                if (strcmp(token->name, "}") != 0) 
                    invalid(token);
            }
            else invalid(token);
        }
        else invalid(token);
    }
    else invalid(token);
    return 1;
}

int Statement(Token * token) { // Returns 1 if epsilon, 0 otherwise and Changes bufToken
    int res = AssignStatement(token);
    if (res != 1) {
        token = bufToken;
        if ((token == NULL) || (strcmp(token->name, ";") != 0))
            invalid(token);
        bufToken = getNextToken();
    }
    else {
        res = DecisionStatement(token);
        if (res == 1) {
            res = LoopingStatement(token);
            if (res == 1)
                bufToken = getNextToken();
        }
    }
    return res;
}

void StatementList(Token * token) { // Changes bufToken
    if (token == NULL) 
        token = getNextToken();
    
    int res = Statement(token);
    if (res != 1)
        StatementList(bufToken);
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