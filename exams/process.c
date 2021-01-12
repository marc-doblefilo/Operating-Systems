#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define PROCESS 2

int main(int argc, char **argv) {

    pid_t pid, child_pid;
    int status;
    int input_number;
    int input;
    int factorial = 1;

    if (argv[1] == NULL) {
        perror("[!] Error in usage. Usage: ./a.out {number} \n");
        exit(EXIT_FAILURE);
    } else {
        input_number = atoi(argv[1]);
        input = input_number;
    }

    for(int i = 0; i < PROCESS; i++) {
        pid = fork();
        if (pid == 0) {
            if(i == 0) {
                while(input_number > 1) {
                    factorial *= input_number;
                    input_number--;
                }
                printf("Soy el hijo %d, mi padre %d el factorial de %i es %i. \n", getpid(), getppid(), input, factorial);
                exit(EXIT_SUCCESS);
            }
            if(i == 1) {
                printf("Soy el hijo %d, mi padre %d y voy a abrir la calculadora \n", getpid(), getppid());
                char *arg[] = {"/usr/bin/gnome-calculator", NULL};
                execv(arg[0], arg);
                exit(EXIT_SUCCESS);
           }
        }
        else if (pid == -1) {
            perror("Error creating a child. \n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < PROCESS; i++) {
        child_pid = wait(&status);
        if(child_pid > 0) {
            if(WIFEXITED(status)) {
                printf("Child %d killed (status %d) \n", child_pid, WTERMSIG(status));
            } 
            else if(WIFSIGNALED(status)) {
                printf("Child %d killed (status %d) \n", child_pid, WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)) {
                printf("Child %d killed (status %d) \n", child_pid, WSTOPSIG(status));
            }
        } else {
            perror("Error invoking call or the call was interrupted \n");
            exit(EXIT_FAILURE);
        }
    }
    
    exit(EXIT_SUCCESS);
}