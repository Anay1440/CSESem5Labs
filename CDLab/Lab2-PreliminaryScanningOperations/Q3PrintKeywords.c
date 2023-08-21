#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum", "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static", "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};
int keywordsLen = 32;

int check(char * word) {
	for(int i = 0; i < keywordsLen; i++) {
		if (strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

void main() {
	FILE * fptr;
	char fileName[100];
	int lineStart = 1, insideQuotes = 0, insideDoubleQuotes = 0, i = 0;
	printf("Enter filename to open for preprocessing ");
	scanf("%s", fileName);
	fptr = fopen(fileName, "r");
	if (fptr != NULL) {
		char ch = fgetc(fptr);

		char word[100];

		while (ch != EOF) {

			if (ch == '"' && !insideQuotes)
				insideDoubleQuotes = !insideDoubleQuotes;
			if (ch == '\'' && !insideDoubleQuotes)
				insideQuotes = !insideQuotes;
			if (ch == '\n') {
					insideQuotes = 0;
					insideDoubleQuotes = 0;
					lineStart = 1;
				}
			else
				lineStart = 0;

			if (!insideQuotes && !insideDoubleQuotes) {
				if (!((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90))) {
					if (i > 0 && check(word)) {
						int j = 0;
						while (word[j] != '\0')
							printf("%c", toupper(word[j++]));
						printf("\n");		
					}
					strcpy(word, "\0");
					i = 0;			
				}
				else {
					word[i] = ch;
					word[i + 1] = '\0';
					i++;
				}
			}

			ch = fgetc(fptr);

		}

	}
	else
		printf("Could not open file: %s", fileName);
}