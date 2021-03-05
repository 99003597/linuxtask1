#include<string.h>
#include<stdio.h>
#include "myutils.h"
#include "bitmask.h"
#include "mystring.h"
#include <stdarg.h>


int main()
{
char s1[10]="pawri";
char s2[10]="horahi h";
int x = 5, y = 1; 

printf("%ld\n",mystrlen(s1));
printf("%s\n",mystrcpy(s1,s2));
printf("%s\n",mystrcat(s1,s2));
printf("%d\n",mystrcmp(s1,s2));
printf("%d\n",factorial(5));
printf("%d\n",isPrime(6));
printf("%d\n",isPalindrome(1001));
printf("%d\n",vsum(3,6,4,5));
printf("%d with %d-th bit Set: %d\n", x, y, set(x, y)); 
printf("%d with %d-th bit Cleared: %d\n", x, y, reset(x, y)); 
printf("%d with %d-th bit Toggled: %d\n", x, y, flip(x, y));
if(query(x, y))
  printf("Bit number %d is SET in number %d.\n",y,x);
else
  printf("Bit number %d is not SET in number %d.\n",y,x);
return 0; 

}