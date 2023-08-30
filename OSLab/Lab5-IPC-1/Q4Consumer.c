#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/fifo"

void main() {
    int res, pid, n;
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

    while(1) {
        read(pipeID, &n, sizeof(int));
        if (n == 0) {
            printf("Consumer could not consume because no goods are available\n");
            write(pipeID, &n, sizeof(int));
        }
        else if (n > 0) {
            n -= 1;
            write(pipeID, &n, sizeof(int));
            printf("Consumer consumed goods. Total number of goods now: %d\n", n);
        }
        sleep(1);
    }
    close(pipeID);
}