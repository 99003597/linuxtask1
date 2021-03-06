#include<pthread.h>
//#include<semaphore.h>
#include<stdio.h>

int maximum_value = 10;
int stack[10];
int top = -1;
int data;

//check if the stack is empty or not
int ifemptyStack()
{
    if(top == -1)
        return -1;
    else 
        return 0;

}


int iffullStack()//check if stack is full or not
{
    if(top == maximum_value)
        return 1;
    else 
        return 0;    
}


int peek()
{
    return stack[top];
}

int pop()// remove the top element
{

    if(!ifemptyStack())
    {
        data = stack[top];
        top = top -1;
        return data;
    }
    else
    {   
        printf("Stack is empty macha!!\n");
       
}


int push(data)//insert an element
{
    if(!iffullStack())
    {
        top = top+1;
        stack[top] = data;
    }

    else
    {
        printf("Stack id full macha!! :( \n");
       
}

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
//sem_t s1;


void* producer_function(void* pv)//push operation from the producer
{
    int i;
    printf("push the operation of 1,2,3,4,5,6,7 \n");
    pthread_mutex_lock(&m1);    //lock the mutex

  //push the data
    push(1);
    push(2);
    push(3);                
    push(4);
    push(5);
    push(6);
    push(7);

    pthread_mutex_unlock(&m1);      
}


void* consumer_function(void* pv)	//pop operation from the consumer	
{
	int i;
	printf("poping all the values from the stack\n");
	//sem_wait(&s1);			
	pthread_mutex_lock(&m1);
	
	pop();
	pop();
    pop();
    pop();
    pop();
    pop();
    pop();
	
	pthread_mutex_unlock(&m1);
}

int main()
{
    printf("\n\nstarts\n\n");
    pthread_t pt1,pt2;	//thread handles
	
	pthread_create(&pt1,NULL,producer_function,NULL);
	pthread_create(&pt2,NULL,consumer_function,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);//changing sequence lead to deadlock
	printf("Top element in stack: %d\n" ,peek());
	printf("Is the stack full? - %s\n" , iffullStack()?"Yes":"No");
   	printf("is the stack empty? - %s\n" , ifemptyStack()?"Yes":"No");
	
	pthread_mutex_destroy(&m1);
	printf("CODE DONE WELL!!\n");
	return 0;

}