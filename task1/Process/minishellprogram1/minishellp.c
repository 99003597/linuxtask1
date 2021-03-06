#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
//minishell
int main()
{
    pid_t v_ret;
    int s_s;
    int c_e;
    char c[10];
    printf("Enter your command:");
    scanf("%s", c);                  
    v_ret=fork();
    //checks if errors are there
    if(v_ret<0)
    {
        perror("fork");
        exit(1);
    }
    if(v_ret==0)
    {
        c_e=execlp(c,c,NULL);
        if(c_e<0)
        {
            perror("execlp");
            exit(2);
        }
        exit(0);
    }
    else
    {
        waitpid(-1,&s_s,0); //wait of (&s_s);
        printf("parent--child exit status=%d\n",
			WEXITSTATUS(s_s));
    }
}