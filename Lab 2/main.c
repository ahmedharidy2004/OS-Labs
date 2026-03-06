#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sub_tool.h"
int main(int argc, char *argv[]){
    if(argc == 3){
        if(strcmp(argv[2], "-v") == 0) {
            viewAll(argv[1]);
        }
    }
    if(argc == 5 && strcmp(argv[2], "-v") == 0 && strcmp(argv[3], "-n") == 0){
        int target = atoi(argv[4]);
        viewLine(argv[1], target);
    }
    if(argc == 4 && strcmp(argv[2], "-f") == 0){
        int num = atoi(argv[3]);
        viewFirstNLines(argv[1], num);
    }
    if(argc == 4 && strcmp(argv[2], "-l") == 0){
        int num = atoi(argv[3]);
        viewLastNLines(argv[1], num);
    }
    if(argc == 4 && strcmp(argv[2], "-i") == 0) {
        char * line = argv[3];
        InsertEndLineOld(argv[1], line);
    }
    if(argc == 6 && strcmp(argv[2], "-i") == 0 && strcmp(argv[4], "-s") == 0) {
        char * line = argv[3];
        InsertEndLineNew(argv[1], argv[5], line);
    }
    if(argc == 6 && strcmp(argv[2], "-e") == 0 && strcmp(argv[4], "-n") == 0){
        int target = atoi(argv[5]);
        EditLineOld(argv[1],argv[3], target);
    }
    if(argc == 8 && strcmp(argv[2], "-e") == 0 && strcmp(argv[4], "-n") == 0 &&  strcmp(argv[6], "-s") == 0){
        int target = atoi(argv[5]);
        EditLineNew(argv[1],argv[7], argv[3], target);
    }
    return 0;
}