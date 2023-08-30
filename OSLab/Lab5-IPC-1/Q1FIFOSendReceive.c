#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#define FIFO_NAME "/tmp/fifo"

void main() {
    int res, pid;
    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777); // permission: read, write, and execute for all users
        if (res != 0) {
            printf("Could not create FIFO %s\n", FIFO_NAME);
            exit(1);
        }
    }
    int pipeID = open(FIFO_NAME, O_RDWR);
    if (pipeID == -1) {
        printf("Failed to open pipe\n");
        exit(1);
    }
    pid = fork();
    if (pid < 0) {
        printf("Error\n");
        exit(1);
    }
    else if (pid == 0) {
        int arr[4] = {1,2,5,9};
        write(pipeID, arr, 4 * sizeof(int));
        exit(0);
    }
    else {
        wait(NULL);
        int arr[4];
        read(pipeID, arr, 4 * sizeof(int));
        printf("Integers received: %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
    }
    close(pipeID);
}