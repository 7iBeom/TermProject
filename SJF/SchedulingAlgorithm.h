#pragma once
#ifndef DATA_H_
#define DATA_H_

// 프로세스 구조체
typedef struct {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
}Process;

// 결과 출력 구조체
typedef struct {
    int processID;
    int burstTime;
    int waitingTime;
} ResultElement;


int OpenFile(const char* filename, Process** process); // 파일 열기
void Initialize(Process** process, int i); // Queue 초기화
void ShowResult(ResultElement process); // 결과 출력
void SchedulingAlgorithm(Process process[], int); // SJF 스케줄링 알고리즘
void Sort(Process process[], int); // 프로그램 정렬
int nextRun(Process* process, int size); // 다음 실행될 프로세스 찾는 함수
void ShowGanttChart(ResultElement[], int); // 간트차트 출력 함수

#endif