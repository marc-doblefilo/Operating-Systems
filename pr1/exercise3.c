#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int arc, char** argv) {

    pid_t pid, child_pid;
    int status;

    pid = fork();
    if(pid == 0) {
        printf("This is the child %d with pid %d, which father's %d\n", status, getpid(), getppid());
           
    }

}