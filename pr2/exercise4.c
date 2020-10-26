#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global_var;

void *increase_global_var() {
    for(int i = 0; i < 10000; i++){
        global_var++;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    global_var = 0;
    pthread_t *threads = calloc(2, sizeof(pthread_t));


    for(int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, (void *) increase_global_var, NULL);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Global var = %i", global_var);
    exit(EXIT_SUCCESS);
}