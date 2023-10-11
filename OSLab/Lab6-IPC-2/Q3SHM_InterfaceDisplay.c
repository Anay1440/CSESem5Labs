#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define QUEUESIZE 10

typedef struct shared {
    int front, rear;
    char queue[QUEUESIZE][20];
} Shared;

void main() {
    void * sharedMemory = (void *) 0;
    Shared *data;
    int shmID = shmget(1441, sizeof(Shared), 0666 | IPC_CREAT);
    if (shmID == -1) {
        printf("Shared memory creation failed\n");
        exit(1);
    }
    sharedMemory = shmat(shmID, (void *)0, 0);
    if (sharedMemory == (void *) -1) {
        printf("Shared memory attachment failed\n");
        exit(1);
    }
    printf("Memory attached at %X\n", (int) sharedMemory);
    data = (Shared *) sharedMemory;
    data->front = -1;
    data->rear = -1;
    if (fork() == 0) { // Child Process (Display)

        while(1) {

            while(data->front == data->rear)
                sleep(1);

            while(data->front != data->rear) {
                data->front = (data->front + 1) % QUEUESIZE;
                printf("Display: %s\n", data->queue[data->front]);
            }
        }

    }
    else { // Parent Process (Interface)

        while(1) {
            char str[20];
            printf("Enter string ");
            scanf("%s", str);
            data->rear = (data->rear + 1) % QUEUESIZE;
            strcpy(data->queue[data->rear], str);
            fflush(stdin);
        }
    }

    if (shmdt(sharedMemory) == -1) {
        printf("Shared Memory deletion failed\n");
        exit(1);
    }
}