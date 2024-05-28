#include <stdio.h>
#include <stdlib.h>

#include "SchedulingAlgorithm.h"

// Queue 초기화 (Ready Queue에 있던 프로세스가 실행되는 과정)
void Initialize(Process** process, int index) {
    (*process)[index].processID = -1;
    (*process)[index].arrivalTime = 0;
    (*process)[index].burstTime = 0;
    (*process)[index].priority = 0;
}

// 결과 출력 함수
void ShowResult(ResultElement process) {

    printf("%2d\t\t%2d\t\t%2d\t\t\n", process.processID, process.burstTime, process.waitingTime);
}

// 대기열 정렬 함수
void Shift(Process process[], int size) {
    Process temp;
    for (int i = 0; i <= size; i++) {
        int j = 1;
        if (process[i].processID != -1 && process[i-j].processID == -1 && i - j >= 0) {
            temp = process[i-j];
            process[i-j] = process[i];
            process[i] = temp;
            j++; 
        }
    }
}

// 다음 실행될 프로세스 찾는 함수 (SRTF)
int nextRun(Process* process, int size) {
    int index = 0;
    Process highPriority = *process;

    for (int i = 0; i < size; i++) {
        if (highPriority.processID == -1 && process[i].processID != -1) {
            highPriority = process[i];
            index = i;
            break;
        }
    }

    for (int i = 0; i < size; i++) {
        if (process[i].processID != -1) {
            if (highPriority.burstTime > process[i].burstTime) {
                highPriority = process[i];
                index = i;
            }
            else if (highPriority.burstTime == process[i].burstTime && highPriority.arrivalTime > process[i].arrivalTime) {
                highPriority = process[i];
                index = i;
            }
        }
        
    }
    return index;
}

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

void SortResult(ResultElement process[], int numProcess) {
    ResultElement temp;
    for (int i = 0; i < numProcess; i++) {
        for (int j = i+1; j < numProcess; j++) {
            if (process[i].processID > process[j].processID) {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
}