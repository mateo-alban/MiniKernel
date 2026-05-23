#include "../include/queue.h"

#include <stdio.h>

void init_queue(ready_queue_t* queue) {

    queue->front = 0;

    queue->rear = 0;

    queue->size = 0;

    pthread_mutex_init(&queue->mutex, NULL);

    pthread_cond_init(&queue->not_empty, NULL);
}

void enqueue(ready_queue_t* queue, pcb_t* process) {

    // Bloqueo acceso a la cola
    pthread_mutex_lock(&queue->mutex);

    // Insertar proceso
    queue->processes[queue->rear] = process;

    queue->rear = (queue->rear + 1) % MAX_QUEUE;

    queue->size++;

    printf("[QUEUE] Processo %d inserted\n", process->pid);

    // Despertar CPUs esperando procesos
    pthread_cond_signal(&queue->not_empty);

    // Liberar mutex
    pthread_mutex_unlock(&queue->mutex);
}

pcb_t* dequeue(ready_queue_t* queue) {

    pthread_mutex_lock(&queue->mutex);

    
//Esperar mientras la cola esté vacía
    
    while(queue->size == 0) {

        pthread_cond_wait(
            &queue->not_empty,
            &queue->mutex
        );
    }

    pcb_t* process = queue->processes[queue->front];

    queue->front = (queue->front + 1) % MAX_QUEUE;

    queue->size--;

    printf("[QUEUE] Processes %d removed\n",
           process->pid);

    pthread_mutex_unlock(&queue->mutex);

    return process;
}