#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv) {

    pid_t pid, child_pid;
    int status;
    char *args[] = {"gnome-calculator", NULL};
    int PROCESS;

    if (argc != 2) {
        perror("[!] Error in usage. Usage: ./a.out {process} \n");
        exit(EXIT_FAILURE);
    } else {
        PROCESS = atoi(argv[1]);
    }

    for(int i = 0; i < PROCESS; i++) {
        pid = fork();
        if (pid == -1) {
            fprintf(stderr, " errno: %i \n", errno);
            perror("[!] Error creating a child. \n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            printf("Child: %i, Father: %i. \n", getpid(), getppid());
            execvp(args[0], args);
        }
    }

    for(int i = 0; i < PROCESS; i++) {
        child_pid = wait(&status);

        if(WIFEXITED(status)) {
            printf("Child %i exited correctly (status %i) \n", child_pid, WTERMSIG(status));
        }
        else if(WIFSIGNALED(status)) {
            printf("Child %i signaled (status %i) \n", child_pid, WTERMSIG(status));
        }
        else if(WIFSTOPPED(status)) {
            printf("Child %i exited correctly (status %i) \n", child_pid, WSTOPSIG(status));
        }
    }

    exit(EXIT_SUCCESS);
}