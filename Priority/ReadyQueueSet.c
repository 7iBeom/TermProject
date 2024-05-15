#include <stdio.h>
#include <stdlib.h>

#include "Priority.h"

// Queue 초기화 (Ready Queue에 있던 프로세스가 실행되는 과정)
void Initialize(Process** process, int index) {
    (*process)[index].processID = -1;
    (*process)[index].arrivalTime = 0;
    (*process)[index].burstTime = 0;
    (*process)[index].priority = 0;
}
