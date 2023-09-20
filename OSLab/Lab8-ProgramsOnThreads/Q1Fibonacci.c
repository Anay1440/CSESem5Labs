#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void * fibThread(void * param) {
    int n = (long) param;
    int * arr = (int *) malloc(n * sizeof(int));
    int a = 0, b = 1, c;
    arr[0] = a;
    arr[1] = b;
    for (int i = 2; i < n; i++) {
        c = a + b;
        arr[i] = c;
        a = b;
        b = c;
    }
    return (void *) arr;
}

void main() {
    int n;
    printf("Enter number of fibonacci numbers to be generated ");
    scanf("%d", &n);
    int * arr = (int *) malloc(n * sizeof(int));
    pthread_t fibThreadID;
    pthread_create(&fibThreadID, 0, &fibThread, (void *)(long) n);
    pthread_join(fibThreadID, (void**)&arr);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}