#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#define PROCESS 5

int main(int argc, char** argv) {

    pid_t pid, pid_child;
    int status;
    int result = 0;

    for (int i = 0; i < PROCESS; i++) {
        pid = fork();
        if (pid == 0) {
            printf("This is the child %d with pid %d, which father's %d\n", status, getpid(), getppid());
            printf("result++\n");
            result++;
            exit(EXIT_SUCCESS);
        }
        else if (pid == -1) {
            perror("Error creating a child\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < PROCESS; j++) {
        pid_child = wait(&status);

        if(pid_child > 0) {
            if (WIFEXITED(status)){
                printf("Child %d killed (signal %d)\n", pid_child, WTERMSIG(status));
            }
            else if (WIFSIGNALED(status)){
                printf("Child %d killed (signal %d)\n", pid_child, WTERMSIG(status));
            }
            else if (WIFSTOPPED(status)){
                printf("Child %d stopped (signal %d)\n", pid_child, WSTOPSIG(status));
            }
        }
        else {
                printf("Error invoking wait or the call was interrupted\n");
                exit(EXIT_FAILURE);
        }
    }

    printf("Innitial result: 0, now: %d", result);
    exit(EXIT_SUCCESS);
} 