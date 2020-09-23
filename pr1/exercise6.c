#include	<signal.h>
#include	<stdio.h>
#include	<unistd.h>
#include <stdlib.h>
#include <errno.h>

void sig_alrm(int sign)
{
    printf("Signal received, value: %i\n", sign);
    return;
}

void SetAlarm(int nsecs)
{
	alarm(nsecs);
	pause();
}

int main ()
{

    int counter = 0;
    int seconds[] = {5, 3, 1};

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
	{
		perror("Signal error");
   	printf("errno value= %d\n", errno);  
		exit(EXIT_FAILURE);
	}
   
    while(1) {
        for(int i = 0; i < 3; i++) {
            if(counter < 4) {
                printf("Alarm at %d seconds\n", seconds[i]);
                SetAlarm(seconds[i]);
                counter++;
            }
            else {
                kill(getpid(), SIGALRM);
                printf("Killed process");
                exit(EXIT_SUCCESS);
            }
        }
    }

    exit(EXIT_FAILURE);

}