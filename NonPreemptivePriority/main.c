// Priority Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // 윈도우에서 실행 시 <io.h>로 변경하고 경로 '\'로 바꾸기

#include "SchedulingAlgorithm.h"

// Sort by Arrival Time
void Sort(Process process[], int numProcess) {
    Process temp;
    for (int i = 0; i < numProcess; i++) {
        for (int j = i+1; j < numProcess; j++) {
            if (process[i].arrivalTime > process[j].arrivalTime) {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
}

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
    printf("선점형 우선순위 스케줄링\n");
    printf("입력\n");
    printf("---------------------------------------------------------\n");
    printf("Process ID\t Arrival Time\t Burst Time\t Priority\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < numProcess; i++) {
        printf("%2d\t\t %2d\t\t %2d\t\t %2d\n", process[i].processID, process[i].arrivalTime, process[i].burstTime, process[i].priority);
    }

    // Sort by Arrival Time
    Sort(process, numProcess);

    // Run Scheduling Algorithm
    SchedulingAlgorithm(process, numProcess);

    free(process);
    return 0;

    
}