#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxlen 100
int main()
{
	int s[2], r_nbytes, w_nbytes;
	
    //open the two files
    s[0] = open("abcd.txt",O_RDONLY);
    s[1] = open("ABCD.txt", O_WRONLY | O_CREAT , 0666); 

    //check for errors
	if(s[0]<0)
	{
		perror("open");
		exit(1);
	}
    if(s[1]<0)
    {
		perror("open");
		exit(2);
	}
	char buf[maxlen];

       while(s[0]!=EOF)
        {
    r_nbytes = read(s[0],buf,maxlen);
    w_nbytes = write(s[1], buf, r_nbytes);
    }
    
    // while not EOF
    //     read to buff n bytes from file1
    //     write to file2 n bytes from buff
    


    //checks for errors and exit
	if(r_nbytes<0)
	{
		perror("read");
		exit(2);
	}
    if(w_nbytes<0)
	{
		perror("write");
		exit(3);
	}
   
    printf("written successfully, w_nbytes = %d\n",w_nbytes);
    
	close(s[0]);
    close(s[1]);
	return 0;
}