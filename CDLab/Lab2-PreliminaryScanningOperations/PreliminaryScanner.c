#include <stdio.h>

void main() {
	FILE * fptr1, * fptr2;
	char fileName[100];
	int lineStart = 1, insideQuotes = 0, insideDoubleQuotes = 0;
	printf("Enter filename to open for preprocessing ");
	scanf("%s", fileName);
	fptr1 = fopen(fileName, "r");
	if (fptr1 != NULL) {
		fptr2 = fopen("Out.txt", "w+");
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
				if (ch == '#' && !insideQuotes && !insideDoubleQuotes) {
					while (ch != EOF && (ch != '\n'))
						ch = fgetc(fptr1);
					lineStart = 1;
				}
				else if ((ch == '\t' || ch == ' ') && !insideQuotes && !insideDoubleQuotes) {
					fputc(' ', fptr2);
					while (ch != EOF && (ch == '\t' || ch == ' '))
						ch = fgetc(fptr1);
				}
				else if (ch == '/') {
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
		printf("Output file Out.txt created\n");
	}
	else
		printf("Could not open file: %s", fileName);
}