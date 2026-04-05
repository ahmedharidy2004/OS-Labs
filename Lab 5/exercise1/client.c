#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
struct msgbuff
{
    long mtype;
    long client_id;
    char mtext[256];
};
#define MSG_SIZE (sizeof(struct msgbuff) - sizeof(long))
int main() {
    key_t vkey_id, wkey_id;
    int WORDS_id, VOWELS_id, send_val, rec_val;

    vkey_id = ftok("keyfile", 50);
    wkey_id = ftok("keyfile", 40);
    WORDS_id = msgget(wkey_id, 0666 | IPC_CREAT);
    VOWELS_id = msgget(vkey_id, 0666 | IPC_CREAT);

    long client_id = getpid() % 10000;
    while(1){
    // taking input from the user
    char queue_choice[10];
    char sentence[256];

    printf("Enter queue (1 for WORDS/2 for VOWELS): ");
    fgets(queue_choice, sizeof(queue_choice), stdin);
    queue_choice[strcspn(queue_choice, "\n")] = '\0';

    printf("Enter sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0';

    // preparing the msg
    struct msgbuff msg;
    msg.mtype = 1;
    msg.client_id = client_id;
    strcpy(msg.mtext, sentence);

    // sending the message to the server
    if(!strcmp(queue_choice, "1")){
        send_val = msgsnd(WORDS_id, &msg, MSG_SIZE, 0);
    }
    else if(!strcmp(queue_choice, "2")){
        send_val = msgsnd(VOWELS_id, &msg, MSG_SIZE, 0);
    }

    if (send_val == -1)
        perror("Errror in send");

    // waiting for the response from the server
    if(!strcmp(queue_choice, "1")){
        rec_val = msgrcv(WORDS_id, &msg, MSG_SIZE, client_id, MSG_NOERROR);
    }
    else if(!strcmp(queue_choice, "2")){
        rec_val = msgrcv(VOWELS_id, &msg, MSG_SIZE, client_id, MSG_NOERROR);
    }
    if (rec_val == -1){
        perror("Error in receive");
    }
    else{
    printf("result: %s\n", msg.mtext);
    }
}
}
