# FCFS 의사 코드

    function FCFS(processes):
        # processes는 (PID, AT, BT, Priority)로 구성된 구조체 배열
        processes를 AT가 작은 순서로 정렬

        currentTime, doneTask = 0
        numProcess = 프로세스의 수
        readyQueue # 대기열을 구현하기 위한 구조체 배열, 선입선출의 큐 형식이다.
        runProcess # 실행 중인 프로세스를 구현하기 위한 구조체 배열

        jobResult # (PID, BT, WT)로 구성된 구조체 배열
        
        while doneTask < numProcess:
            for process in Processes:
                if process.AT == currentTime:
                    readyQueue = process
            
            if runProcess.PID == -1;
                runProcess = (readyQueue)를 매개 변수로 AT가 가장 작은 프로세스를 반환하는 함수

            if runProcess.BT != 0:
                runProcess.Bt -=1
                if runProcess.BT == 0:
                    doneTask += 1
                    runProcess 초기화
            
            currentTime += 1

