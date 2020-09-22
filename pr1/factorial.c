#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if(argc == 2){
        int number = atoi(argv[1]);
        int result = 1;
        for(int i = 1; i<=number; i++) {
            result = result * i;
            printf("Calculating factorial of %i: %i\n", number, result);
            sleep(1);
        }
        printf("The factorial of %i is: %i\n", number, result);
        return result;
    }
    else {
        perror("ERROR! Usage: ./factorial <number>\n");
        exit(EXIT_FAILURE);
    }
}