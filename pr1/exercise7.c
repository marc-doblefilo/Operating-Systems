#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#define PROCESS 1

void trataSennal()
{
    printf("Signal received from %d\n", getpid());
    return;
}

int main(int argc, char** argv) {

    pid_t pid, pid_child;
    pid_t father_pid = getpid();
    int status;

    if (signal(SIGUSR1, trataSennal) == SIG_ERR) {
		perror("Signal error");
   	printf("errno value= %d\n", errno);  
		exit(EXIT_FAILURE);
	}

    for (int i = 0; i < PROCESS; i++) {
        pid = fork();
        if (pid == 0) {
            printf("This is the child %d with pid %d, which father's %d\n", status, getpid(), getppid());
            for(int i = 0; i < 5; i++) {
                printf("Signal sent from: %d\n", getppid());
                kill(father_pid, SIGUSR1);
                sleep(1);
            }
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

    exit(EXIT_SUCCESS);

} 