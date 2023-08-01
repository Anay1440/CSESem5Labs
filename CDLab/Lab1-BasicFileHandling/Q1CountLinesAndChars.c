#include <stdio.h>

void main() {
	FILE * fptr;
	char fileName[100];
	printf("Enter filename to open for reading ");
	scanf("%s", fileName);
	fptr = fopen(fileName, "r");
	if (fptr != NULL) {
		int charCount = 0, lineCount = 0;
		char ch = fgetc(fptr);
		while(ch != EOF) {
			if (ch == '\n')
				lineCount++;
			else
				charCount++;
			ch = fgetc(fptr);
		}
		fclose(fptr);
		printf("Number of lines: %d\nNumber of characters: %d\n", lineCount + 1, charCount);
	}
	else 
		printf("Could not open file: %s\n", fileName);
}