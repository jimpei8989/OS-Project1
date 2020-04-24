#include "include/utility.h"
#include "include/process.h"

#include <stdio.h>

int FIFO(int N, struct Process* processes) {
    int idx = 0, running = -1;
    int currentTime = 0;

    while (1) {
        // Check if a new ready process is going to start
        if (running == -1 && processes[idx].readyTime >= currentTime) {
            running = idx++;
            processes[running].pid = startProcess(processes[running]);
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
            running = -1;
            if (idx == N) break;
        }

    }
    return 0;
}

