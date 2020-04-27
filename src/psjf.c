#include "include/utility.h"
#include "include/process.h"

#include <stdio.h>
#include <sys/wait.h>

int PSJF(int N, struct Process* processes) {
    int idx = 0, running = -1;
    int currentTime = 0;

    struct PQueue *pq = newPQueue(N, processes);

    while (1) {
        // Enqueue all ready processes
        while (idx < N && processes[idx].readyTime <= currentTime) {
            processes[idx].pid = startProcess(processes[idx]);
            PQPush(pq, idx++);
        }

        // Check if running is current shortest
        if (running != -1 && pq->size > 0 && processes[running].executionTime > processes[PQTop(pq)].executionTime) {
            blockProcess(processes[running].pid);
            PQPush(pq, running);
            running = -1;
        }

        // Start / wakeup a process
        if (running == -1 && pq->size > 0) {
            running = PQPop(pq);
            wakeProcess(processes[running].pid);
        }

        // Elapse
        UNIT();
        currentTime += 1;
        if (running != -1)
            processes[running].executionTime -= 1;

        // Check if process ends or TTL = 0
        if (running != -1) {
            if (processes[running].executionTime == 0) {
                printf("%s %d\n", processes[running].name, processes[running].pid);
                waitpid(processes[running].pid, NULL, 0);
                running = -1;
            }
        }

        // Check if all done
        if (running == -1 && idx == N && pq->size == 0)
            break;
    }
    return 0;
}
