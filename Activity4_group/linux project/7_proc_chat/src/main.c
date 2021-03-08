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

#define NAME_MAX_LEN        (32)

// #undef COM_PREFIX
#ifndef COM_PREFIX
    #define COM_PREFIX "com"
#endif // !COM_PREFIX

#define FIFO_PATH(s)        ("/tmp/" COM_PREFIX "." s)

#define SHARED_RES_PERMS    (0666)
#define READ_FD             (0)
#define WRITE_FD            (1)

__sig_atomic_t run = 1;

const char *fifo0_path = FIFO_PATH("chat0");
const char *fifo1_path = FIFO_PATH("chat1");

typedef struct
{
    int fifo_fd[2];
    const char *fifo_path[2];
    sem_t *sync_fifo;
    char *prompt;
    int prompt_len;
} shared_state_t;

void *sender(void *pv)
{
    char send_buff[128] = {0};
    int send_buff_len = 0;
    int sb_i = 0;
    int ret;

    shared_state_t *p_cs = (shared_state_t *)pv;

    p_cs->fifo_fd[WRITE_FD] = open(p_cs->fifo_path[WRITE_FD], O_WRONLY);
    if (p_cs->fifo_fd[WRITE_FD] < 0)
    {
        perror("open");
        return errno;
    }

    while (run)
    {
        if (sb_i != 0)
        {
            // Send Data
            ret = write(p_cs->fifo_fd[WRITE_FD], send_buff, sb_i+1);
            if (ret < 0)
                perror("write");
        }

        write(STDOUT_FILENO, p_cs->prompt, p_cs->prompt_len);

        // Wait and get user input
        for (sb_i = 0; run && sb_i < 127; sb_i++)
        {
            if (read(STDIN_FILENO, &send_buff[sb_i], 1) > 0)
            {
                if (send_buff[sb_i] == '\n')
                {
                    send_buff[sb_i+1] = 0;
                    break;
                }
            }
            else
            {
                run = 0;
                break;
                perror("read");
            }
        }
    }
    //pthread_exit(NULL);
}

void *receiver(void *pv)
{
    shared_state_t *p_cs = (shared_state_t *)pv;
    char recv_buff[128];
    int len, ret;
    char* prompt_clr = malloc(p_cs->prompt_len);
    memset(prompt_clr, ' ', p_cs->prompt_len);

    p_cs->fifo_fd[READ_FD] = open(p_cs->fifo_path[READ_FD], O_RDONLY);
    if (p_cs->fifo_fd[READ_FD] < 0)
    {
        perror("open");
        return errno;
    }

    while (run)
    {
        // Receive Data
        // Wait and get user input
        for (len = 0; len < 127; len++)
        {
            if (read(p_cs->fifo_fd[READ_FD], &recv_buff[len], 1) > 0)
            {
                if (recv_buff[len] == '\n')
                {
                    recv_buff[len+1] = 0;
                    break;
                }
            }
            else
            {
                run = 0;
                break;
                perror("read");
            }
        }
        printf("\r%s\r%s", prompt_clr, recv_buff);
        write(STDOUT_FILENO, p_cs->prompt, p_cs->prompt_len);

        // while ((len = read(p_cs->fifo_fd[READ_FD], recv_buff, 1)) > 0)
        // {
        //     // ret = write(STDOUT_FILENO, "\n", 1);
        //     ret = write(STDOUT_FILENO, recv_buff, len);
        //     if (ret < 0)
        //         perror("write");
        // }
    }
    //pthread_exit(NULL);
}

int main()
{
    shared_state_t cs;
    pthread_t th_receiver, th_sender;
    int ret = 0;
    int first = 0;

    // Create fifos if they don't exist yet
    ret = mkfifo(fifo0_path, SHARED_RES_PERMS);
    if (ret < 0)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");
            ret = errno;
            goto main_cleanup_end;
        }
        first = 0;
    }
    else
    {
        first = 1;
    }

    ret = mkfifo(fifo1_path, SHARED_RES_PERMS);
    if (ret < 0 && errno != EEXIST)
    {
        perror("mkfifo");
        ret = errno;
        goto main_cleanup_mkfifo0;
    }

    if (first == 1)
    {
        cs.fifo_path[READ_FD] = (char*)fifo1_path;
        cs.fifo_path[WRITE_FD] = (char*)fifo0_path;
    }
    else
    {
        cs.fifo_path[READ_FD] = (char*)fifo0_path;
        cs.fifo_path[WRITE_FD] = (char*)fifo1_path;
    }

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
    cs.prompt_len += strlen(cs.fifo_path[WRITE_FD]);

    cs.prompt = (char *)malloc(cs.prompt_len);
    cs.prompt_len = snprintf(cs.prompt, cs.prompt_len, prompt_fmt, username, hostname, cs.fifo_path[WRITE_FD]);

#ifdef DEBUG
    printf("FIFO_READ  = %s\n", cs.fifo_path[READ_FD]);
    printf("FIFO_WRITE = %s\n", cs.fifo_path[WRITE_FD]);
    printf("PROMPT     = %s\n", cs.prompt);
#endif // DEBUG

    printf("Starting Chat Endpoint...\n");
    pthread_create(&th_receiver, NULL, receiver, &cs);
    pthread_create(&th_sender, NULL, sender, &cs);
    pthread_join(th_receiver, NULL);
    pthread_join(th_sender, NULL);

    free(cs.prompt);
// main_cleanup_fifo_wr_open:
//     close(cur_wr_fd);
// main_cleanup_fifo_rd_open:
//     close(cur_rd_fd);
main_cleanup_mkfifo1:
    // Remove fifo if this process created it
    if (first == 1)
        unlink(fifo1_path);
main_cleanup_mkfifo0:
    // Remove fifo if this process created it
    if (first == 1)
        unlink(fifo0_path);
main_cleanup_end:
    return 0; //exit(0);
}
