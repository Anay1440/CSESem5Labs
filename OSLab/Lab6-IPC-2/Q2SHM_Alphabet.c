#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>

typedef struct shared {
    int turn;
    char ch;
} Shared;

void main() {
    void * sharedMemory = (void *) 0;
    Shared *data;
    int shmID = shmget(1440, sizeof(Shared), 0666 | IPC_CREAT);
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
    data->turn = 1;
    if (fork() == 0) { // Child Process (Turn == 0)

        while(data -> turn == 1)
            sleep(1);

        data->ch = data->ch + 1;

        data->turn = 1;

    }
    else { // Parent Process (Turn == 1)

        char ch;
        printf("Enter a character ");
        scanf("%c", &ch);
        data->ch = ch;

        data->turn = 0;

        while (data->turn == 0) 
            sleep(1);

        printf("Received character: %c\n", data->ch);

    }

    if (shmdt(sharedMemory) == -1) {
        printf("Shared Memory deletion failed\n");
        exit(1);
    }
}