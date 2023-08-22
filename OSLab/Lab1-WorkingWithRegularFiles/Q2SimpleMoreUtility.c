#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main(int argsCount, char * args[]) {
    char ch, dummy;
    int i = 1, linesPrinted;

    if (argsCount > 1) {

        int inFileDesc = open(args[i], O_RDONLY);

        if (inFileDesc == -1) {
            printf("Error opening file %s. Exiting", args[i]);
            exit(0);
        }

        linesPrinted = 1;
        while(linesPrinted < 21) {
            printf("LINE %d : ", linesPrinted);
            while (read(inFileDesc, &ch, 1) == 1) {
                printf("%c", ch);
                if (ch == '\n') {
                    linesPrinted++;
                    if (linesPrinted == 21)
                        break;
                    printf("LINE %d : ", linesPrinted);
                }
            }
            if (linesPrinted < 21) {
                close(inFileDesc);

                i++;

                if (args[i] == NULL)
                    break;

                inFileDesc = open(args[i], O_RDONLY);

                if (inFileDesc == -1) {
                    printf("Error opening file %s. Exiting", args[i]);
                    exit(0);
                }
            }
            else {
                fflush(stdin);
                scanf("%c", &dummy);
                linesPrinted = 1;
            }
        }
    }
}