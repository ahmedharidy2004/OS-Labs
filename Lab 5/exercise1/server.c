#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int WORDS_id, VOWELS_id;
void sigint_handler(int signum) {
    msgctl(WORDS_id, IPC_RMID, NULL);
    msgctl(VOWELS_id, IPC_RMID, NULL);
    exit(0);
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

struct msgbuff
{
    long mtype;
    long client_id;
    char mtext[256];
};
#define MSG_SIZE (sizeof(struct msgbuff) - sizeof(long))
int main() {
    signal(SIGINT,sigint_handler);
    key_t vkey_id, wkey_id;
    int rec_val;

    vkey_id = ftok("keyfile", 50);
    wkey_id = ftok("keyfile", 40);
    WORDS_id = msgget(wkey_id, 0666 | IPC_CREAT);
    VOWELS_id = msgget(vkey_id, 0666 | IPC_CREAT);
    struct msgbuff msg;
    sleep(10);
    while(1){
        // checking for word
        rec_val = msgrcv(WORDS_id, &msg, MSG_SIZE, 1, IPC_NOWAIT | MSG_NOERROR);
        if(rec_val != -1){
            int nWords = count_words(msg.mtext);
            struct msgbuff reply;
            reply.mtype = msg.client_id;
            sprintf(reply.mtext, "%d", nWords);
            msgsnd(WORDS_id, &reply, sizeof(reply.mtext), 0);
            sleep(3);
        }
        // checking for vowels
        rec_val = msgrcv(VOWELS_id, &msg, MSG_SIZE, 1, IPC_NOWAIT | MSG_NOERROR);
        if(rec_val != -1){
            int nVowels = count_vowels(msg.mtext);
            struct msgbuff reply;
            reply.mtype = msg.client_id;
            sprintf(reply.mtext, "%d", nVowels);
            msgsnd(VOWELS_id, &reply, sizeof(reply.mtext), 0);
            sleep(3);
        }
    }
}