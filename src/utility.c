#include "include/utility.h"
#include "include/process.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void UNIT() {
    for(volatile unsigned long i = 0; i < 1000000UL; i++);
} 

void ELAPSE(int t) {
    while (t--) {
        UNIT();
    }
}

void ERROR(const char *msg) {
    perror(msg);
    exit(1);
}

struct Queue* newQueue(int size) {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->head = 0;
    q->size = 0;
    q->capacity = size;
    q->arr = (int*)calloc(size, sizeof(int));
    return q;
}

void QPush(struct Queue *q, int x) {
    if (q->size == q->capacity)
        ERROR("Try to push elements into a full queue");

    q->arr[(q->head + q->size) % q->capacity] = x;
    q->size += 1;
}

int QFront(struct Queue *q) {
    if (q->size == 0) ERROR("Try to access element from an empty queue");
    return q->arr[q->head];
}

int QPop(struct Queue *q) {
    if (q->size == 0) ERROR("Try to pop from an empty queue");

    int ret = q->arr[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size -= 1;

    return ret;
}

struct PQueue *newPQueue(int size, struct Process *ps) {
    struct PQueue *pq = (struct PQueue*)malloc(sizeof(struct PQueue));

    pq->size = 0;
    pq->capacity = size;
    pq->arr = (int*)calloc(size + 1, sizeof(int));
    pq->ps = ps;

    return pq;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int LT(struct Process *ps, int a, int b) {
    if (ps[a].executionTime == ps[b].executionTime) {
        return a < b;
    } else {
        return ps[a].executionTime < ps[b].executionTime;
    }
}

void PQPush(struct PQueue *pq, int x) {
    pq->arr[++pq->size] = x;
    int cur = pq->size;

    while (1) {
        if (cur > 1 && LT(pq->ps, pq->arr[cur], pq->arr[cur / 2])) {
            swap(&pq->arr[cur], &pq->arr[cur / 2]);
            cur /= 2;
        } else {
            break;
        }
    }
}

int PQTop(struct PQueue *pq) {
    if (pq->size == 0) ERROR("Try to access element from an empty pqueue");
    return pq->arr[1];
}

int PQPop(struct PQueue *pq) {
    if (pq->size == 0) ERROR("Try to pop from an empty pqueue");
    int ret = pq->arr[1];

    pq->arr[1] = pq->arr[pq->size--];
    int cur = 1;
    while (1) {
        int change = 0;
        if (cur * 2 + 1 <= pq->size) {
            if (LT(pq->ps, pq->arr[cur * 2], pq->arr[cur * 2 + 1])) {
                if (LT(pq->ps, pq->arr[cur * 2], pq->arr[cur])) {
                    change = 1;
                }
            } else {
                if (LT(pq->ps, pq->arr[cur * 2 + 1], pq->arr[cur])) {
                    change = 2;
                }
            }
        } else if (cur * 2 <= pq->size) {
            if (LT(pq->ps, pq->arr[cur * 2], pq->arr[cur])) {
                change = 1;
            }
        }

        if (change == 1) {
            swap(&pq->arr[cur], &pq->arr[cur * 2]);
            cur = cur * 2;
        } else if (change == 2) {
            swap(&pq->arr[cur], &pq->arr[cur * 2 + 1]);
            cur = cur * 2 + 1;
        } else {
            break;
        }
    }
    return ret;
}

