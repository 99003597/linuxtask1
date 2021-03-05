#include<stdio.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
# define MAX 8
sem_t empty;
sem_t full;
int circular_queue[MAX];
int head = -1;
int tail = -1;
void insert(int item);
void delete();
void* produced(void* pp)
{ 
   int item;
   sem_wait(&empty);
   //printf("Enter the item\n");
   scanf("%d",&item);
   insert(item);
   printf("\n");
   sem_post(&full);
}
void* consumed(void* pp)
{
 sem_wait(&full);
  delete();
   sem_post(&empty);
}

void insert(int item)
{
if((head == 0 && tail == MAX-1) || (head == tail+1))
{
printf("Queue Overflow n");
return;
}
if(head == -1)
{
head = 0;
tail = 0;
}
else
{
if(tail == MAX-1)
tail = 0;
else
tail = tail+1;
}
circular_queue[tail] = item ;
printf("element that are Produced : %d\n",item);
}

void delete()
{
if(head == -1)
{
printf("Queue Underflown");
return ;
}
printf("element that are Consumed : %d\n",circular_queue[head]);
if(head == tail)
{
head = -1;
tail=-1;
}
else
{
if(head == MAX-1)
head = 0;
else
head = head+1;
}
}


int main()
{
  int item;
   sem_init(&empty,0,MAX);
    sem_init(&full,0,0);
    pthread_t pro[8],con[8];
   printf("Please enter the items to be produced and consumed :\n ");
   for(int i = 0; i < 8; i++) {
    pthread_create(&pro[i], NULL, (void *)produced, NULL);
    }
     for(int i = 0; i < 8; i++) {
        pthread_create(&con[i], NULL, (void *)consumed,NULL);
    }
     for(int i = 0; i < 8; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 8; i++) {
        pthread_join(con[i], NULL);
    }
       sem_destroy(&empty);
    sem_destroy(&full);
return 0;
}