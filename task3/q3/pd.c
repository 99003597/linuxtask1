#include <pthread.h>
//#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>



#define MaxItems 7 
#define BufferSize 7 





//sem_t empty;         
//sem_t full;         
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer_side(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce an random item
        //sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer guy %d: Insert the Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        //sem_post(&full);
    }
}
void *consumer_side(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        //sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        //sem_post(&empty);
    }
}

int main()
{   

    pthread_t pro[7],con[7];
    pthread_mutex_init(&mutex, NULL);
  

    int a[7] = {1,2,3,4,5,6,7}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 7; i++) {
        pthread_create(&pro[i], NULL, (void *)producer_side, (void *)&a[i]);
    }
    for(int i = 0; i < 7; i++) {
        pthread_create(&con[i], NULL, (void *)consumer_side, (void *)&a[i]);
    }

    for(int i = 0; i < 7; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 7; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    //sem_destroy(&empty);
    //sem_destroy(&full);         

    return 0;
    
}