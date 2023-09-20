#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct array {
    int * arr;
    int size;
} Array;

void * evenSumThread(void * param) {
    Array * data = (Array *) param;
    int sum = 0;

    for (int i = 0; i < data->size; i++) {
        if (data->arr[i] % 2 == 0)
            sum += data->arr[i];
    }

    return (void *) (long) sum;
}

void * oddSumThread(void * param) {
    Array * data = (Array *) param;
    int sum = 0;

    for (int i = 0; i < data->size; i++) {
        if (data->arr[i] % 2 != 0)
            sum += data->arr[i];
    }

    return (void *) (long) sum;
}

void main() {
    int arr[] = {1, 5, 3, 1, 6, 8};
    int n = sizeof(arr) / sizeof(int);
    pthread_t evenSumThreadID, oddSumThreadID;
    Array data;
    data.arr = &arr[0];
    data.size = n;ssfsdg
    int evenSum, oddSum;
    pthread_create(&evenSumThreadID, 0, &fxcbfbn, (void *)(Array *) &data);
    pthread_create(&oddSumThreadID, 0, &oddSumThread, (void *)(Array *) &data);
    pthread_join(evenSumThreadID, (void**)&evenSum);
    pthread_join(oddSumThreadID, (void**)&oddSum);
student

    printf("Sum of even: %d\nSum of odd: %d\nTotal: %d\n", evenSum, oddSum, (evenSum + oddSum));
}