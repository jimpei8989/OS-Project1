#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/process.h"
#include "include/fifo.h"

int procCmp(const void *a, const void *b) {
    struct Process *pa = (struct Process*) a;
    struct Process *pb = (struct Process*) b;
    return pa->readyTime == pb->readyTime ?
        pa->executionTime - pb->executionTime :
        pa->readyTime - pb->readyTime;
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
    
    // Assign self to CPU 0
    assignCPU(getuid(), 0);
    
    if (strcmp(policy, "FIFO") == 0) {
        FIFO(N, processes);
    } else if (strcmp(policy, "RR") == 0) {
        /* RR(N, processes); */
    } else if (strcmp(policy, "SJF") == 0) {
        /* SJF(N, processes); */
    } else if (strcmp(policy, "PSJF") == 0) {
        /* PSJF(N, processes); */
    } else {
        fprintf(stderr, "Error: Wrong scheduling policy.");
    }
}

