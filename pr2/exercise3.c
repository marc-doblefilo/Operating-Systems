#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void sum_vector(void *received_vector) {
    int * sum = calloc(1, sizeof(int));
    *sum = 0;
    int *vector = (int *)received_vector;
    for(int i = 0; i < 5; i++) {
        *sum = *sum + vector[i];
    }

    printf("%i\n", *sum);
    pthread_exit( (void *) sum);
}

int main(int argc, char **argv) {

    if(argc < 2 || argc > 2) {
        perror("Error in arguments. Usage: ./a.out 2");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int *vector = calloc(10, sizeof(int));
    int number_threads = atoi(argv[1]);
    int *v = calloc(number_threads, sizeof(int));
    int aux = 0;
    int **sum_vectors = calloc(number_threads, sizeof(int*));

    for(int i = 0; i < 10; i++) {
        vector[i] = rand() % 8 + 1;
    }

    pthread_t *threads = calloc(number_threads, sizeof(pthread_t));

    for(int i = 0; i < number_threads; i++) {
        if(number_threads == 2) {
            for(int j = 0; j < 5; j++) {
                v[j] = vector[j+aux];
                printf("v[%i] = %i \n", j, v[j]);
            }
            pthread_create(&threads[i], NULL, (void *) sum_vector, (void *) v);
            pthread_join(threads[i], (void **) &sum_vectors[i]);
            aux = 5;
        } else if(number_threads == 5) {
            for(int j = 0; j < 2; j++) {
                v[j] = vector[j+aux];
                printf("v[%i] = %i\n", j, v[j]);
            }
            pthread_create(&threads[i], NULL, (void *) sum_vector, (void *) v);
            pthread_join(threads[i], (void **) &sum_vectors[i]);
            aux = aux + 2;
        }
    }

    for(int i = 0; i < number_threads; i++) {
        printf("Thread %i sum = %i\n", i, *sum_vectors[i]);
    }


    free(vector);
    free(v);
    exit(EXIT_SUCCESS);
}