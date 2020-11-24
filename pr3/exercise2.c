#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int pair = 0;
int odd = 0;

pthread_mutex_t semaphore;

void *returnPairOdd(void * index) {
    int* sumValue = calloc(sizeof(int), 1);
    int* identifier = (int*)index;
    if(sumValue == NULL) {
        perror("[!]Error reserving memory for sumValue\n");
        exit(EXIT_FAILURE);
    }
    int randomValue;
    for(int i = 0; i < 5; i++) {
        randomValue = rand()%11;
        *sumValue = *sumValue + randomValue;
    }
    if( (*identifier) % 2 == 0) {
        pthread_mutex_lock(&semaphore);
        printf("Thread %i added %i to pair variable \n", *identifier, *sumValue);
        pair = pair + *sumValue;
        pthread_mutex_unlock(&semaphore);
    } else {
        pthread_mutex_lock(&semaphore);
        printf("Thread %i added %i to odd variable \n", *identifier, *sumValue);
        odd = odd + *sumValue;
        pthread_mutex_unlock(&semaphore);
    }
    pthread_exit((void *) sumValue);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        perror("[!]Error in arguments. Usage: ./a.out threads\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&semaphore, 0);
    srand(time(NULL));
    int nThreads = atoi(argv[1]);
    pthread_t threads[nThreads];
    void *returnValues[nThreads];
    int index[nThreads];

    for(int i = 0; i < nThreads; i++) {
        index[i] = i + 1;
        pthread_create(&threads[i], NULL, returnPairOdd, (void *)&index[i]);
    }

    for(int i= 0; i < nThreads; i++) {
        pthread_join(threads[i], &returnValues[i]);
    }

    int sumPair = 0;
    int sumOdd = 0;

    for(int i = 1; i < nThreads+1; i++) {
        if(i % 2 == 0) {
            sumPair = sumPair + *((int *) returnValues[i-1]);
        } else {
            sumOdd = sumOdd + *((int *) returnValues[i-1]);
        }
    }

    printf("Pair value: %i, Odd value: %i \n", sumPair, sumOdd);
    printf("Pair var: %i, Odd var: %i\n", pair, odd);
    exit(EXIT_SUCCESS);
}