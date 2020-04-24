#include "include/utility.h"
#include "include/process.h"

#include <stdio.h>

const int PERIOD = 500;

int RR(int N, struct Process* processes) {
    int idx = 0, running = -1;
    int currentTime = 0, TTL = 0;

    struct Queue *q = newQueue(N);

    while (1) {
        // Enqueue all ready processes
        while (idx < N && processes[idx].readyTime >= currentTime) {
            QPush(idx++);
        }

        // Start / wakeup a process
        if (running == -1 && q.size > 0) {
            running = QPop(q);
            if (processes[running] == -1) {
                processes[running].pid = startProcess(processes[running]);
            } else {
                wakeProcess(processes[running].pid);
            }
        }

        UNIT();
        currentTime += 1;
        if (running != -1) {
            processes[running].executionTime -= 1;
            TTL -= 1;
        }

        // Check if process ends or TTL = 0
        if (running != -1) {
            if (processes[running].executionTime == 0) {
                printf("%s %d\n", processes[running].name,
                        processes[running].pid);
                running = -1;
                if (idx == N && q.size == 0) break;
            } else if (TTL == 0) {
                blockProcess(running);
                QPush(running);
                running = -1;
            }
        }
    }
    return 0;
}

