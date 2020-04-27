#include "include/utility.h"
#include "include/process.h"

#include <stdio.h>
#include <sys/wait.h>

const int PERIOD = 500;

int RR(int N, struct Process* processes) {
    int idx = 0, running = -1;
    int currentTime = 0, TTL = 0;

    struct Queue *q = newQueue(N);

    while (1) {
        // Enqueue all ready processes
        while (idx < N && processes[idx].readyTime <= currentTime) {
            processes[idx].pid = startProcess(processes[idx]);
            QPush(q, idx++);
        }

        // If TTL = 0
        if (running != -1 && TTL == 0) {
            blockProcess(processes[running].pid);
            QPush(q, running);
            running = -1;
        }

        // Start / wakeup a process
        if (running == -1 && q->size > 0) {
            running = QPop(q);
            wakeProcess(processes[running].pid);
            TTL = PERIOD;
        }

        // Elapse
        UNIT();
        currentTime += 1;
        if (running != -1) {
            processes[running].executionTime -= 1;
            TTL -= 1;
        }

        // Check if process ends or TTL = 0
        if (running != -1 && processes[running].executionTime == 0) {
            waitpid(processes[running].pid, NULL, 0);
            running = -1;
        }

        // Check if all done
        if (running == -1 && idx == N && q->size == 0)
            break;
    }
    return 0;
}

