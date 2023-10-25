#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t mutex, start;
int processesCount, resourcesCount, finishedProcessesCount = 0, *total, **alloc, **max, *available;

void calcAvailable(int resourcesCount, int processesCount, int * total, int * alloc[], int * available) {
    int allocated;
    for(int i = 0; i < resourcesCount; i++) {
        allocated = 0;
        for(int j = 0; j < processesCount; j++)
            allocated += alloc[j][i];
        available[i] = total[i] - allocated;
    }
}

int checkIfAvailable(int resourcesCount, int * need, int * available) {
    for(int i = 0; i < resourcesCount; i++) {
        if (need[i] > available[i])
            return 0;
    }
    return 1;
}

void * processThread(void * arg) {
    int processID = (long) arg;
    int * need = (int *) malloc(sizeof(int) * resourcesCount);
    for (int i = 0; i < resourcesCount; i++)
        need[i] = max[processID][i] - alloc[processID][i];
    while(!checkIfAvailable(resourcesCount, need, available));
    sem_wait(&mutex);
    printf("Process %d was executed\nNow resources available: ", processID);
    for (int i = 0; i < resourcesCount; i++) {
        available[i] += alloc[processID][i];
        printf("%d\t", available[i]);
        alloc[processID][i] = 0;
        max[processID][i] = 0;
        finishedProcessesCount += 1;
    }
    printf("\n");
    sem_post(&mutex);
}

void main() {
    sem_init(&mutex, 0, 1);

    processesCount = 5;
    resourcesCount = 3;
    int totalResources[3] = {10, 5, 7};
    total = (int *) malloc(sizeof(int) * resourcesCount);
    for(int i = 0; i < resourcesCount; i++)
        total[i] = totalResources[i];

    int allocation[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    alloc = (int **) malloc(sizeof(int *) * processesCount);

    for(int i = 0; i < processesCount; i++) {
        alloc[i] = (int *) malloc(sizeof(int) * resourcesCount);
        for(int j = 0; j < resourcesCount; j++)
            alloc[i][j] = allocation[i][j];
    }
    
    int maxResources[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};

    max = (int **) malloc(sizeof(int *) * processesCount);

    for(int i = 0; i < processesCount; i++) {
        max[i] = (int *) malloc(sizeof(int) * resourcesCount);
        for(int j = 0; j < resourcesCount; j++)
            max[i][j] = maxResources[i][j];
    }

    available = (int *) malloc(sizeof(int) * resourcesCount);
    calcAvailable(resourcesCount, processesCount, total, alloc, available);

    pthread_t * threadIDs = (pthread_t *) malloc(sizeof(pthread_t) * processesCount);

    for(int i = 0; i < processesCount; i++)
        pthread_create(&threadIDs[i], 0, &processThread, (void *) (long) i);

    for(int i = 0; i < processesCount; i++)
        pthread_join(threadIDs[i], NULL);

    printf("\nAll processes finished\n");
}
