#include <stdio.h>

int preliminaryScanner(char * fileName) {
    int lineStart = 1, insideQuotes = 0, insideDoubleQuotes = 0, insideFunction = 0;
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
				if (ch == '#' && !insideQuotes && !insideDoubleQuotes && insideFunction == 0) {
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
                    if (ch == '{')
                        insideFunction = 1;
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