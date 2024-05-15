#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Priority.h"

#define DRAW(x, y) printf("\033[%d;%dH", (y), (x))
#define SHOW_TEXT(x) printf("\033(B%d",x)

void ShowGanttChart(ResultElement gantt[], int size) {
    int time = 0;
    int x = 1, y = 10, height = 3;
    for (int i = 0; i <15; i++) printf("\n");
    
    DRAW(x-1, y); // 좌측 상단 모서리로 이동
    printf("┌"); // 좌측 상단 모서리 그리기
    for (int i = 1; i < height; ++i) {
        DRAW(x, y + i); // 다음 줄로 이동
        printf("│"); // 세로선 그리기
    }
    DRAW(x, y+height); // 좌측 하단 모서리로 이동
    printf("└"); // 좌측 상단 모서리 그리기

    DRAW(x, y+height+1);
    SHOW_TEXT(time);

    x = 2;
    int i = 0, j = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < gantt[i].burstTime; j++) {
            if (j == 0 & i == 0) {
                x++;
                DRAW(x+j-1, y); // 다음 줄로 이동
                printf("─");
                DRAW(x+j-1, y+height); // 다음 줄로 이동
                printf("─");
            }
            DRAW(x+j, y); // 다음 줄로 이동
            printf("─");
            DRAW(x+j, y+height); // 다음 줄로 이동
            printf("─"); 
        } 
        x+=gantt[i].burstTime;
        if (i == size-1) {
            DRAW(x, y); // 좌측 상단 모서리로 이동
            printf("┐"); // 좌측 상단 모서리 그리기
            for (int i = 1; i < height; ++i) {
                DRAW(x, y + i); // 다음 줄로 이동
                printf("│"); // 세로선 그리기
            }
            DRAW(x, y+height); // 좌측 하단 모서리로 이동
            printf("┘"); // 좌측 상단 모서리 그리기
        } 
        else {
            x++;
            DRAW(x-1, y); // 다음 줄로 이동
            printf("┬"); // 세로선 그리기
            for (int j = 1; j < height; ++j) {
                DRAW(x-1, y + j); // 다음 줄로 이동
                printf("│"); // 세로선 그리기
            }
            DRAW(x-1, y+height); // 다음 줄로 이동
            printf("┴"); // 세로선 그리기

            
        }
        DRAW(x-2, y+height-1);    
        SHOW_TEXT(gantt[i].processID);

        time += gantt[i].burstTime;
        DRAW(x-1, y+height+1);
        SHOW_TEXT(time);
    }
    printf("\n");
    printf("\033(B");
}