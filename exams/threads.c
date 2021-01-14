#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

int par = 0;
int impar = 0;
pthread_mutex_t semaphore;

void *thread_value(void* id) {
    int* index = (int*) id;
    int* sumValue = calloc(sizeof(int), 1);
    if(sumValue == NULL) {
        perror("Error allocating memory in thread. \n");
        exit(EXIT_FAILURE);
    }
    *sumValue = 0;
    for(int i = 0; i < 100; i++) {
        int random = rand()%11;
        *sumValue = *sumValue + random;
    }
    if(*index % 2 == 0) {
        pthread_mutex_lock(&semaphore);
        par += *sumValue;
        printf("Thread %i has a value of: %i \n", *index, *sumValue);
        pthread_mutex_unlock(&semaphore);
    } else {
        pthread_mutex_lock(&semaphore);
        impar += *sumValue;
        printf("Thread %i has a value of: %i \n", *index, *sumValue);
        pthread_mutex_unlock(&semaphore);
    }

    pthread_exit((void *) sumValue);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        perror("Error in usage. Usage: ./a.out {threads}. \n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&semaphore, 0);
    srand(time(NULL));
    int numberThreads = atoi(argv[1]);
    pthread_t threads[numberThreads];
    void *returnValues[numberThreads];
    int index[numberThreads];

    for(int i = 0; i < numberThreads; i++) {
        index[i] = i+1;
        pthread_create(&threads[i], NULL, thread_value, (void *)&index[i]);
    }

    for(int i = 0; i < numberThreads; i++) {
        pthread_join(threads[i], &returnValues[i]);
    }

    int sumPar = 0;
    int sumImpar = 0;

    for(int i = 1; i < numberThreads+1; i++) {
        if(i % 2 == 0) {
            sumPar += *(int *) returnValues[i-1];
        } else {
            sumImpar += *((int *)returnValues[i-1]);
        }
    }

    printf("GLOBALS: Par: %i Impar: %i \n", par, impar);
    printf("THREADS JOIN: Par: %i Impar: %i \n", sumPar, sumImpar);
    
    exit(EXIT_SUCCESS);
}