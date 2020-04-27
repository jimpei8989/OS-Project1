#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/process.h"
#include "include/fifo.h"
#include "include/rr.h"
#include "include/sjf.h"
#include "include/psjf.h"

int procCmp(const void *a, const void *b) {
    struct Process *pa = (struct Process*) a, *pb = (struct Process*) b;

    if (pa->readyTime != pb->readyTime) {
        return pa->readyTime - pb->readyTime;
    /* } else if (pa->executionTime != pb->executionTime) { */
    /*     return pa->executionTime - pb->executionTime; */
    } else {
        return strcmp(pa->name, pb->name);
    }
}

int main() {
    char policy[40];
    scanf("%s", policy);

    int N;
    scanf("%d", &N);

    struct Process *processes = (struct Process*)calloc(N, sizeof(struct Process));

    // Handle Input
    for (int i = 0; i < N; i++) {
        scanf("%s%d%d", processes[i].name,
                &processes[i].readyTime, &processes[i].executionTime);
        processes[i].pid = -1;
    }

    qsort(processes, N, sizeof(struct Process), procCmp);
    
    // Assign self to CPU 0, set self to highest
    assignCPU(getuid(), 0);
    wakeProcess(getuid());
    
    if (strcmp(policy, "FIFO") == 0) {
        FIFO(N, processes);
    } else if (strcmp(policy, "RR") == 0) {
        RR(N, processes);
    } else if (strcmp(policy, "SJF") == 0) {
        SJF(N, processes);
    } else if (strcmp(policy, "PSJF") == 0) {
        PSJF(N, processes);
    } else {
        fprintf(stderr, "Error: Wrong scheduling policy.");
    }
}

