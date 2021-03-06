#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
// structure for message queue
struct message 
{
   long m_t;
   char msg[100];
} message;

int main() 
{
   key_t key;
   int m_id;
   key = ftok("progfile", 65); //create unique key
   m_id = msgget(key, 0666 | IPC_CREAT); //create message queue and return id
   message.m_t = 1;
   printf("Write Message : ");
   fgets(message.msg, 100, stdin);
   printf("Sent message is : %s \n", message.msg);
   msgsnd(m_id, &message, sizeof(message), 0); //send message
   msgrcv(m_id, &message, sizeof(message), 1, 0); //used to receive message
   // display the message
   printf("Received Message is : %s \n", message.msg);

   return 0;
}