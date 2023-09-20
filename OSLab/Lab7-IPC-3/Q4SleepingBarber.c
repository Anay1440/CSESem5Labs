#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int waitCount = 0;
sem_t mutex, start;

void * barber(void * arg) {
    while (1) {
        sem_wait(&start);
        sem_wait(&mutex);
        waitCount--;
        sem_post(&mutex);
        printf("Barber woke up. Wait count: %d\n", waitCount);
        sleep(1);
        printf("Barber going to sleep. Wait count: %d\n", waitCount);
        sleep(2);
    }
}

void * customer(void * arg) {
    while (1) {
        sem_wait(&mutex);
        waitCount++;
        printf("New customer. Wait count: %d\n", waitCount);
        sem_post(&start);
        sem_post(&mutex);
        sleep(1);
    }
}

void main() {

    /*
        How to compile
        $ gcc -pthread -o Q4 Q4SleepingBarber.c
    */

    pthread_t barberThreadID, customer1ThreadID, customer2ThreadID;
    sem_init(&mutex, 0, 1);
    sem_init(&start, 0, 0);
    pthread_create(&barberThreadID, NULL, barber, NULL);
    pthread_create(&customer1ThreadID, NULL, customer, NULL);
    // pthread_create(&customer2ThreadID, NULL, customer, NULL);
    pthread_join(barberThreadID, NULL);
    pthread_join(customer1ThreadID, NULL);
    // pthread_join(customer2ThreadID, NULL);
}