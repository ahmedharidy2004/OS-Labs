#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#define REQUEST_WORDS  0
#define REQUEST_VOWELS 1

union Semun
{
    int val;
};

struct SharedData {
    char message[256];
    int  request_type;
    int  result;
};

int shmid  = -1;
int sem_id  = -1;
struct SharedData *shm_ptr = NULL;

void sigint_handler(int signum)
{
    if (shm_ptr != NULL)
        shmdt(shm_ptr);
 
    if (shmid != -1)
        shmctl(shmid, IPC_RMID, NULL);
 
    if (sem_id != -1)
        semctl(sem_id, 0, IPC_RMID);
    exit(0);
}

int count_vowels(const char *str) 
{ 
    int count = 0; 
    while (*str) 
    { 
        char c = *str; 
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'|| 
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U') 
        { 
            count++; 
        } 
        str++; 
    } 
    return count; 
}

int count_words(const char *str) 
{ 
    int count = 0; 
    int in_word = 0; 
    while (*str) 
    { 
        if (*str != ' ' && in_word == 0) 
        { 
            count++; 
            in_word = 1; 
        } 
        else if (*str == ' ') 
        { 
            in_word = 0; 
        } 
        str++; 
    }
    return count; 
} 

void down(int sem, int sem_num)
{
    struct sembuf op;

    op.sem_num = sem_num;
    op.sem_op = -1;
    op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &op, 1) == -1)
    {
        perror("Error in down()");
        exit(-1);
    }
}

void up(int sem, int sem_num)
{
    struct sembuf op;

    op.sem_num = sem_num;
    op.sem_op = 1;
    op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &op, 1) == -1)
    {
        perror("Error in up()");
        exit(-1);
    }
}

int main(){
    union Semun semun;
    signal(SIGINT, sigint_handler);
    key_t sh_key,sem_key;

    sh_key = ftok("keyfile", 50);
    shmid = shmget(sh_key, sizeof(struct SharedData), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("Error in create");
        exit(-1);
    }
    shm_ptr = (struct SharedData *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
         perror("shmat"); exit(-1); 
        }

    sem_key = ftok("keyfile", 60);
    sem_id = semget(sem_key, 3, 0666 | IPC_CREAT);
    if (sem_id == -1)
    {
        perror("Error in create sem");
        exit(-1);
    }

    semun.val = 0;
    if (semctl(sem_id, 0,  SETVAL, semun) == -1) {
        perror("semctl"); exit(-1); 
    }
    if (semctl(sem_id, 1, SETVAL, semun) == -1) {
        perror("semctl"); exit(-1); 
    }
    semun.val = 1;
    if (semctl(sem_id, 2, SETVAL, semun) == -1) {
        perror("semctl"); exit(-1);
    }

    sleep(10);
    while(1){
        down(sem_id, 0);
        int result;
        if (shm_ptr->request_type == REQUEST_WORDS)
            result = count_words(shm_ptr->message);
        else
            result = count_vowels(shm_ptr->message);
        
        shm_ptr->result = result;
        up(sem_id, 1);
        sleep(3);
    }
    return 0;
}