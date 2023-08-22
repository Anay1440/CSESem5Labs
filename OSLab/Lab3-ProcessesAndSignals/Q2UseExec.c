#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
    int pid = fork();
    if (pid < 0) {
        printf("Error\n");
        exit(1);
    }
    else if (pid == 0) {
        execlp("./Q1", "Q1", NULL);
    }
    else {
        wait(NULL);
        printf("This is from the parent\n");
    }
}