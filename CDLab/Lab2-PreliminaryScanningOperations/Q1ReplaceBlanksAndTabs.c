#include <stdio.h>

void main() {

	FILE * fptr1, * fptr2;
	char fileName[100];
	int lineStart = 1, insideQuotes = 0, insideDoubleQuotes = 0;
	printf("Enter filename to open for preprocessing ");
	scanf("%s", fileName);
	fptr1 = fopen(fileName, "r");
	if (fptr1 != NULL) {
		fptr2 = fopen("Q1Out.txt", "w+");
		char ch = fgetc(fptr1);

		while (ch != EOF) {

			if (lineStart == 1 && ch == '\n') {
					ch = fgetc(fptr1);
					continue;
			}
			else {
				if (ch == '\n')
					lineStart = 1;
				else
					lineStart = 0;
				if (ch == '"' && !insideQuotes)
					insideDoubleQuotes = !insideDoubleQuotes;
				if (ch == '\'' && !insideDoubleQuotes)
					insideQuotes = !insideQuotes;
				if ((ch == '\t' || ch == ' ') && !insideQuotes && !insideDoubleQuotes) {
					fputc(' ', fptr2);
					while (ch != EOF && (ch == '\t' || ch == ' '))
						ch = fgetc(fptr1);
				}
				else {
					fputc(ch, fptr2);
					ch = fgetc(fptr1);
				}
			}
		}
		printf("Output file Q1Out.txt created\n");
	}
	else
		printf("Could not open file: %s", fileName);
	
}