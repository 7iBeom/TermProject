#include <stdio.h>
#include <stdlib.h>

#include "SchedulingAlgorithm.h"

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

    // 대기열 생성
    readyQueue = (Process *)malloc(sizeof(Process) * (numProcess+5));
    if (readyQueue == NULL) {
        fprintf(stderr, "메모리 할당을 실패했습니다.");
        exit(-1);
    }
    // 대기열 초기화
    for (int i = 0; i < numProcess+5; i++)
        Initialize(&readyQueue, i);

    runProcess = (Process*)malloc(sizeof(Process));
    Initialize(&runProcess, 0); // 실행 중인 프로세스가 없다는 것을 의미

    printf("\nSRTF 스케줄링 실행\n");
    printf("-------------------------------------------\n");
    printf("Process ID\tBurst Time\tWaitingTime\n");
    printf("-------------------------------------------\n");

    while (doneProcess < numProcess) {
         // 프로세스가 대기열로 진입
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
        else { // 대기열에 프로세스 진입 시 실행 중인 프로세스가 있는 경우, 대기열에 진입한 프로세스의 실행 시간이 적다면 실행
            for (int i = 0; i < newProcess; i++) {
                if (readyQueue[i].processID != -1 && runProcess->burstTime > readyQueue[i].burstTime) {
                    for (int j = 0; j < numProcess; j++) {
                        if (runProcess->processID == showProcess[j].processID) {
                            ShowResult(showProcess[j]);
                            gantt[ganttIndex] = showProcess[j];
                            ganttIndex++;
                            gantt = realloc(gantt, sizeof(ResultElement) * (ganttIndex+1));
                        }
                    }
                    Process temp = *runProcess;
                    *runProcess = readyQueue[i];
                    readyQueue[i] = temp;
                }
            }
        }

        // 대기열 정렬
        Shift(readyQueue, queueIndex); 
        
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
                }
            }
        }

        currentTime++;
    }
    for (int i = 0; i < numProcess; i++)
        total.waitingTime += showProcess[i].waitingTime;

    ShowGanttChart(gantt, ganttIndex);

    SortResult(showProcess, numProcess);
    printf("\n결과\n");
    printf("-------------------------------------------\n");
    printf("Process ID\tBurst Time\tWaitingTime\n");
    printf("-------------------------------------------\n");
    for (int i = 0; i < numProcess; i++)
        ShowResult(showProcess[i]);

    printf("\n전체 실행 시간: %d, 평균 대기 시간: %.1f\n", total.burstTime, (float)total.waitingTime / numProcess);

    free(readyQueue);
    free(runProcess);
    free(showProcess);
}