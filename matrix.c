#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define COLUMNS 3
#define ROWS 3

struct args {
  int * matrix;
  int * column;
};

void * MultiplyVector(void* matrixValues ){
  struct args * argumentos = matrixValues;

  int * final_value = calloc(1, sizeof(int));
  if ( final_value == NULL ){
    perror("Error al reservar memoria");
    exit(EXIT_FAILURE);
  }

  for (int i= 0; i<COLUMNS; i++){
    * final_value = *final_value + ( argumentos->matrix[i] * argumentos->column[i] );
  }

  pthread_exit( (void *) final_value);
}

int main(int argc, char *argv[]){
  int ** result = calloc(ROWS, sizeof(int *));
  if (result == NULL){
    perror("ERROR AL RESERVER MEMORIA");
    exit(EXIT_FAILURE);
  }

  int matrix[ROWS][COLUMNS] = {
    {1,2,3},
    {1,2,3},
    {1,2,3}
  };

  int column[] = {1,2,3};
  pthread_t *threads_array = calloc(argc - 1, sizeof(pthread_t));
  if (threads_array  == NULL){
    perror("Fallo al reservar memoria para el array de threads");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i<ROWS; i++){
      struct args matrix_args;
      matrix_args.matrix = (int *)&matrix[i];
      matrix_args.column = (int*)&column;
      pthread_create(&threads_array[i], NULL, (void*) MultiplyVector, (void *) &matrix_args);
    }

  for (int i = 0; i<ROWS; i++){
      pthread_join(threads_array[i], (void **) &result[i]);
    }

  for (int i = 0; i<ROWS; i++){
      printf("%d\n", *result[i]);
    }




  return 0;
}