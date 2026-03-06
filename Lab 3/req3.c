#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
    // reading arguments
    char * filename = argv[1];
    const int N = atoi(argv[2]);
    int V = atoi(argv[3]);
    // file open and getting arrays nItems and pItem
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
    perror("fopen");
    return 1;
    }
    // variables declaration
    int i = 1;
    int j = 0;
    char line[100];
    int M;
    int* nItems;
    int* pItem;
    // reading file line by line.
    while (fgets(line, sizeof(line), fp) != NULL) {
        if(i == 1) {
            M = atoi(line);
            nItems = malloc(M * sizeof(int));
            pItem = malloc(M * sizeof(int));
        }
        else {
            sscanf(line, "%d %d", &nItems[j], &pItem[j]);
            j++;
        }
        i++;
    }
    fclose(fp);
    // work with children
    pid_t pids[N];
    for(int i = 0;i<N;i++){
        pids[i] = fork();
        if(pids[i] == 0){
            int c = 0;
            if(i < N - 1){
                
                int start = i * floor(M / N);
                int end = (i + 1) * floor(M / N);
                for(int j = start;j<end;j++) {
                    if(nItems[j] * pItem[j] >= V) c++;
                }
            }
            else if(i == N - 1){
                int start = i * floor(M / N);
                for(int j = start;j<M;j++) {
                    if(nItems[j] * pItem[j] >= V) c++;
                }
            }
            exit(c);
        }
    }
    // waiting for children
    int results[N];
    for (int i = 0; i < N; i++) {
        int stat_loc;
        waitpid(pids[i], &stat_loc, 0);
        results[i] = WEXITSTATUS(stat_loc);
    }
    for(int i = 0;i<N;i++){
        if(i < N - 1) printf("%d ", results[i]);
        else printf("%d", results[i]);
    }
    // freeing memory.
    free(nItems);
    free(pItem);
    nItems = pItem = NULL;
    return 0;
}
