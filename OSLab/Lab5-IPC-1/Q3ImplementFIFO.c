#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char * items;
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

void insert(Queue * q,char ch) {
    if(isFull(*q)) {
        printf("Error. Queue is full");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear = q->rear + 1;
    q->items[q->rear] = ch;
}

char delete(Queue * q) {
    if(isEmpty(*q)) {
        printf("Error. Queue is empty");
        return EOF;
    }
    char item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    else {
        q->front = q->front + 1;
    }
    return item;
}

void main() {
    Queue q;
    q.items = (char *) malloc(100 * sizeof(char));
    q.front = -1;
    q.rear = -1;
    q.size = 100;

    int inp = 0;

    printf("Enter 1 for writing, 0 for reading (1 char at a time). Enter -1 to exit\n");


    while (inp != -1) {
        printf("Enter input ");
        scanf("%d", &inp);
        if (inp == 0) {
            char ch = delete(&q);
            printf("Read: %c\n", ch);
        }
        else if (inp == 1) {
            char ch;
            printf("Enter character to write ");
            scanf(" %c", &ch);
            insert(&q, ch);
            printf("Wrote %c\n", ch);
        }
    }
}