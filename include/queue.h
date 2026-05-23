#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

#include "pcb.h"

#define MAX_QUEUE 100

typedef struct {

    pcb_t* processes[MAX_QUEUE];

    int front;

    int rear;

    int size;

    pthread_mutex_t mutex;

    pthread_cond_t not_empty;

} ready_queue_t;

void init_queue(ready_queue_t* queue);

void enqueue(ready_queue_t* queue,
             pcb_t* process);

pcb_t* dequeue(ready_queue_t* queue);

#endif