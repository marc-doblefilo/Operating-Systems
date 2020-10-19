#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void count_lines(void* filenames) {
    int * number_lines = calloc(1, sizeof(int));
    *number_lines = 1;
    char * filename = filenames;
    printf("%p \n", filenames);
    FILE * file_stream = fopen(filename, "r");
    if (file_stream == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while(!feof(file_stream)){
        char ch = fgetc(file_stream);
        if (ch == '\n'){
        *number_lines = *number_lines + 1;
        }
    }
    printf("%i\n",*number_lines);
    pthread_exit( (void *) number_lines);
}

int main(int argc, char **argv){
    int total_lines;

    pthread_t *threads = calloc(argc -1, sizeof(pthread_t));
    if(threads == NULL){
        perror("Error allocating memory for threads array.");
        exit(EXIT_FAILURE);
    }

    int **lines_array = calloc(argc -1, sizeof(int*));
    if(lines_array == NULL) {
        perror("Error allocating memory for lines array.");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < argc; i++) {
        pthread_create(&threads[i], NULL, (void*) count_lines, (void*) argv[i]);
    }

    for(int i = 1; i < argc; i++) {
        pthread_join(threads[i], (void **) &lines_array[i]);
    }

    for(int i = 1; i < argc; i++) {
        total_lines = total_lines + *lines_array[i];
    }

    free(*lines_array);
    free(threads);
    printf("Number of lines: %d\n", total_lines);
    exit(EXIT_SUCCESS);
}