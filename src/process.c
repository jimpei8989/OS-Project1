#define _GNU_SOURCE

#include "include/process.h"
#include "include/utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>

void assignCPU(const pid_t pid, int cpu) {
    if (cpu > (int)sizeof(cpu_set_t))
        ERROR("CPU index error");

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu, &mask);

    if (sched_setaffinity(pid, sizeof(mask), &mask) < 0)
        ERROR("Setting CPU affinity");
}

void blockProcess(const pid_t pid) {
    struct sched_param param;
    param.sched_priority = 1;

    if (sched_setscheduler(pid, SCHED_FIFO, &param) < 0) 
        ERROR("Set scheduler [1]");
}

void wakeProcess(const pid_t pid) {
    struct sched_param param;
    param.sched_priority = 99;

    if (sched_setscheduler(pid, SCHED_FIFO, &param) < 0) 
        ERROR("Set scheduler [99]");
}

pid_t startProcess(struct Process process) {
    pid_t pid = fork();

    if (pid < 0) {
        ERROR("Fork");
    } else if (pid == 0) {
        // is child
        struct timespec beginTS, endTS;

        if (clock_gettime(CLOCK_REALTIME, &beginTS) < 0)
            ERROR("Clock gettime (begin)");
        
        ELAPSE(process.executionTime);

        if (clock_gettime(CLOCK_REALTIME, &endTS) < 0)
            ERROR("Clock gettime (end)");

        char msg[50];
        sprintf(msg, "[Project1] %d %lu.%09lu %lu.%09lu", getpid(),
                beginTS.tv_sec, beginTS.tv_nsec,
                endTS.tv_sec, endTS.tv_nsec);

        fprintf(stderr, "%s\n", msg);

        exit(0);
    } else {
        // is parent
        blockProcess(pid);
    }
    return pid;
}
