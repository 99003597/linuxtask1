#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


// structure for message queue
struct msg_buffer 
{
   long message_type;
   char text_message[100];
} message;

int main() 
{
   key_t my_key;
   int msg_id,id;
   my_key = ftok("progfile", 65); //create unique key

   char path[100];
   

   printf("Enter source file path: ");
   scanf("%s", path);

   struct stat {
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */
    uid_t     st_uid;     /* user ID of owner */
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file) */
    off_t     st_size;    /* total size, in bytes */
    blocksize_t st_blksize; /* blocksize for file system I/O */
    blockcnt_t  st_blocks;  /* number of 512B blocks allocated */
    time_t    st_atime;   /* time of last access */
    time_t    st_mtime;   /* time of last modification */
    time_t    st_ctime;   /* time of last status change */
   };
   struct stat stats;

   msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
   message.message_type = 1;

   id = stat(path, &stats);
   /*
   printf("Write Message : ");
   fgets(message.text_message, 100, stdin);
   
   printf("Sent message is : %s \n", message.text_message);
   */
   msgsnd(msg_id,id,sizeof(id),0); //send message
   
   msgrcv(msg_id, &message, sizeof(message), 1, 0); //used to receive message
   
   // display the message
   printf("Received Message is : %s \n", message.text_message);

   return 0;
}