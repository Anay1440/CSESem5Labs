#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum", "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static", "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};
const int keywordsLen = 32;
const char *dataTypes[] = {"bool", "char", "double", "float", "int", "long", "short", "void"};
const int dataTypesSizes[] = {1, 1, 8, 4, 4, 8, 2, 0};
const int dataTypesLen = 8;

typedef struct token {
    char name[100];
	char type[20];
    int row, col;
} Token;

typedef struct node {
    Token token;
    struct node * next;
} Node;

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

void * getType(char * typeStr, int type) {
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

void printToken(char * tokenName, int type, int row, int col) {
	char typeStr[40];
	getType(typeStr, type);
	printf("<%s,%s,%d,%d>", tokenName, typeStr, row, col);
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
    while (iter != NULL) {
        if (strcmp(iter->symbol.name, name) == 0)
            return 1;
        iter = iter -> next;
    }
    return 0;
}

int preliminaryScanner(char * fileName) {
    int lineStart = 1, insideQuotes = 0, insideDoubleQuotes = 0;
    FILE * fptr1 = fopen(fileName, "r");
	if (fptr1 != NULL) {
		FILE * fptr2 = fopen("Out.txt", "w+");
		char ch = fgetc(fptr1);

		while (ch != EOF) {	
			if (lineStart == 1 && ch == '\n') {
					ch = fgetc(fptr1);
					continue;
			}
			else {
				if (ch == '"' && !insideQuotes)
					insideDoubleQuotes = !insideDoubleQuotes;
				if (ch == '\'' && !insideDoubleQuotes)
					insideQuotes = !insideQuotes;
				if (ch == '#' && !insideQuotes && !insideDoubleQuotes && lineStart == 1) {
					while (ch != EOF && (ch != '\n'))
						ch = fgetc(fptr1);
					lineStart = 1;
				}
				else if ((ch == '\t' || ch == ' ') && !insideQuotes && !insideDoubleQuotes) {
                    lineStart = 0;
					fputc(' ', fptr2);
					while (ch != EOF && (ch == '\t' || ch == ' '))
						ch = fgetc(fptr1);
				}
				else if (ch == '/' && !insideQuotes && !insideDoubleQuotes) {
					ch = fgetc(fptr1);
					if (ch == '/') {
						while (ch != EOF && (ch != '\n'))
							ch = fgetc(fptr1);
					}
					else if (ch == '*') {
						do {
							ch = fgetc(fptr1);
							if (ch == '*') {
								ch = fgetc(fptr1);
								if (ch == '/') {
									ch = fgetc(fptr1);
									break;
								}
							}
						} while (ch != EOF);
					}
					else {
						fputc('/', fptr2);
						fputc(ch, fptr2);
						ch = fgetc(fptr1);
					}
				}
				else {
					if (ch == '\n') {
						insideQuotes = 0;
						insideDoubleQuotes = 0;
						lineStart = 1;
					}
					else
						lineStart = 0;
					fputc(ch, fptr2);
					ch = fgetc(fptr1);
				}
			}
		}
        fclose(fptr1);
        fclose(fptr2);
        return 1;
	}
	else
		printf("Could not open file: %s", fileName);
        return 0;
}

Node * getNextToken() {
    tokenListRoot = tokenListRoot -> next;
    return tokenListRoot;
}

void main() {

    char fileName[100];

    printf("Enter filename to open for token generation ");
	scanf("%s", fileName);

    int res = preliminaryScanner(fileName);

    if (res == 1) {

        Node * list = (Node *) malloc(sizeof(Node));
        strcpy(list->token.name, "START");
        list->next = NULL;
        tokenListRoot = list;
        SymbolNode * symbolList = (SymbolNode *) malloc(sizeof(SymbolNode));
        strcpy(symbolList->symbol.name, "START");
        symbolList->next = NULL;
        symbolListRoot = symbolList;

        FILE * fptr1 = fopen("Out.txt", "r");
        if (fptr1 != NULL) {

	        int insideQuotes = 0, insideDoubleQuotes = 0, i = 0, row = 1, col = 1, type = 4, dataTypeInd = -1;
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
                    printf("\n");
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
                                    fseek(fptr1, -offset, SEEK_CUR);
                                }
                                strcpy(word, "id");
                            }
                            int ind = checkType(word);
                            if (ind != -1)
                                dataTypeInd = ind;
                            insertNode(list, word, type, row, col);
                            list = list -> next;
                            printToken(word, type, row, oldCol);
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
                            printToken(word, type, row, oldCol);
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

            // printf("\nTOKENS:\n");
            // Node * temp;
            // while ((temp = getNextToken()) != NULL) {
            //     printf("<%s,%s,%d,%d>", temp->token.name, temp->token.type, temp->token.row, temp->token.col);
            // }
            printf("\nSYMBOL TABLE:\nNo.\tName\tType\tDataType\tNumber of args\n");
            i = 1;
            symbolListRoot = symbolListRoot -> next;
            while (symbolListRoot != NULL) {
                printf("%d\t%s\t%s\t%s\t\t%d\n", i++, symbolListRoot->symbol.name, symbolListRoot->symbol.type, symbolListRoot->symbol.dataType, symbolListRoot->symbol.numberOfArgs);
                symbolListRoot = symbolListRoot -> next;
            }
        }
    }
}