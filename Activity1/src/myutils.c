#include <stdio.h>
#include <stdarg.h>
#include "myutils.h"

int factorial(unsigned int x)
{
	
	if (x>=1)
        return x*factorial(x-1);
    else
        return 1;
	
}
int isPrime(int a)
{
   int p;
   for ( p = 2 ; p <= a - 1 ; p++ )
   {
      if ( a%p == 0 )
     return 0;
   }
   return 1;
	
}
int isPalindrome(int str)
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
	va_list valist;
	  int sum = 0, i; 
  
    va_start(valist, x); 
    for (i = 0; i < x; i++)  
        sum += va_arg(valist, int); 
  
    va_end(valist); 
    return sum;

}
	
	
	
	

