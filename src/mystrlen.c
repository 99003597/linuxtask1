#include <stdio.h>
#include "mystring.h"


size_t mystrlen(const char *str)
{
char *p=str

for (i = 0; p[i] != '\0'; ++i);

return i;

}
char *mystrcpy(char *str1, char *str2)
{
	char *p1=str1;
	char *p2=str2;
	 for (i = 0; p1[i] != '\0'; ++i) 
	 {
        p2[i] = p1[i];
    }
return p2;
}
char  *mystrcat(char *str1, const char *str2)
{
    strcat(str1,str2);
    return str1;
	
}
int  mystrcmp(const char *str1, const char *str2)
{
	int r;
	
	r=strcmp(str1,str2);
	
	return r;
}
