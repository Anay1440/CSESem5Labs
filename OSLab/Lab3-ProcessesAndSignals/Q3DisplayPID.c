#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
    int pid, pidChild;

    pidChild = fork();

    if (pidChild < 0) {
        printf("Error\n");
        exit(1);
    }
    else if (pidChild == 0) {
        printf("This is from the child. PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else {
        wait(NULL);
        printf("This is from the parent. PID: %d, Child PID: %d\n", getpid(), pidChild);
    }

}