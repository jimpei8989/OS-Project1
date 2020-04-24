#ifndef _UTILITY_H
#define _UTILITY_H

#include "include/process.h"

void UNIT();
void ELAPSE(int t);
void ERROR(const char *msg);

struct Queue {
    int head, size, capacity;
    int *arr;
};

struct Queue *newQueue(int size);
void QPush(struct Queue *q, int x);
int QFront(struct Queue *q);
int QPop(struct Queue *q);

struct PQueue {
    int size, capacity;
    int *arr;
    struct Process *ps;
};

struct PQueue *newPQueue(int size, struct Process *ps);
void PQPush(struct PQueue *pq, int x);
int PQTop(struct PQueue *pq);
int PQPop(struct PQueue *pq);

#endif
