#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct array {
    int * arr;
    int size;
} Array;

void * nonNegSumThread(void * param) {
    Array * data = (Array *) param;
    int sum = 0, j;
    for (int i = 0; i < data->size; i++) {
        j = data->arr[i];
        if (j > 0)
            sum += j;
    }
    return (void *) (long) sum;
}

void main() {
    int arr[] = {1, 5, -1, 2, -9, 6};
    int n = sizeof(arr) / sizeof(int);
    pthread_t nonNegSumThreadID;
    int nonNegSum;
    Array data;
    data.arr = &arr[0];
    data.size = n;
    pthread_create(&nonNegSumThreadID, 0, &nonNegSumThread, (void *)(Array *) &data);
    pthread_join(nonNegSumThreadID, (void**)&nonNegSum);
    printf("Sum of non negative numbers: %d\n", nonNegSum);
}