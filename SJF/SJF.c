﻿#include <stdio.h>
#include <stdlib.h>

#include "SchedulingAlgorithm.h"

// 결과 출력 함수
void ShowResult(ResultElement process) {

    printf("%2d\t\t%2d\t\t%2d\t\t\n", process.processID, process.burstTime, process.waitingTime);
}

// 준비 큐 정렬 함수
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

// 다음 실행될 프로세스 찾는 함수
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
            else if (highPriority.burstTime == process[i].burstTime && highPriority.arrivalTime == process[i].arrivalTime && highPriority.processID > process[i].arrivalTime) {
                highPriority = process[i];
                index = i;
            }
        }
        
    }
    return index;
}

// 스케줄링 알고리즘
void SchedulingAlgorithm(Process process[], int numProcess) {
    Process *runProcess, *readyQueue;
    int newProcess = 0, currentTime = 0, queueIndex = 0;
    int emptyIndex = 0, doneProcess = 0, ganttIndex = 0;

    
    ResultElement total = { -1, 0, 0 };
    ResultElement *showProcess = (ResultElement*)malloc(numProcess * sizeof(ResultElement));
    ResultElement *gantt = (ResultElement*)malloc(sizeof(ResultElement) * (ganttIndex+1));

    for (int i = 0; i < numProcess; i++) {
        int PID = process[i].processID;
        showProcess[i].processID = PID;
        showProcess[i].burstTime = 0;
        showProcess[i].waitingTime = 0;
    }

    // Ready Queue 생성
    readyQueue = (Process *)malloc(sizeof(Process) * (numProcess+5));
    if (readyQueue == NULL) {
        fprintf(stderr, "메모리 할당을 실패했습니다.");
        exit(-1);
    }
    // Ready Queue 초기화
    for (int i = 0; i < numProcess+5; i++)
        Initialize(&readyQueue, i);

    runProcess = (Process*)malloc(sizeof(Process));
    Initialize(&runProcess, 0); // 실행 중인 프로세스가 없다는 것을 의미

    printf("\n----------------------\n");
    printf("SJF 스케줄링 실행\n");
    printf("----------------------\n\n");
    printf("출력\n");
    printf("-------------------------------------------\n");
    printf("Process ID\tBurst Time\tWaitingTime\n");
    printf("-------------------------------------------\n");

    while (doneProcess < numProcess) {
         // 프로세스가 ready queue로 진입
        for (int i = 0; i < numProcess; i++) {
            if (readyQueue[queueIndex].processID == -1 && process[i].processID != -1 && currentTime == process[i].arrivalTime) {
            readyQueue[queueIndex] = process[i];
            queueIndex++;
            newProcess++;
            }
        }

        // 실행 중인 프로세스가 없는 경우
        if (runProcess->processID == -1) {
            int index = nextRun(readyQueue, queueIndex);
            *runProcess = readyQueue[index];
            Initialize(&readyQueue, index);
        }

        // 준비 큐 정렬
        Shift(readyQueue, queueIndex); 
        for (int i = 0; i < queueIndex; i++) printf("%d ", readyQueue[i].processID); printf("\n");
        
        // 프로세스 실행
        if (runProcess->burstTime != 0) {
            for (int i = 0; i < numProcess; i++) {
                if (runProcess->processID == process[i].processID) {
                    showProcess[i].processID = runProcess->processID;
                    showProcess[i].burstTime = process[i].burstTime - (--runProcess->burstTime);
                    total.burstTime++;
                    // 실행 프로세스 종료
                    if (runProcess->burstTime == 0) {
                        for (int j = 0; j < numProcess; j++) {
                            if (showProcess[j].processID == runProcess->processID) {
                                ShowResult(showProcess[j]);
                                gantt[ganttIndex] = showProcess[j];
                                ganttIndex++;
                                gantt = realloc(gantt, sizeof(ResultElement) * (ganttIndex+1));
                            }
                        }
                        doneProcess++;
                        Initialize(&runProcess, 0);
                    }
                }
            }
        }
        // 대기 중인 프로세스 대기 시간 추가
        for (int i = 0; i < queueIndex; i++) {
            for (int j = 0; j < newProcess; j++) {
                if (readyQueue[i].processID == showProcess[j].processID) {
                    showProcess[j].waitingTime++;
                    gantt[ganttIndex] = showProcess[j];
                    total.waitingTime++;
                }
            }
        }

        currentTime++;
    }
    ShowGanttChart(gantt, ganttIndex);
    printf("\n전체 실행시간: %d, 평균 대기시간: %.1f\n", total.burstTime, (float)total.waitingTime / numProcess);

    free(readyQueue);
    free(runProcess);
    free(showProcess);
}