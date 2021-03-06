#include <pthread.h> 
#include <stdio.h>

  

#define MAX 16 
  
// maximum number of threads taken here
#define MAX_THREAD 4 
  

  
int a[] = { 2, 6, 8, 13, 17 ,19, 26, 29, 32, 57, 72, 108, 152, 172 }; 
int sum[4] = { 0 }; 
int part = 0; 
  
void* sum_array(void* arg) 
{ 
  
    // Each thread will find the sum of 1/4th of array 
    int thread_part = part++; 
  
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++) 
        sum[thread_part] += a[i]; 
} 
  
int main() 
{ 
  
    pthread_t threads[MAX_THREAD]; 
  
    // Creation of all 4 threads 
    for (int i = 0; i < MAX_THREAD; i++) 
        pthread_create(&threads[i], NULL, sum_array, NULL); 
  
    // combining all 4 threads and waiting for it to compute
    for (int i = 0; i < MAX_THREAD; i++) 
        pthread_join(threads[i], NULL); 
  
    // summing up all 4 parts
    int total_sum = 0; 
    for (int i = 0; i < MAX_THREAD; i++) 
        total_sum += sum[i]; 
  
    printf("the sum is %d\n", total_sum);
  
    return 0; }