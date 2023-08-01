#include <stdio.h>

void main() {
	FILE * fptr1, * fptr2;
	char fileName1[100], fileName2[100];
	printf("Enter filename to open for reading ");
	scanf("%s", fileName1);
	printf("Enter filename to open for writing ");
	scanf("%s", fileName2);
	fptr1 = fopen(fileName1, "r");
	if (fptr1 != NULL) {
		fptr2 = fopen(fileName2, "w+");
		char ch;
		int i = -1;
		while (ftell(fptr1) != 1) {
			fseek(fptr1, i--, SEEK_END);
			ch = fgetc(fptr1);
			fputc(ch, fptr2);
		}
		printf("%s contains reverse of %s\n", fileName2, fileName1);
		fseek(fptr1, 0, SEEK_END);
		printf("Size of %s: %ld bytes\n", fileName1, ftell(fptr1));
		fclose(fptr1);
		fclose(fptr2);
	}
	else {
		printf("Could not open file: %s", fileName1);
	}
}