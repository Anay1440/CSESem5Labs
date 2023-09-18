#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Util_LA.h"

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum", "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static", "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};
const int keywordsLen = 32;
const char *dataTypes[] = {"bool", "char", "double", "float", "int", "long", "short", "void"};
const int dataTypesSizes[] = {1, 1, 8, 4, 4, 8, 2, 0};
const int dataTypesLen = 8;

Node *tokenListRoot;
SymbolNode *symbolListRoot;

int checkType(char * word) {
    int i;
    for (i = 0; i < dataTypesLen; i++) {
        if (strcmp(word, dataTypes[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int check(char * word) {
	int isNum = 1, i = 0;
	for(int j = 0; j < keywordsLen; j++) {
		if (strcmp(word, keywords[j]) == 0)
			return 1;
	}
	while (word[i] != '\0') {
		if (!(word[i] >= '0' && word[i] <= '9'))
			isNum = 0;
		i++;
	}
	if (isNum)
		return 2;
    if ((word[0] == '\'' || word[0] == '"') && (word[i - 1] == '\'' || word[i - 1] == '"'))
        return 3;
	return 0;
}

void getType(char * typeStr, int type) {
	if (type == 1)
		strcpy(typeStr, "Keyword");
	else if (type == 2)
		strcpy(typeStr, "Number");
	else if (type == 3)
		strcpy(typeStr, "String literal");
	else if (type == 4)
		strcpy(typeStr, "Separator");
	else
		strcpy(typeStr, "Identifier");
}

void insertNode(Node * prev, char * name, int type, int row, int col) {
	char typeStr[40];
	getType(typeStr, type);
    Node * new = (Node *) malloc(sizeof(Node));
    strcpy(new->token.name, name);
	strcpy(new->token.type, typeStr);
    new->token.row = row;
    new->token.col = col;
    new->next = NULL;
    prev->next = new;
}

void insertSymbolNode(SymbolNode * prev, char * name, char * type, const char * dataType, int size, int numberOfArgs) {
    SymbolNode * new = (SymbolNode *) malloc(sizeof(Node));
    strcpy(new->symbol.name, name);
    strcpy(new->symbol.type, type);
    strcpy(new->symbol.dataType, dataType);
    new->symbol.size = size;
    new->symbol.numberOfArgs = numberOfArgs;
    new->next = NULL;
    prev->next = new;
}

int symbolExists(SymbolNode * root, char * name) {
    SymbolNode * iter = (SymbolNode *) malloc(sizeof(Node));
    iter = root;
    int ind = 0;
    while (iter != NULL) {
        if (strcmp(iter->symbol.name, name) == 0)
            return ind;
        iter = iter -> next;
        ind++;
    }
    return 0;
}

char * getIDName(char * tokenName) {
    //tokenName will be of the format "id1" or "id2" etc
    int id = 0;
    for (int i = 2; tokenName[i] != '\0'; i++) 
        id = id * 10 + (tokenName[i] - '0');
    SymbolNode * iter = symbolListRoot;
    iter = iter -> next;
    for (int i = 0; i < id; i++) 
        iter = iter -> next;
    return iter->symbol.name;
}

Node * getNextToken() {
    tokenListRoot = tokenListRoot -> next;
    return tokenListRoot;
}

int execLA(char * fileName) {

    Node * list = (Node *) malloc(sizeof(Node));
    strcpy(list->token.name, "START");
    list->next = NULL;
    tokenListRoot = list;
    SymbolNode * symbolList = (SymbolNode *) malloc(sizeof(SymbolNode));
    strcpy(symbolList->symbol.name, "START");
    symbolList->next = NULL;
    symbolListRoot = symbolList;

    FILE * fptr1 = fopen(fileName, "r");
    if (fptr1 != NULL) {

        int insideQuotes = 0, insideDoubleQuotes = 0, i = 0, row = 1, col = 1, type = 4, dataTypeInd = -1, idNum = 1;
        char ch = fgetc(fptr1);
        char word[100];

        while (ch != EOF) {
            if (ch == '"' && !insideQuotes) {
                if (insideDoubleQuotes) {
                    word[i] = ch;
                    word[i + 1] = '\0';
                    i++;
                }
                insideDoubleQuotes = !insideDoubleQuotes;
            }
            if (ch == '\'' && !insideDoubleQuotes) {
                if (insideQuotes) {
                    word[i] = ch;
                    word[i + 1] = '\0';
                    i++;
                }
                insideQuotes = !insideQuotes;
            }
            if (ch == '\n') {
                insideQuotes = 0;
                insideDoubleQuotes = 0;
                row++;
                col = 1;
            }
            else
            if (!insideQuotes && !insideDoubleQuotes) {
                if (!((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90) || (ch >= '0' && ch <= '9'))) {
                    int oldCol = col;
                    if (i > 0) {
                        col += strlen(word);
                        type = check(word);
                        if (!type) {
                            if (dataTypeInd != -1 && (!symbolExists(symbolListRoot, word))) {
                                char chTemp = ch;
                                int offset = 1, numberOfArgs = 0;
                                while (chTemp == ' ' || chTemp == '\t') {
                                    offset++;
                                    chTemp = fgetc(fptr1);
                                }
                                if (chTemp == '(') {
                                    while (chTemp != ')') {
                                        chTemp = fgetc(fptr1);
                                        offset++;
                                        if (chTemp == ',') {
                                            if (numberOfArgs == 0)
                                                numberOfArgs = 2;
                                            else
                                                numberOfArgs++;
                                        }
                                    }
                                    insertSymbolNode(symbolList, word, "function", dataTypes[dataTypeInd], dataTypesSizes[dataTypeInd], numberOfArgs);
                                    symbolList = symbolList -> next;
                                }
                                else {
                                    insertSymbolNode(symbolList, word, "variable", dataTypes[dataTypeInd], dataTypesSizes[dataTypeInd], 0);
                                    symbolList = symbolList -> next;
                                }
                                fseek(fptr1, -offset + 1, SEEK_CUR);
                            }
                            int ind = symbolExists(symbolListRoot, word);
                            if (ind == 0) {
                                strcpy(word, "id");
                                char numInStr[10];
                                sprintf(numInStr, "%d", idNum);
                                strcat(word, numInStr);
                                idNum++;
                            }
                            else {
                                strcpy(word, "id");
                                char numInStr[10];
                                sprintf(numInStr, "%d", ind);
                                strcat(word, numInStr);
                            }
                        }
                        int ind = checkType(word);
                        if (ind != -1)
                            dataTypeInd = ind;
                        insertNode(list, word, type, row, col);
                        list = list -> next;
                        oldCol = col;
                        i = 0;
                        type = 4;
                        strcpy(word, "\0");
                    }
                    if (ch == '=') {
                        i = 0;
                        word[i++] = ch;
                        ch = fgetc(fptr1);
                        if (ch == '=') 
                            word[i++] = ch;
                        else
                            fseek(fptr1, -1, SEEK_CUR);
                        word[i] = '\0';
                    }
                    else if (ch == '<' || ch == '>' || ch == '!') {
                        i = 0;
                        word[i++] = ch;
                        ch = fgetc(fptr1);
                        if (ch == '=')
                            word[i++] = ch;
                        else
                            fseek(fptr1, -1, SEEK_CUR);
                        word[i] = '\0';
                    }
                    else if (ch == '&') {
                        i = 0;
                        word[i++] = ch;
                        ch = fgetc(fptr1);
                        if (ch == '&')
                            word[i++] = ch;
                        else
                            fseek(fptr1, -1, SEEK_CUR);
                        word[i] = '\0';
                    }
                    else if (ch == '|') {
                        i = 0;
                        word[i++] = ch;
                        ch = fgetc(fptr1);
                        if (ch == '|')
                            word[i++] = ch;
                        else
                            fseek(fptr1, -1, SEEK_CUR);
                        word[i] = '\0';
                    }
                    else if (ch == '!') {
                        i = 0;
                        word[i++] = ch;
                        ch = fgetc(fptr1);
                        if (ch == '=')
                            word[i++] = ch;
                        fseek(fptr1, -1, SEEK_CUR);
                        word[i] = '\0';
                    }
                    else if (ch == '+') {
                        i = 0;
                        word[i++] = ch;
                        ch = fgetc(fptr1);
                        if (ch == '+')
                            word[i++] = ch;
                        else
                            fseek(fptr1, -1, SEEK_CUR);
                        word[i] = '\0';
                    }
                    else if (ch == '-') {
                        i = 0;
                        word[i++] = ch;
                        ch = fgetc(fptr1);
                        if (ch == '-')
                            word[i++] = ch;
                        else if (ch == '>')
                            word[i++] = ch;
                        else
                            fseek(fptr1, -1, SEEK_CUR);
                        word[i] = '\0';
                    }
                    else if (ch == '}' || ch == ']' || ch == ';' || ch == '{' || ch == '[' || ch == '^' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == ',' || ch == '.' || ch == '#') {
                        i = 0;
                        word[i++] = ch;
                        word[i] = '\0';
                    }
                    else if (ch == '\t')
                        i = 4;
                    else if (ch == ' ')
                        i = 1;
                    if (strcmp(word, "\0") != 0) {
                        insertNode(list, word, type, row, col);
                        list = list -> next;
                    }
                    strcpy(word, "\0");
                    col += i;
                    i = 0;
                }
                else {
                    word[i] = ch;
                    word[i + 1] = '\0';
                    i++;
                }
            }
            else {
                word[i] = ch;
                word[i + 1] = '\0';
                i++;
            }
            ch = fgetc(fptr1); 
        }
    }
    return 1;
}