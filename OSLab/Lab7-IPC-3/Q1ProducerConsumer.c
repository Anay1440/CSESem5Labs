#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int goods[10], front, rear;
sem_t mutex, start, empty;

void * produce (void * arg) {
    for (int i = 0; i < 100; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("Produced item %d\n", i);
        goods[(++rear) % 10] = i;
        sem_post(&start);
        sem_post(&mutex);
        // sleep(1);
    }
}

void * consume (void * arg) {
    int item;
    for (int i = 0; i < 100; i++) {
        sem_wait(&start);
        sem_wait(&mutex);
        item = goods[(++front) % 10];
        printf("Consumed item %d\n", item);
        sem_post(&mutex);
        sem_post(&empty);
        // sleep(2);
    }
}

void main() {

    /*
        How to compile
        $ gcc -pthread -o Q1 Q1ProducerConsumer.c
    */

    pthread_t producerThreadID, consumerThreadID;
    sem_init(&mutex, 0, 1);
    sem_init(&start, 0, 0);
    sem_init(&empty, 0, 10);
    pthread_create(&producerThreadID, NULL, produce, NULL);
    pthread_create(&consumerThreadID, NULL, consume, NULL);
    pthread_join(producerThreadID, NULL);
    pthread_join(consumerThreadID, NULL);
}