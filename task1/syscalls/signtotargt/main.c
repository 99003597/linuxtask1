#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h>
#define SIGHUP 1
#define SIGQUIT 3

void sighup(); 
void sigint(); 
void sigquit(); 
   
void sighup() 
  
{ 
    signal(SIGHUP, sighup); //reset signal
    printf("CHILD: SIGHUP Received\n"); 
} 
  
void sigint() 
  
{ 
    signal(SIGINT, sigint); //reset signal
    printf("CHILD: SIGNIT Received \n"); 
} 
  
void sigquit() 
{ 
    printf("I have been finished\n"); 
    exit(0); 
} 

void main() 
{ 
    int pid; 
  
     //get child process
    if ((pid = fork()) < 0) { 
        perror("fork"); 
        exit(1); 
    } 
  
    if (pid == 0)
		{                            //child
        signal(SIGHUP, sighup); 
        signal(SIGINT, sigint); 
        signal(SIGQUIT, sigquit); 
        for (;;); 
    } 
  
    else 
    { 
        printf("\nPARENT: sending SIGHUP\n\n");  //pid hold id of child
        kill(pid, SIGHUP); 
  
        sleep(2); 
        printf("\nPARENT: sending SIGINT\n\n"); 
        kill(pid, SIGINT); 
  
        sleep(2);
        printf("\nPARENT: sending SIGQUIT\n\n"); 
        kill(pid, SIGQUIT); 
        sleep(2); 
    } 
} 