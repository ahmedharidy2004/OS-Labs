#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#define REQUEST_WORDS  0
#define REQUEST_VOWELS 1

struct SharedData {
    char message[256];
    int  request_type;
    int  result;
};

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

int main() {
    key_t sh_key,sem_key;
    int shmid, sem_id;
    
    sh_key = ftok("keyfile", 50);
    shmid = shmget(sh_key, sizeof(struct SharedData), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("Error in create");
        exit(-1);
    }
    struct SharedData *shm_ptr = (struct SharedData *)shmat(shmid, NULL, 0);
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
    while(1){
        
        char type[10];
        char sentence[256];

        printf("Enter type (1 for WORDS/ 2 for VOWELS): ");
        fgets(type, sizeof(type), stdin);
        type[strcspn(type, "\n")] = '\0';

        printf("Enter sentence: ");
        fgets(sentence, sizeof(sentence), stdin);
        sentence[strcspn(sentence, "\n")] = '\0';
        
        int req;
        if (strcasecmp(type, "1") == 0)
            req = REQUEST_WORDS;
        else if (strcasecmp(type, "2") == 0)
            req = REQUEST_VOWELS;
        else continue;

        down(sem_id, 2);

        strncpy(shm_ptr->message, sentence, 255);
        shm_ptr->message[255] = '\0';
        shm_ptr->request_type = req;
        
        up(sem_id, 0);
        
        down(sem_id, 1);
        printf("result: %d\n", shm_ptr->result);

        up(sem_id, 2);
    }
    shmdt(shm_ptr);
    return 0;
}
