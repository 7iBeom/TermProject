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

    // List of process
    printf("\nSRTF 스케줄링\n\n");
    printf("입력\n");
    printf("-------------------------------------------\n");
    printf("Process ID\t Arrival Time\t Burst Time\n");
    printf("-------------------------------------------\n");
    for (int i = 0; i < numProcess; i++) {
        printf("%2d\t\t %2d\t\t %2d\n", process[i].processID, process[i].arrivalTime, process[i].burstTime);
    }

    // Sort by Arrival Time
    Sort(process, numProcess);

    // Run Scheduling Algorithm
    SchedulingAlgorithm(process, numProcess);

    free(process);
    return 0;

    
}