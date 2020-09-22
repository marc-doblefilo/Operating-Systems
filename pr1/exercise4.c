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

    for(int i = 1; i <= 2; i++) {
        pid = fork();
        if(pid == 0) {
            if(execl("./factorial", "factorial", argv[i], NULL) == -1) {
                perror("Error executing factorial\n");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
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