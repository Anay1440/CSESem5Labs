#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void main() {
    Queue queue1 = createQueue(); // 4ms quantum
    Queue queue2 = createQueue(); // 8ms quantum
    Queue queue3 = createQueue(); // 16ms quantum
    Queue queues[3] = {queue1, queue2, queue3};

    int processesTimes[4] = {6, 3, 32, 24};
    int processesPriorities[4] = {1, 1, 3, 2};
    int processesCount = 4;

    for (int i = 0; i < processesCount; i++) {
        if (processesPriorities[i] == 1)
            insert(&queue1, i + 1);
        if (processesPriorities[i] == 2)
            insert(&queue2, i + 1);
        if (processesPriorities[i] == 3)
            insert(&queue3, i + 1);
    }

    while (!isEmpty(queue1) || !isEmpty(queue2) || !isEmpty(queue3)) {
        while (!isEmpty(queue1)) {
            int processID = delete(&queue1) - 1;
            if (processID < 0) break;
            processesTimes[processID] -= 4;
            if (processesTimes[processID] <= 0)
                printf("Process %d was given 4ms to execute. It finished execution.\n", processID);
            else {
                printf("Process %d was given 4ms to execute. Remaining time: %d. It has been put into queue2\n", processID, processesTimes[processID]);
                insert(&queue2, processID + 1);
            }
            sleep(1);
        }
        while (!isEmpty(queue2)) {
            int processID = delete(&queue2) - 1;
            if (processID < 0) break;
            processesTimes[processID] -= 8;
            if (processesTimes[processID] <= 0)
                printf("Process %d was given 8ms to execute. It finished execution.\n", processID);
            else {
                printf("Process %d was given 8ms to execute. Remaining time: %d. It has been put into queue3\n", processID, processesTimes[processID]);
                insert(&queue3, processID + 1);
            }
            sleep(1);
        }
        while (!isEmpty(queue3)) {
            int processID = delete(&queue3) - 1;
            if (processID < 0) break;
            processesTimes[processID] -= 16;
            if (processesTimes[processID] <= 0)
                printf("Process %d was given 16ms to execute. It finished execution.\n", processID);
            else {
                printf("Process %d was given 16ms to execute. Remaining time: %d. It has been put into queue3\n", processID, processesTimes[processID]);
                insert(&queue3, processID + 1);
            }
            sleep(1);
        }
    }
}