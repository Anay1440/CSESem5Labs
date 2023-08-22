#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main() {
    char ch, st[100];
    int inFileDesc, i = 0, lineStart = -1, comparInd = 0, substrlen, lineNo = 1;

    printf("Enter substring to grep ");
    scanf("%s", st);
    substrlen = strlen(st);

    inFileDesc = open("Text.txt", O_RDONLY);

    while (read(inFileDesc, &ch, 1) == 1) {
        if (ch == '\n') {
            lineStart = i;
            lineNo++;
        }
        else if (ch == st[comparInd]) {
            if (comparInd == substrlen - 1) {
                int seek = lseek(inFileDesc, lineStart + 1, SEEK_SET);
                int lineLen = 0;
                printf("LINE %d : ", lineNo);
                while (read(inFileDesc, &ch, 1) == 1) {
                    printf("%c", ch);
                    lineLen++;
                    if (ch == '\n')
                        break;
                }
                i = lineStart + lineLen;
                lineStart = i;
                lineNo++;
                comparInd = 0;
            }
            else
                comparInd++;
        }
        else
            comparInd = 0;
        i++;
    }
}