#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum", "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static", "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};
int keywordsLen = 32;

typedef struct token {
    char name[100];
	char type[20];
    int row, col;
} Token;

typedef struct node {
    Token token;
    struct node * next;
} Node;

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

void main() {
	FILE * fptr1;
    Node * list = (Node *) malloc(sizeof(Node)), * root;
    strcpy(list->token.name, "START");
    list->token.row = 0;
    list->token.col = 0;
    list->next = NULL;
    root = list;
	char fileName[100];
	int lineStart = 1, insideQuotes = 0, insideDoubleQuotes = 0, i = 0, row = 1, col = 1;
	printf("Enter filename to open for token generation ");
	scanf("%s", fileName);
	fptr1 = fopen(fileName, "r");
	if (fptr1 != NULL) {
		char ch = fgetc(fptr1);
		char word[100];
		int type;

		while (ch != EOF) {
					
			if (lineStart == 1 && ch == '\n') {
                ch = fgetc(fptr1);
			}
			else {
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
					lineStart = 1;
					row++;
					col = 1;
					printf("\n");
				}
				else
					lineStart = 0;
				if (!insideQuotes && !insideDoubleQuotes) {
					if (!((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90) || (ch >= '0' && ch <= '9'))) {
                        int oldCol = col;
						if (i > 0) {
							col += strlen(word);
							type = check(word);
							if (!type)
								strcpy(word, "id");
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
						else if (ch == '}' || ch == ']' || ch == ';' || ch == '{' || ch == '[' || ch == '^' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == ',' || ch == '.') {
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
		}

        printf("\nTOKENS:\n");
        while (root != NULL) {
            printf("<%s,%s,%d,%d>", root->token.name, root->token.type, root->token.row, root->token.col);
            root = root -> next;
        }
	}
	else
		printf("Could not open file: %s", fileName);
}