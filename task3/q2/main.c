#include<stdio.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
# define MAX 8
sem_t em;
sem_t f;
int circular_queue[MAX];
int h = -1;
int t = -1;
void insert(int item);
void delete();
void* produced(void* pp)
{ 
   int item;
   sem_wait(&em);
   //printf("Enter the item\n");
   scanf("%d",&item);
   insert(item);
   printf("\n");
   sem_post(&f);
}
void* consumed(void* pp)
{
 sem_wait(&f);
  delete();
   sem_post(&em);
}

void insert(int item)
{
if((h == 0 && t == MAX-1) || (h == t+1))
{
printf("Queue Overflow n");
return;
}
if(h == -1)
{
h = 0;
t = 0;
}
else
{
if(t == MAX-1)
t = 0;
else
t = t+1;
}
circular_queue[t] = item ;
printf("element that are Produced : %d\n",item);
}

void delete()
{
if(h == -1)
{
printf("Queue Underflown");
return ;
}
printf("element that are Consumed : %d\n",circular_queue[h]);
if(h == t)
{
h = -1;
t=-1;
}
else
{
if(h == MAX-1)
h = 0;
else
h = h+1;
}
}


int main()
{
  int item;
   sem_init(&em,0,MAX);
    sem_init(&f,0,0);
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
       sem_destroy(&em);
    sem_destroy(&f);
return 0;
}