#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
int ch, pidA, pidB;
void loserHandler(int signum){
    if(ch == 1) {
        printf("I am child A, and I received from my parent that I am the loser.\n");
        fflush(stdout);
        exit(-1);
    }
    else if(ch == 2){
        printf("I am child B, and I received from my parent that I am the loser.\n");
        fflush(stdout);
        exit(-1);
    }
}

void alarm_handler(int signum) {
    kill(pidA, SIGUSR2);
    kill(pidB, SIGUSR2);
    exit(-1);
}

void not_found_handler(int signum){
    printf("I am the child and I could not find the file.\n");
    fflush(stdout);
    exit(-1);
}
int main(int argc, char* argv[]){
    // ---------- Receving the target and filenames ----------
    int target = atoi(argv[1]);
    int nf = argc - 2;

    int sizeA = (nf + 1) / 2;
    int sizeB = nf - sizeA;

    char *filesA[sizeA];
    char *filesB[sizeB];
    int idxA[sizeA];
    int idxB[sizeB];

    for (int i = 0; i < sizeA; i++) {
        filesA[i] = argv[i + 2];
        idxA[i] = i;
    }

    for (int i = 0; i < sizeB; i++) {
        filesB[i] = argv[i + sizeA + 2];
        idxB[i] = i + sizeA;
    }

    // forking 2 children
    pidA = fork();
    if(pidA != 0) pidB = fork();
    if(pidA == 0){
        ch = 1;
        signal(SIGUSR1, loserHandler);
        signal(SIGUSR2, not_found_handler);
        struct stat info;
        for(int i = 0;i<sizeA;i++){
            if(stat(filesA[i], &info) == 0){
                if(info.st_size == target){
                    printf("I found the file at location %d\n", idxA[i]);
                    fflush(stdout);
                    exit(0);
                }
            }
        }
        pause();
    }
    else if(pidB == 0) {
        ch = 2;
        signal(SIGUSR1, loserHandler);
        signal(SIGUSR2, not_found_handler);
        struct stat info;
        for(int i = 0;i<sizeB;i++){
            if(stat(filesB[i], &info) == 0){
                if(info.st_size == target){
                    printf("I found the file at location %d\n", idxB[i]);
                    fflush(stdout);
                    exit(0);
                }
            }
        }
        pause();
    }
    else{
        signal(SIGALRM, alarm_handler);
        alarm(5);
        int winnerPid = wait(NULL);
        alarm(0);
        if(winnerPid == pidA) {
            printf("Parent: Child A found the file.\n");
            fflush(stdout);
            kill(pidB, SIGUSR1);
        }
        else if(winnerPid == pidB) {
            printf("Parent: Child B found the file.\n");
            fflush(stdout);
            kill(pidA, SIGUSR1);
        }
        wait(NULL);
    }
    return 0;
}
