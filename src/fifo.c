#include "include/utility.h"
#include "include/process.h"

#include <stdio.h>
#include <sys/wait.h>

int FIFO(int N, struct Process* processes) {
    int idx = 0, running = -1;
    int currentTime = 0;

    struct Queue *q = newQueue(N);

    while (1) {
        // Check if a new ready process is going to start
        while (idx < N && processes[idx].readyTime <= currentTime) {
            processes[idx].pid = startProcess(processes[idx]);
            QPush(q, idx++);
        }

        if (running == -1 && q->size > 0) {
            running = QPop(q);
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
            printf("%s %d\n", processes[running].name,
                    processes[running].pid);
            waitpid(processes[running].pid, NULL, 0);
            running = -1;
        }
        
        // Check if all done
        if (running == -1 && idx == N && q->size == 0)
            break;
    }
    return 0;
}

