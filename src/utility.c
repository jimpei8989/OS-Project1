#include "include/utility.h"

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
    if (q->size == 0) 
        ERROR("Try to access element from an empty queue");
    return q->arr[(q->head + q->size - 1) % q->capacity];
}

int QPop(struct Queue *q) {
    if (q->size == 0)
        ERROR("Try to pop from an empty queue");

    int ret = QFront(q);
    q->size -= 1;
    q->head += 1;
    return ret;
}

