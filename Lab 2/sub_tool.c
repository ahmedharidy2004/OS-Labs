#include <stdio.h>
#include "sub_tool.h"
#include <stdlib.h>
#include <string.h>
int getfileLinesNumber(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: File does not exist.\n");
        exit(0);
    }
    int n = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
    n++;
    }
    fclose(fp);
    return n;
}

void viewAll(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
    printf("%s", buffer);
    }
    fclose(fp);
}

void viewLine(const char *filename, int target){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    char buffer[256];
    int n = getfileLinesNumber(filename);
    if(target < 1 || target > n){
        fprintf(stderr, "Error: Line out of bounds.\n");
        fclose(fp);
        exit(0);
    }
    int current = 1;
    while(fgets(buffer, sizeof(buffer), fp)){
        if(current == target){
            printf("%s", buffer);
            break;
        }
        current++;
    }
    fclose(fp);
}

void viewFirstNLines(const char *filename, int num){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    int n = getfileLinesNumber(filename);
    if (num > n) {
        fprintf(stderr, "Error: File limit exceeded.\n");
        fclose(fp);
        exit(0);
    }
    char buffer[256];
    int current = 1;
    while(fgets(buffer, sizeof(buffer), fp)){
        printf("%s", buffer);
        current++;
        if(current > num) break;
    }
    fclose(fp);
}

void viewLastNLines(const char *filename, int num) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }

    int n = getfileLinesNumber(filename);
    if (num > n) {
        fprintf(stderr, "Error: File limit exceeded.\n");
        fclose(fp);
        exit(0);
    }

    char buffer[256];
    int current = 1;
    int start = n - num + 1;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (current >= start) {
            printf("%s", buffer);
        }
        current++;
    }

    fclose(fp);
}

void InsertEndLineOld(const char *filename, char *line){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    fputs(line, fp);
    fclose(fp);
    return;
}

void InsertEndLineNew(const char *filename,const char *outfile,char *line){
    FILE *fp = fopen(filename, "r");
    FILE *fp2 = fopen(outfile, "w");
    char last_char;
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    if (fp2 == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
    fputs(buffer, fp2);
    last_char = buffer[strlen(buffer) - 1];
    }
    if (last_char != '\n') fputs("\n", fp2);
    fputs(line, fp2);
    fclose(fp);
    fclose(fp2);
    return;
}

void EditLineNew(const char *filename,const char *outfile,char *line, int target){
    FILE *fp = fopen(filename, "r");
    FILE *fp2 = fopen(outfile, "w");
    int curr = 1;
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    if (fp2 == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
    if(curr == target) {
        fputs(line, fp2);
        fputs("\n", fp2);
    }
    else fputs(buffer, fp2);
    curr++;
    }
    fclose(fp);
    fclose(fp2);
    return;
}

void EditLineOld(const char *filename, const char *line, int target)
{
    FILE *fp  = fopen(filename, "r");
    FILE *fp2 = fopen("temp.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    if (fp2 == NULL) {
        fprintf(stderr, "Error: File does not exist.\n");
        exit(0);
    }
    char buffer[256];
    int curr = 1;
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (curr == target) {
            fputs(line, fp2);
            fputs("\n", fp2);
        } else {
            fputs(buffer, fp2);
        }
        curr++;
    }
    fclose(fp);
    fclose(fp2);
    remove(filename);
    rename("temp.txt", filename);
}