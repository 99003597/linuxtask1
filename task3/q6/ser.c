#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

// Define message queue structure
struct msg_buffer 
{
   long message_type;
   char text_message[100];
} message;

int main() 
{
   key_t the_key;
   int msg_id;
   the_key = ftok("progfile", 65); //create unique key
   msg_id = msgget(the_key, 0666 | IPC_CREAT); //create message queue and return id
   msgrcv(msg_id, &message, sizeof(message), 1, 0); //used to receive message
   // display the message
   lstat(msg_id, &message.text_message);
   printf("Received Message is : %s \n", message.text_message);
   
   msgsnd(msg_id, &message, sizeof(message), 0); 
   
  // printf("Sent message is : %s \n", message.text_message);
   return 0;
}