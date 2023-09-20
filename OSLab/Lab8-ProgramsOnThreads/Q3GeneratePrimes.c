#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct array {
    int * arr;
    int size;
} Array;

void * primeNumThread(void * param) {
    Array * data = (Array *) param;
    int * arr = (int *) malloc(((data->arr[1]) - (data->arr[0]) + 1) * sizeof(int));
    int ind = 0;

    for (int i = data->arr[0]; i <= data->arr[1]; i++) {
        int isPrime = 1;
        for (int j = 2; j < i; j++) {
            if (i%j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
            arr[ind++] = i;
    }

    arr = (int *) realloc(arr, (ind) * sizeof(int));

    data->arr = arr;
    data->size = ind;

}

void main() {
    int n1 = 10, n2 = 80;
    pthread_t primeNumThreadID;
    Array data;
    data.arr = (int *) malloc(2 * sizeof(int));
    data.arr[0] = n1;
    data.arr[1] = n2;
    data.size = 2;
    pthread_create(&primeNumThreadID, 0, &primeNumThread, (void *)(Array *) &data);
    pthread_join(primeNumThreadID, NULL);

    printf("Prime numbers: \n");
    for (int i = 0; i < data.size; i++) {
        printf("%d ", data.arr[i]);
    }
}