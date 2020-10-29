// CPP code to create three child 
// process of a parent 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
  
// Driver code 
int main() 
{ 
    int pid, pid1, pid2; 
  
    // variable pid will store the 
    // value returned from fork() system call 
    pid = fork(); 
  
    // If fork() returns zero then it 
    // means it is child process. 
    if (pid == 0) { 
  
        // First child needs to be printed 
        // later hence this process is made 
        // to sleep for 3 seconds. 
        sleep(3); 
  
        // This is first child process 
        // getpid() gives the process 
        // id and getppid() gives the 
        // parent id of that process. 
        printf("child[1] --> pid = %d and ppid = %d\n", 
               getpid(), getppid()); 
    } 
  
    else { 
        pid1 = fork(); 
        if (pid1 == 0) { 
            sleep(2); 
            printf("child[2] --> pid = %d and ppid = %d\n", 
                   getpid(), getppid()); 
        } 
        else { 
            pid2 = fork(); 
            if (pid2 == 0) { 
                // This is third child which is 
                // needed to be printed first. 
                printf("child[3] --> pid = %d and ppid = %d\n", 
                       getpid(), getppid()); 
            } 
  
            // If value returned from fork() 
            // in not zero and >0 that means 
            // this is parent process. 
            else { 
                // This is asked to be printed at last 
                // hence made to sleep for 3 seconds. 
                sleep(3); 
                printf("parent --> pid = %d\n", getpid()); 
            } 
        } 
    } 
  
    return 0; 
} 