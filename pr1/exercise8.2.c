#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const** argv)
{
  int status;
  int pid = atoi(argv[1]);
  if (argc < 2)
  {
    printf("Error! Usage: ./exercise8.out PID\n");
    exit(EXIT_FAILURE);
  }
  printf("PID: %d\n", pid);
  status = kill(SIGUSR1, pid);
  printf("Kill return: %d\n", status);
  exit(EXIT_SUCCESS);
}