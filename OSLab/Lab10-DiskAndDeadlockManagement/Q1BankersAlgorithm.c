#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int items[20];
    int front, rear, size;
} Queue;

int isFull(Queue q) {
    if (q.rear == q.size - 1) 
        return 1;
    return 0;
}

int isEmpty(Queue q) {
    if (q.front == -1) 
        return 1;
    return 0;
}

void insert(Queue * q, int n) {
    if(isFull(*q)) {
        printf("Error. Queue is full");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear = q->rear + 1;
    q->items[q->rear] = n;
}

int delete(Queue * q) {
    if(isEmpty(*q)) {
        printf("Error. Queue is empty");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    else
        q->front = q->front + 1;
    return item;
}

Queue createQueue() {
    Queue q;
    q.rear = -1, q.front = -1, q.size = 20;
    return q;
}

void calcAvailable(int resourcesCount, int processesCount, int * total, int * alloc[], int * available) {
    int allocated;
    for(int i = 0; i < resourcesCount; i++) {
        allocated = 0;
        for(int j = 0; j < processesCount; j++)
            allocated += alloc[j][i];
        available[i] = total[i] - allocated;
    }
}

void calcNeed(int resourcesCount, int processesCount, int * alloc[], int * max[], int * need[]) {
    for(int i = 0; i < processesCount; i++) {
        for(int j = 0; j < resourcesCount; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
}

void printNeed(int resourcesCount, int processesCount, int * need[]) {
    printf("Need:\n");
    for(int i = 0; i < processesCount; i++) {
        printf("Process %d: ", i);
        for(int j = 0; j < resourcesCount; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

int checkIfAvailable(int resourcesCount, int * need, int * available) {
    for(int i = 0; i < resourcesCount; i++) {
        if (need[i] > available[i])
            return 0;
    }
    return 1;
}

void main() {
    int processesCount, resourcesCount, finishedProcessesCount = 0;

    // printf("Enter number of processes, and number of resources ");
    // scanf("%d %d", &processesCount, &resourcesCount);

    // int * total = (int *) malloc(sizeof(int) * resourcesCount);

    // for(int i = 0; i < resourcesCount; i++) {
    //     printf("Enter total resources for resource: %d ", i);
    //     scanf("%d", &total[i]);
    // }

    // int ** alloc = (int **) malloc(sizeof(int *) * processesCount);

    // for(int i = 0; i < processesCount; i++) 
    //     alloc[i] = (int *) malloc(sizeof(int) * resourcesCount);

    // int ** max = (int **) malloc(sizeof(int *) * processesCount);

    // for(int i = 0; i < processesCount; i++) 
    //     max[i] = (int *) malloc(sizeof(int) * resourcesCount);

    // for(int i = 0; i < processesCount; i++) {
    //     for(int j = 0; j < resourcesCount; j++) {
    //         printf("Enter the allocation and max of process %d for resource %d ", i, j);
    //         scanf("%d %d", &alloc[i][j], &max[i][j]);
    //     }
    // }

    // int * available = (int *) malloc(sizeof(int) * resourcesCount);

    // To skip manual input
    processesCount = 5;
    resourcesCount = 3;
    int total[3] = {10, 5, 7};
    int allocation[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int ** alloc = (int **) malloc(sizeof(int *) * processesCount);

    for(int i = 0; i < processesCount; i++) {
        alloc[i] = (int *) malloc(sizeof(int) * resourcesCount);
        for(int j = 0; j < resourcesCount; j++)
            alloc[i][j] = allocation[i][j];
    }
    
    int maxResources[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};

    int ** max = (int **) malloc(sizeof(int *) * processesCount);

    for(int i = 0; i < processesCount; i++) {
        max[i] = (int *) malloc(sizeof(int) * resourcesCount);
        for(int j = 0; j < resourcesCount; j++)
            max[i][j] = maxResources[i][j];
    }
    int available[3];
    // End of hardcoded input

    int * finishedProcesses = (int *) calloc(processesCount, sizeof(int));

    int ** need = (int **) malloc(sizeof(int *) * processesCount);

    for(int i = 0; i < processesCount; i++) 
        need[i] = (int *) malloc(sizeof(int) * resourcesCount);
    
    Queue q = createQueue();

    calcAvailable(resourcesCount, processesCount, total, alloc, available);
    while(finishedProcessesCount < processesCount) {
        calcNeed(resourcesCount, processesCount, alloc, max, need);
        printNeed(resourcesCount, processesCount, need);

        for (int i = 0; i < processesCount; i++) {
            if (!finishedProcesses[i] && checkIfAvailable(resourcesCount, need[i], available)) {
                insert(&q, i);
            finishedProcesses[i] = 1;
            }
        }

        if (isEmpty(q)) {
            printf("Unsafe state\n");
            exit(1);
        }

        int processID = delete(&q);
        finishedProcessesCount += 1;
        printf("Process %d was executed\nNow resources available: ", processID);

        for (int i = 0; i < resourcesCount; i++) {
            available[i] += alloc[processID][i];
            printf("%d\t", available[i]);
            alloc[processID][i] = 0;
            max[processID][i] = 0;
        }
    }

    printf("\nAll processes finished\n");
    
}