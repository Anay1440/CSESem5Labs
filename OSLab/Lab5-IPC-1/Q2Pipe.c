#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

void main() {
    int pipeIDs[2], pid, res;
    res = pipe(pipeIDs);
    if (res == -1) {
        printf("Error opening piples\n");
        exit(1);
    }
    pid = fork();
    if (pid < 0) {
        printf("Error\n");
        exit(1);
    }
    else if (pid == 0) { // Child reads from pipe
        close(pipeIDs[1]); // Close unused write end
        char ch;
        while (read(pipeIDs[0], &ch, 1) > 0) {
            printf("%c", ch);
        }
        printf("\n");
        close(pipeIDs[0]);
        exit(0);
    }
    else {
        close(pipeIDs[0]); // Close unused read end
        write(pipeIDs[1], "Hello World", strlen("Hello World"));
        close(pipeIDs[1]);
        wait(NULL);
    }
}