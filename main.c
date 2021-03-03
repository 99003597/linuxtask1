#include <stdio.h>
#include <unistd.h>

int main() 
{
int ret = fork();
// int i;
// for (i=0;i<=5;i++)

if (ret == 0)
printf("child  %d ",ret);
exclp("./b.out",NULL);
else
printf("parent  %d",ret);


return 0;

}