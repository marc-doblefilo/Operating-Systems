#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define N 4

void *partial_addition(){
    float *fn = calloc(1, sizeof(float));
    if (fn == NULL) {
        perror("Error allocating memory to the partial addition");
        exit(EXIT_FAILURE);
    }
    *fn = (float)rand() + (float)rand();
    printf("Child content: %f\n", *fn);
    pthread_exit( (void *) fn);
    }


int main(int argc, char* argv[]) {
    float result = 0.0;

    pthread_t *threads = calloc(N, sizeof(float));
    if(threads == NULL) {
        perror("Error making a thread.");
        exit(EXIT_FAILURE);
    }

    float **partial_array = calloc(N, sizeof(float*));

    if (partial_array == NULL) {
        perror("Error allocate memory for partial.");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, (void *) partial_addition, NULL);
    }

    for(int i = 0; i < N; i++) {
        pthread_join(threads[i], (void **) &partial_array[i]);
    }

    for(int i = 0; i < N; i++) {
        result = result + *partial_array[i];
    }

    printf("%f\n", result);
    printf("Threads ended correctly. \n");

    free(*partial_array);
    free(threads);
    exit(EXIT_SUCCESS);
}