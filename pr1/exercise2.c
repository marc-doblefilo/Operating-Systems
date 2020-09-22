#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

    pid_t pid, child_pid;
    int status;

    pid = fork();
    if (pid == 0){
        printf("This is the child %d with pid %d, which father's %d\n", status, getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    else if (pid == -1){
        perror("Error creating a child process\n");
        exit(EXIT_FAILURE);
    }

    sleep(20);

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