#include <stdio.h>
#include "myutils.h"

int factorial(unsigned int x)
{
	
	if (x>=1)
        return x*multiplyNumbers(x-1);
    else
        return 1;
	
}
int isPrime(int p)
{
	
	   for ( p = 2 ; p <= a - 1 ; p++ )
   { 
      if ( a%p == 0 )
     return 0;
   }
   return 1;
	
}
int isPalindrome(char *str)
{
	
	{
  int temp, remainder, rev=0;
  temp = str;

  while( str!=0 )
  {
     remainder = str % 10;
     rev = rev*10 + remainder;
     str /= 10;
  }

  if ( rev == temp ) return 0;
  else return 1;
}
	
	
}
int vsum(int x, ...)
{
	
	
	
	
	
	
	
}
