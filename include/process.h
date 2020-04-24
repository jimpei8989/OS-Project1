#ifndef _PROCESS_H
#define _PROCESS_H

#include <sys/types.h>

struct Process {
    char name[40];
    int readyTime, executionTime;
    pid_t pid;
};

void assignCPU(const pid_t pid, int cpu);
void blockProcess(const pid_t pid);
void wakeProcess(const pid_t pid);
pid_t startProcess(struct Process process);

#endif
