#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int reqID, arrivalTime, address;
} DiskAccessRequest;

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
    Queue q = createQueue();
    int input[4][3] = {{0, 5, 32}, {1, 2, 10}, {2, 6, 9}, {3, 10, 89}};
    int headAddress = 0;
    int reqCount = 4, finishedReqCount = 0, time = 0;
    DiskAccessRequest * requests = (DiskAccessRequest *) malloc(sizeof(DiskAccessRequest) * reqCount);

    for(int i = 0; i < reqCount; i++) {
        requests[i].reqID = input[i][0];
        requests[i].arrivalTime = input[i][1];
        requests[i].address = input[i][2];
    }

    // First Come First Serve
    int seek, totalSeek = 0;
    while(1) {
        for(int i = 0; i < reqCount; i++) {
            if (requests[i].arrivalTime == time) {
                seek = abs(headAddress - requests[i].address);
                totalSeek += seek;
                finishedReqCount += 1;
                printf("Request %d was granted. Seek: %d\n", i, seek);
            }
        }
        if (finishedReqCount == reqCount)
            break;
        time += 1;
    }

    printf("Average seek in FCFS: %d\n", (totalSeek / reqCount));

}