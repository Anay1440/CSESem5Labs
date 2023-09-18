#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Util_PrelimScanner.c"
#include "Util_LA.c"

void IDList();
Node * bufToken;

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

void invalid() {
    printf("Invalid\n");
    exit(1);
}

void AssignStatementPrime() {
    Node * token = getNextToken();
    if (token == NULL)
        invalid();
    if ((!checkIfID(token->token.name)) && (!checkIfNum(token->token.name)))
        invalid();
    token = getNextToken();
    if ((token == NULL) || (strcmp(token->token.name, ";") != 0))
        invalid();
}

void AssignStatement(Node * token) {
    if (checkIfID(token->token.name)) {
        token = getNextToken();
        if (token == NULL)
            invalid();
        if (strcmp(token->token.name, "=") == 0)
            AssignStatementPrime();
    }
    else invalid();
}

Node * IDListPrime() {
    Node * token = getNextToken();
    if (strcmp(token->token.name, ",") == 0) 
        IDList();
    else return token;
    return NULL;
}

void IDList() {
    Node * token = getNextToken();
    if (checkIfID(token->token.name)) {
        token = IDListPrime();
        if (token != NULL)
            bufToken = token;
    }
    else invalid();
}

void Declarations() {
    Node * token = getNextToken();
    if (checkType(token->token.name) != -1) {
        IDList();
        if (strcmp(bufToken->token.name, ";") == 0)
            Declarations();
    }
    else bufToken = token;
}

int Program() {
    Node * token = getNextToken();
    if (strcmp(getIDName(token->token.name), "main")) {
        token = getNextToken();
        if (token == NULL)
            invalid();
        if (strcmp(token->token.name, "(") == 0) {
            token = getNextToken();
            if (token == NULL)
                invalid();
            if (strcmp(token->token.name, ")") == 0) {
                token = getNextToken();
                if (token == NULL)
                    invalid();
                if (strcmp(token->token.name, "{") == 0) {
                    Declarations();
                    AssignStatement(bufToken);
                    token = getNextToken();
                    if (token == NULL)
                        invalid();
                    if (strcmp(token->token.name, "}") == 0)
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
    execLA("Out.txt");

    int res = Program();

    if (res)
        printf("Valid\n");
    else
        printf("Invalid\n");

}