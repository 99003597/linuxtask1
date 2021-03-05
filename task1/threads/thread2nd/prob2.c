#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
  

#define max 16 
  
// total 4 threads 
#define Th_max 4 
  

int a[max] = { 2, 6, 8, 13, 17 ,19, 26, 29, 32,566, 57, 72, 108, 152, 172, 200 }; 
  
// Array to store max of threads 
int maximum_number[Th_max] = { 0 }; 
int thread_no = 0; 
  
// Function to compute maximum number in the array
void maximum(void* arg) 
{ 
    int i, number = thread_no++; 
    int maxs = 0; 
  
    for (i = number * (max / 4); i < (number + 1) * (max / 4); i++) { 
        if (a[i] > maxs) 
            maxs = a[i]; 
    } 
  
    maximum_number[number] = maxs; 
} 
  

int main() 
{ 
    int maxi = 0; 
    int i; 
    pthread_t threads[Th_max]; 
  
  
    // creation of all 4 threads
    for (i = 0; i < Th_max; i++) 
        pthread_create(&threads[i], NULL, 
                       maximum, (void*)NULL); 
  
    //combining all 4 threads and waiting for the result
    for (i = 0; i < Th_max; i++) 
        pthread_join(threads[i], NULL); 
  
    // compute the max through individual threads
    for (i = 0; i < Th_max; i++) { 
        if (maximum_number[i] > maxi) 
            maxi = maximum_number[i]; 
    } 
  
    printf("Maxi in the element is : %d", maxi); 
  
    return 0; 
} 