
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer 
{
   long message_type;
   char the_msg[100];
} message;

int main1() 
{
   key_t the_key;
   int message_id;
   the_key = ftok("progfile", 65); //create an unique key
   message_id = msgget(the_key, 0666 | IPC_CREAT); //create message queue and return id
   msgrcv(message_id, &message, sizeof(message), 1, 0); //used to receive message
   // display the message
   printf("Received Message is : %s \n", message.the_msg);
    printf("Write Message : ");
   fgets(message.the_msg, 100, stdin);
  
  
   msgsnd(message_id, &message, sizeof(message), 0); 
   
   printf("Sent message is : %s \n", message.the_msg);
   return 0;
}