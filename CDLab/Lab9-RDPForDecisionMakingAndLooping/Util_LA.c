#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum", "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static", "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};
const int keywordsLen = 32;
const char *dataTypes[] = {"bool", "char", "double", "float", "int", "long", "short", "void"};
const int dataTypesSizes[] = {1, 1, 8, 4, 4, 8, 2, 0};
const int dataTypesLen = 8;

FILE * fptr;
int row = 1, col = 1, dataTypeInd = -1, idCount = 1;

typedef struct token {
    char name[100];
	char type[20];
    int row, col;
} Token;

typedef struct symbol {
    char name[100];
    char type[100];
    char dataType[100];
    int size, numberOfArgs;
} Symbol;

typedef struct symbolNode {
    Symbol symbol;
    struct symbolNode * next;
} SymbolNode;

SymbolNode * symbolListRoot;
SymbolNode * symbolList;

int checkDataType(char * word) {
    int i;
    for (i = 0; i < dataTypesLen; i++) {
        if (strcmp(word, dataTypes[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void insertSymbolNode(SymbolNode * prev, char * name, char * type, const char * dataType, int numberOfArgs) {
    SymbolNode * new = (SymbolNode *) malloc(sizeof(SymbolNode));
    strcpy(new->symbol.name, name);
    strcpy(new->symbol.type, type);
    strcpy(new->symbol.dataType, dataType);
    new->symbol.numberOfArgs = numberOfArgs;
    new->next = NULL;
    prev->next = new;
}

int checkIfKeywordOrIdentifier(char * word) {
	for(int i = 0; i < keywordsLen; i++) {
		if (strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int symbolExists(SymbolNode * root, char * name) {
    SymbolNode * iter = (SymbolNode *) malloc(sizeof(SymbolNode));
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
    for (int i = 0; i < id; i++)  
        iter = iter -> next;
    return iter->symbol.name;
}

Token * getCharOrStringLiteral(int type) {

    char buf[100];
    int i = 0;
    buf[i++] = type == 1 ? '\'' : '"';
    char ch = fgetc(fptr);

    while (ch != EOF && ch != (type == 1 ? '\'' : '"')) {
        buf[i++] = ch;
        ch = fgetc(fptr);
    }

    buf[i++] = (type == 1 ? '\'' : '"');
    buf[i] = '\0';

    Token * new = (Token *) malloc(sizeof(Token));
    strcpy(new->name, buf);
    strcpy(new->type, (type == 1 ? "Char literal" : "String literal"));
    new->row = row;
    new->col = col;
    col += i;

    return new;
}

Token * getNumber(char ch) {
    
    char buf[100];
    int i = 0;
    buf[i++] = ch;
    ch = fgetc(fptr);

    while (ch != EOF && (ch >= '0' && ch <= '9')) {
        buf[i++] = ch;
        ch = fgetc(fptr);
    }

    fseek(fptr, -1, SEEK_CUR);

    buf[i] = '\0';

    Token * new = (Token *) malloc(sizeof(Token));
    strcpy(new->name, buf);
    strcpy(new->type, "Number");
    new->row = row;
    new->col = col;
    col += i;

    return new;
}

Token * getKeywordOrIdentifier(char ch) {

    char buf[100];
    int i = 0;

    while (ch != EOF && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= '0' && ch <= '9'))) {
        buf[i++] = ch;
        ch = fgetc(fptr);
    }

    fseek(fptr, -1, SEEK_CUR);

    buf[i] = '\0';

    if (checkIfKeywordOrIdentifier(buf) == 1) { //Keyword

        int temp = checkDataType(buf);

        if (temp != -1)
            dataTypeInd = temp;

        Token * new = (Token *) malloc(sizeof(Token));
        strcpy(new->name, buf);
        strcpy(new->type, "Keyword");
        new->row = row;
        new->col = col;
        col += i;

        return new;

    }
    else { //Identifier

        Token * new = (Token *) malloc(sizeof(Token));
        strcpy(new->name, "id");
        strcpy(new->type, "Identifier");
        new->row = row;
        new->col = col;
        col += i;

        int ind = symbolExists(symbolListRoot, buf);

        if (ind == 0) {
            
            ch = fgetc(fptr);
            int offset = 1, numberOfArgs = 0;
            char type[100];

            while (ch != EOF && (ch == ' ')) {
                offset++;
                ch = fgetc(fptr);
            }

            if (ch == '(') {
                while (ch != ')') {
                    ch = fgetc(fptr);
                    offset++;
                    if (ch == ',') {
                        if (numberOfArgs == 0)
                            numberOfArgs = 2;
                        else
                            numberOfArgs++;
                    }
                }
                strcpy(type, "function");
            }
            else 
                strcpy(type, "variable");
            
            fseek(fptr, -offset, SEEK_CUR);

            if (dataTypeInd != -1)
                insertSymbolNode(symbolList, buf, type, dataTypes[dataTypeInd], numberOfArgs);
            else
                insertSymbolNode(symbolList, buf, "Identifier", "NULL", 0);
            symbolList = symbolList -> next;

            char numInStr[10];
            sprintf(numInStr, "%d", idCount++);
            strcat(new->name, numInStr);
        }
        else {
            char numInStr[10];
            sprintf(numInStr, "%d", ind);
            strcat(new->name, numInStr);
        }

        return new;

    }
}

Token * getNextToken() {

    int i;
    char ch = fgetc(fptr);

    if (ch != EOF) {
        
        while ((ch != EOF) && (ch == ' ' || ch == '\n')) {
            if (ch == ' ')
                col++;
            if (ch == '\n') {
                col = 1;
                row++;
                dataTypeInd = -1;
            }
            ch = fgetc(fptr);
        }
        
        if (ch == '"')
            return getCharOrStringLiteral(2);

        if (ch == '\'')
            return getCharOrStringLiteral(1);

        if (ch >= '0' && ch <= '9') 
            return getNumber(ch);

        if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ',' || ch == '.' || ch == '#' || ch == ':' || ch == '?' || ch == '~' || ch == '^' || ch == '%' || ch == '@' || ch == '`' || ch == '$' || ch == '\\' || ch == '*' || ch == '/') {
            char separator[2];
            separator[0] = ch;
            separator[1] = '\0';
            Token * new = (Token *) malloc(sizeof(Token));
            strcpy(new->name, separator);
            strcpy(new->type, "Separator");
            new->row = row;
            new->col = col;
            col++;
            return new;
        }

        char buf[3];
        i = 0;
        if (ch == '=') {
            buf[i++] = ch;
            ch = fgetc(fptr);
            if (ch == '=') 
                buf[i++] = ch;
            else
                fseek(fptr, -1, SEEK_CUR);
            buf[i] = '\0';
        }
        else if (ch == '<' || ch == '>' || ch == '!') {
            buf[i++] = ch;
            ch = fgetc(fptr);
            if (ch == '=')
                buf[i++] = ch;
            else
                fseek(fptr, -1, SEEK_CUR);
            buf[i] = '\0';
        }
        else if (ch == '&') {
            buf[i++] = ch;
            ch = fgetc(fptr);
            if (ch == '&')
                buf[i++] = ch;
            else
                fseek(fptr, -1, SEEK_CUR);
            buf[i] = '\0';
        }
        else if (ch == '|') {
            buf[i++] = ch;
            ch = fgetc(fptr);
            if (ch == '|')
                buf[i++] = ch;
            else
                fseek(fptr, -1, SEEK_CUR);
            buf[i] = '\0';
        }
        else if (ch == '!') {
            ch = fgetc(fptr);
            if (ch == '=')
                buf[i++] = ch;
            fseek(fptr, -1, SEEK_CUR);
            buf[i] = '\0';
        }
        else if (ch == '+') {
            buf[i++] = ch;
            ch = fgetc(fptr);
            if (ch == '+')
                buf[i++] = ch;
            else if (ch == '=')
                buf[i++] = ch;
            else
                fseek(fptr, -1, SEEK_CUR);
            buf[i] = '\0';
        }
        else if (ch == '-') {
            buf[i++] = ch;
            ch = fgetc(fptr);
            if (ch == '-')
                buf[i++] = ch;
            else if (ch == '=')
                buf[i++] = ch;
            else if (ch == '>')
                buf[i++] = ch;
            else
                fseek(fptr, -1, SEEK_CUR);
            buf[i] = '\0';
        }

        if (i > 0) {
            Token * new = (Token *) malloc(sizeof(Token));
            strcpy(new->name, buf);
            strcpy(new->type, "Operator");
            new->row = row;
            new->col = col;
            col += i;
            return new;
        }
        else 
            return getKeywordOrIdentifier(ch);
    }
    return NULL;
}

void initLA(char * fileName) {
    symbolList = (SymbolNode *) malloc(sizeof(SymbolNode));
    strcpy(symbolList->symbol.name, "START");
    symbolList->next = NULL;
    symbolListRoot = symbolList;

    fptr = fopen(fileName, "r");

    row = 1, col = 1, dataTypeInd = -1;
}