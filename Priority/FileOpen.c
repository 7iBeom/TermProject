#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Priority.h"

// 파일 오픈 함수
int OpenFile(const char* filename, Process** process) {
    FILE* file;
    int line = 0;
    int i = 0;

    // 파일 오픈
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return -1;
    }

    char bin[50];
    while (fgets(bin, sizeof(bin), file) != 0) {
        line++;
    }

    rewind(file);

    *process = (Process*)malloc(sizeof(Process) * (line));
    if (*process == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return -1;
    }

    while (i < line &&fscanf(file, "%s %d %d %d %d", bin, &(*process)[i].processID, &(*process)[i].arrivalTime, &(*process)[i].burstTime, &(*process)[i].priority) == 5) {
        i++;
    }


    fclose(file);
    return line;
}