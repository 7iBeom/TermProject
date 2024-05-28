// FCFS Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // 윈도우에서 실행 시 <io.h>로 변경하고 경로 '\'로 변경

#include "SchedulingAlgorithm.h"

int main(int argc, char *argv[]) {

    char *lastSlash = strrchr(argv[0], '/');
    char buff[1024];
    if (lastSlash != NULL) {
        *lastSlash = '\0'; // 
        strcat(buff, argv[0]);
        
    }
    strcat(buff, "/inputFile/scheduling.txt");

    Process *process = NULL;
    int numProcess = OpenFile(buff, &process);
    if (numProcess == -1) {
        printf("Failed to open file.\n");
        return EXIT_FAILURE;
    }

    // 1번 프로세스의 도착 시간으로 모든 프로세스의 도착 시간 통일
    for (int i = 0; i < numProcess; i++) 
        process[i].arrivalTime = process[0].arrivalTime;

    // List of process
    printf("\nRound Robin 스케줄링\n");
    printf("\n입력\n");
    printf("-------------------------------------------------------------\n");
    printf("Process ID\t Arrival Time\t Burst Time\t Time Quantum\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < numProcess; i++) {
        printf("%2d\t\t %2d\t\t %2d\t\t %2d\n", process[i].processID, process[i].arrivalTime, process[i].burstTime, process[0].priority);
    }

    // Sort by Arrival Time
    Sort(process, numProcess);

    // Run Scheduling Algorithm
    RR(process, numProcess);

    free(process);
    return 0;
}