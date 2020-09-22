#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {

    pid_t pid, child_pid;
    int status;

    pid = fork();
    if(pid == 0) {
        printf("This is the child %d with pid %d, which father's %d\n", status, getpid(), getppid());
        char* arg1[] = {argv[1], NULL};
        execv("/usr/bin/mate-calculator", arg1);
        exit(EXIT_SUCCESS);
    }
    else if(pid == -1) {
        perror("Error creating a child process\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid == 0) {
        printf("This is the child %d with pid %d, which father's %d\n", status, getpid(), getppid());
        char* arg2[] = {argv[2]};
        for(int i = 3; i < argc; i++){
           arg2[i-2] = argv[i];
        }
        arg2[argc-2] = NULL;
        execv("/usr/bin/pluma", arg2);
        exit(EXIT_SUCCESS);
    }
    else if(pid == -1) {
        perror("Error creating a child process\n");
        exit(EXIT_FAILURE);
    }


    for (int j = 0; j < 2; j++) {
        child_pid = wait(&status);

        if(child_pid > 0) {
            if (WIFEXITED(status)){
                printf("Child %d killed (signal %d)\n", child_pid, WTERMSIG(status));
            }
            else if (WIFSIGNALED(status)){
                printf("Child %d killed (signal %d)\n", child_pid, WTERMSIG(status));
            }
            else if (WIFSTOPPED(status)){
                printf("Child %d stopped (signal %d)\n", child_pid, WSTOPSIG(status));
            }
        }
        else {
                printf("Error invoking wait or the call was interrupted\n");
                exit(EXIT_FAILURE);
        }
    }


    exit(EXIT_SUCCESS);
}