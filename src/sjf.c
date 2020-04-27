#include "include/utility.h"
#include "include/process.h"

#include <stdio.h>
#include <sys/wait.h>

int SJF(int N, struct Process* processes) {
    int idx = 0, running = -1;
    int currentTime = 0;

    struct PQueue *pq = newPQueue(N, processes);

    while (1) {
        // Enqueue all ready processes
        while (idx < N && processes[idx].readyTime <= currentTime) {
            processes[idx].pid = startProcess(processes[idx]);
            PQPush(pq, idx++);
        }

        // Start / wakeup a process
        if (running == -1 && pq->size > 0) {
            running = PQPop(pq);
            wakeProcess(processes[running].pid);
        }

        // Elapse
        UNIT();
        currentTime += 1;
        if (running != -1) {
            processes[running].executionTime -= 1;
        }

        // Check if process ends
        if (running != -1 && processes[running].executionTime == 0) {
            waitpid(processes[running].pid, NULL, 0);
            running = -1;
        }

        // Check if all done
        if (running == -1 && idx == N && pq->size == 0)
            break;
    }
    return 0;
}

