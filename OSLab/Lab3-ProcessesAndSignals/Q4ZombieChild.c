#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void main() {

    /*
        How to execute. 
        $ gcc -o Q4 Q4ZombieChild.c
        $ ./Q4 &
        (while the code is still running, in the same terminal)
        $ ps
    */

    int pid = fork();
    if (pid < 0) {
        printf("Error\n");
        exit(1);
    }
    else if (pid == 0) {
        exit(0);
    }
    else {
        for (int i = 0; i < 10; i++) {
            printf("This is from the parent\n");
            sleep(1);
        }
    }
}