#include <stdio.h>

void main() {
	FILE * fptr1, * fptr2, * fptr3;
	char fileName1[100], fileName2[100], fileName3[100];
	printf("Enter first filename to open for reading ");
	scanf("%s", fileName1);
	printf("Enter second filename to open for reading ");
	scanf("%s", fileName2);
	printf("Enter filename to open for writing ");
	scanf("%s", fileName3);
	fptr1 = fopen(fileName1, "r");
	fptr2 = fopen(fileName2, "r");
	fptr3 = fopen(fileName3, "w+");

	if ((fptr1 != NULL) && (fptr2 != NULL)) {
		char ch1 = fgetc(fptr1), ch2;
		int flag = 1;
		while (ch1 != EOF && ch2 != EOF) {
			if (flag) {
				while (ch1 != EOF && ch1 != '\n') {
					fputc(ch1, fptr3);
					ch1 = fgetc(fptr1);
				}
				fputc('\n', fptr3);
				ch2 = fgetc(fptr2);
				flag = 0;
			}
			else {
				while (ch2 != EOF && ch2 != '\n') {
					fputc(ch2, fptr3);
					ch2 = fgetc(fptr2);
				}
				fputc('\n', fptr3);
				ch1 = fgetc(fptr1);
				flag = 1;
			}
		}
		while (ch1 != EOF) {
			fputc(ch1, fptr3);
			ch1 = fgetc(fptr1);
		}
		while (ch2 != EOF) {
			fputc(ch2, fptr3);
			ch2 = fgetc(fptr2);
		}
		printf("Files merged\n");
		fclose(fptr1);
		fclose(fptr2);
		fclose(fptr3);
	}
	else {
		if (fptr1 == NULL)
			printf("Could not open file: %s", fileName1);
		else
			printf("Could not open file: %s", fileName2);
	}
}