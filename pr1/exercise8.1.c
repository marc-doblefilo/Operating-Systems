#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void printid() {
    printf("Received... My PID is: %d\n", getpid());
    return;
}

int main(int argc, char** argv) {
    signal(SIGUSR1, printid);
    while(1) {
        kill(getpid(), SIGUSR1);
        sleep(2);
    }
    exit(EXIT_SUCCESS);
}