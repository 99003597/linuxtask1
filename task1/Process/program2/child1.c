#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t ret;
    int s;
    int ex;
    int p;

    ret=fork();
    if(ret < 0)
    {
        perror("fork");
        exit(1);
    }
    if(ret == 0)
    {
                                   
        ex = execl("/usr/bin/gcc","gcc","-c","file.c",NULL); 
	execl("/bin/gcc","gcc","file.o","-o",p,NULL); 

                            
        if(ex<0)
        {
            perror("execv");
            exit(2);
        }
        exit(0);

    }
    else
    {
        waitpid(-1,&s,0); 
        printf("parent--child exit s=%d\n",
			WEXITSTATUS(s));
		
    }
    return 0;

}