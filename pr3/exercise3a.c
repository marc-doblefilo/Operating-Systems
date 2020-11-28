#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define maxItems 10
#define bufferSize 5

sem_t stock;
pthread_mutex_t sem;
sem_t size;
int buffer[bufferSize];
int iterationsIn = 0;
int iterationsOut = 0;

sem_t s;
sem_t e;
int in = 0;
int out = 0;
int buffer[bufferSize];
pthread_mutex_t sem;

void *producer(void *number)
{   
    int item;
    for(int i = 0; i < maxItems; i++) {
        item = rand();
        sem_wait(&s);
        pthread_mutex_lock(&sem);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)number),buffer[in],in);
        in = (in+1)%bufferSize;
        pthread_mutex_unlock(&sem);
        sem_post(&e);
    }
}

void *consumer(void *number)
{   
    for(int i = 0; i < maxItems; i++) {
        sem_wait(&e);
        pthread_mutex_lock(&sem);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)number),item, out);
        out = (out+1)%bufferSize;
        pthread_mutex_unlock(&sem);
        sem_post(&s);
    }
}

int main()
{   

    pthread_t pro[5],con[5];
    pthread_mutex_init(&sem, NULL);
    sem_init(&s,0,bufferSize);
    sem_init(&e,0,0);

    int a[5] = {1,2,3,4,5};

    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&sem);
    sem_destroy(&s);
    sem_destroy(&e);

    return 0;
    
}