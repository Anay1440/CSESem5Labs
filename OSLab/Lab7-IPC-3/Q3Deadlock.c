#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, shared;

void * thread1(void * arg) {
    while (1) {
        sem_wait(&mutex);
        sem_wait(&shared);
        printf("Thread 1\n");
        sleep(1);
        sem_post(&mutex);
    }
}

void * thread2(void * arg) {
    while (1) {
        sem_wait(&mutex);
        printf("Thread 2\n");
        sleep(1);
        sem_post(&shared);
        sem_post(&mutex);
    }
}

void main() {

    /*
        How to compile
        $ gcc -pthread -o Q3 Q3Deadlock.c
    */

    pthread_t thread1ID, thread2ID;
    sem_init(&mutex, 0, 1);
    sem_init(&shared, 0, 0);
    pthread_create(&thread1ID, NULL, thread1, NULL);
    pthread_create(&thread2ID, NULL, thread2, NULL);
    pthread_join(thread1ID, NULL);
    pthread_join(thread2ID, NULL);
}