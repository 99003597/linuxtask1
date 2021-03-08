#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define NUM_TRIES       (10)
#define NAME_MAX_LEN    (32)

// #undef COM_PREFIX
#ifndef COM_PREFIX
    #define COM_PREFIX "com"
#endif // !COM_PREFIX

#define FIFO_PATH(s) ("/tmp/" COM_PREFIX "." s)
#define SEM_PATH(s) ("/" COM_PREFIX "." s)

#define SHARED_RES_PERMS (0666)

const char *fifo_path = FIFO_PATH("chat");
const char *sync_fifo_path = SEM_PATH("chat");

typedef struct
{
    int fifo_fd;
    sem_t *sync_fifo;
    char* prompt;
    int prompt_len;
} shared_state_t;

void *sender(void *pv)
{
    char send_buff[128] = {0};
    int send_buff_len = 0;
    int sb_i = 0;
    shared_state_t *p_cs = (shared_state_t*)pv;

    for (int i = 0; i < NUM_TRIES; i++)
    {
        // Printf Prompt
        printf("%s[%d] \n", p_cs->prompt, i);
        // write(STDOUT_FILENO, p_cs->prompt, p_cs->prompt_len);

        // Wait and get user input
        for (sb_i = 0; sb_i < 127; sb_i++)
        {
            if (read(STDIN_FILENO, &send_buff[sb_i], 1) > 0)
            {
                if(send_buff[sb_i] == '\n')
                {
                    send_buff[sb_i] = 0;
                    break;
                }
            }
        }

        if (send_buff_len == 0)
            continue;

        // Wait until resource is free
        sem_wait(p_cs->sync_fifo);

        // Send Data
        write(p_cs->fifo_fd, send_buff, send_buff_len);

        // Release resource
        sem_post(p_cs->sync_fifo);

        // Free user input buffer given by scanf
        // if (send_buff != NULL)
        //     free(send_buff);
    }
    //pthread_exit(NULL);
}

void *receiver(void *pv)
{
    shared_state_t *p_cs = (shared_state_t*)pv;
    char recv_buff[128];
    int len;
    for (int i = 1; i <= NUM_TRIES; i++)
    {
        // Wait until resource is free
        sem_wait(p_cs->sync_fifo);

        // Receive Data
        while((len = read(p_cs->fifo_fd, recv_buff, 128)) > 0)
        {
            write(STDOUT_FILENO, recv_buff, len);
        }

        // Release resource
        sem_post(p_cs->sync_fifo);
    }
    //pthread_exit(NULL);
}

int main()
{
    shared_state_t cs;
    pthread_t th_receiver, th_sender;
    int ret = 0;
    int cleanup_fifo = 0;

    // Build prompt
    char username[NAME_MAX_LEN] = {0};
    char hostname[NAME_MAX_LEN] = {0};
    char *prompt_fmt = "\033[01;32m%s@%s\033[00m:\033[01;33m%s\033[00m|> ";

    struct passwd *pwd = getpwuid(geteuid());
    strncpy(username, pwd->pw_name, NAME_MAX_LEN);
    gethostname(hostname, NAME_MAX_LEN);
    cs.prompt_len = strlen(prompt_fmt);
    cs.prompt_len += strlen(username);
    cs.prompt_len += strlen(hostname);
    cs.prompt_len += strlen(fifo_path);

    cs.prompt = (char*)malloc(cs.prompt_len);
    printf("len => %d ", cs.prompt_len);
    cs.prompt_len = snprintf(cs.prompt, cs.prompt_len, prompt_fmt, username, hostname, fifo_path);
    printf("%d\n", cs.prompt_len);

#ifdef DEBUG
    printf("FIFO_CHAT = %s\n", fifo_path);
    printf("SEM_FIFO  = %s\n", sync_fifo_path);
    printf("PROMPT    = %s\n", cs.prompt);
#endif // DEBUG

    // Creates a semaphore for fifo access
    cs.sync_fifo = sem_open(sync_fifo_path, O_CREAT | O_RDWR, SHARED_RES_PERMS, 0);
    if (cs.sync_fifo == SEM_FAILED)
    {
        perror("sem_open");
        ret = errno;
        goto main_end;
    }

    // Create a fifo if it doesn't exist yet
    cs.fifo_fd = mkfifo(fifo_path, SHARED_RES_PERMS);
    if (cs.fifo_fd < 0)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");
            ret = errno;
            goto main_err_mkfifo;
        }
        cleanup_fifo = 0;
    }
    else
    {
        cleanup_fifo = 1;
    }

    // Open the fifo
    cs.fifo_fd = open(fifo_path, O_RDWR, SHARED_RES_PERMS);
    if (cs.fifo_fd < 0)
    {
        perror("open");
        ret = errno;
        goto main_err_fifo_open;
    }

    printf("Starting Chat Endpoint...\n");
    pthread_create(&th_receiver, NULL, receiver, &cs);
    pthread_create(&th_sender, NULL, sender, &cs);
    pthread_join(th_receiver, NULL);
    pthread_join(th_sender, NULL);

main_err_fifo_open:
    // Remove fifo if this process created it
    if (cleanup_fifo == 1)
        unlink(fifo_path);
main_err_mkfifo:
    // Close resource semaphore
    sem_close(cs.sync_fifo);
    // Producer Removes the semophore
    sem_unlink(sync_fifo_path);
main_end:
    free(cs.prompt);
    return ret; //exit(0);
}
