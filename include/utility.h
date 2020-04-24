#ifndef _UTILITY_H
#define _UTILITY_H

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

#endif
