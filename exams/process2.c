#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        perror("Error in usage. Usage: ./a.out {process} \n");
        exit(EXIT_FAILURE);
    }

    pid_t pid, pid_child;
    int status;
    int PROCESS = atoi(argv[1]);

    for(int i = 0; i < PROCESS; i++) {
        pid = fork();
        if (pid == 0) {
            printf("Im child %i, my father is %i \n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        } else if (pid == -1) {
            perror("Error creating a process \n");
            fprintf(stderr, "errno: %i \n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < PROCESS; i++) {
        pid_child = wait(&status);
        if(pid_child > 0) {
            if (WIFEXITED(status)) {
                printf("Child %i exited. (status %i) \n", getpid(), WTERMSIG(status));
            }
            else if (WIFSIGNALED(status)) {
                printf("Child %i signaled. (status %i) \n", getpid(), WTERMSIG(status));
            }
            else if (WIFSTOPPED(status)) {
                printf("Child %i stopped. (status %i) \n", getpid(), WSTOPSIG(status));
            }
            else {
                printf("Error invoking call \n");
                exit(EXIT_FAILURE);
            }
        }
    }

    exit(EXIT_SUCCESS);
}