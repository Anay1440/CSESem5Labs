#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readCount = 0;
sem_t mutex, wrt;

void * writer(void * arg) {
    while (1) {
        sem_wait(&wrt);
        printf("Writing started\n");
        sleep(2);
        printf("Writing ended\n");
        sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
    }
}

void * reader(void * arg) {
    while (1) {
        sem_wait(&mutex);
        if (readCount == 0)
            sem_wait(&wrt);
        readCount++;
        sem_post(&mutex);
        printf("Reading started. Readcount: %d\n", readCount);
        sleep(1);
        printf("Reading ended\n");
        sem_wait(&mutex);
        readCount--;
        if (readCount == 0)
            sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
    }
}

void main() {

    /*
        How to compile
        $ gcc -pthread -o Q2 Q2ReaderWriter.c
    */

    pthread_t writerThreadID, reader1ThreadID, reader2ThreadID;
    sem_init(&mutex, 0, 0);
    sem_init(&wrt, 0, 1);
    pthread_create(&writerThreadID, NULL, writer, NULL);
    pthread_create(&reader1ThreadID, NULL, reader, NULL);
    pthread_create(&reader2ThreadID, NULL, reader, NULL);
    pthread_join(writerThreadID, NULL);
    pthread_join(reader1ThreadID, NULL);
    pthread_join(reader2ThreadID, NULL);
}