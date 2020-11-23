#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

pthread_mutex_t semaphore;

typedef struct {
    int *models;
    int size;
} buffer;

void* supply(void * params) {
    buffer * shBuffer = (buffer*)params;
    int model = rand()%shBuffer->size;
    int increments = rand()%10+1;

    printf("SUPPLIER: supplies %i of tshirt %i \n", increments, model);
    pthread_mutex_lock(&semaphore);
    shBuffer->models[model] = shBuffer->models[model] + increments;
    pthread_mutex_unlock(&semaphore);
    pthread_exit(NULL);
}

void* buy(void * params) {
    buffer * shBuffer = (buffer*)params;
    int model = rand()%shBuffer->size;
    int buys = rand()%10+1;

    pthread_mutex_lock(&semaphore);
    if(buys > shBuffer->models[model]) {
        shBuffer->models[model] = shBuffer->models[model] - shBuffer->models[model];
        printf("CLIENT: tried %i, but it got %i of tshirt %i OUT OF STOCK\n", buys, shBuffer->models[model], model);
    } else {
        shBuffer->models[model] = shBuffer->models[model] - buys;
        printf("CLIENT: buyed %i of tshirt %i \n", buys, model);
    }
    pthread_mutex_unlock(&semaphore);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    if(argc != 3) {
        perror("[!] Error. Usage: ./a.out suppliers clients \n");
        return(EXIT_FAILURE);
    }

    srand(time(NULL));
    pthread_mutex_init(&semaphore, 0);
    int numberSuppliers = atoi(argv[1]);
    int numberClients = atoi(argv[2]);

    int *bufferEmpty = calloc(sizeof(int), numberSuppliers);
    if (bufferEmpty == NULL) {
        perror("[!] Error creating a empty buffer. \n");
        return(EXIT_FAILURE);
    }
    buffer bufferShared;
    bufferShared.models = bufferEmpty;
    bufferShared.size = numberSuppliers;

    for(int i = 0; i < numberSuppliers; i++) {
        bufferShared.models[i] = rand()%100+1;
    }

    pthread_t Suppliers[numberSuppliers];
    pthread_t Clients[numberClients];

    for(int i = 0; i < numberSuppliers; i++) {
        if(pthread_create(&Suppliers[i], NULL, supply, (void *) &bufferShared) != 0) {
            perror("[!] Error creating suppliers threads \n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < numberClients; i++) {
        if(pthread_create(&Clients[i], NULL, buy, (void *) &bufferShared) != 0) {
            perror("[!] Error creating clients threads \n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < numberSuppliers; i++) {
        if(pthread_join(Suppliers[i], NULL) != 0) {
            perror("Error recollecting suppliers threads \n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < numberClients; i++) {
        if(pthread_join(Clients[i], NULL) != 0) {
            perror("[!] Error recollecting clients threads \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n - END OF BUFFER - \n");
    for(int i = 0; i < numberSuppliers; i++) {
        printf("%i\t", bufferShared.models[i]);
    }
    return(EXIT_SUCCESS);
}