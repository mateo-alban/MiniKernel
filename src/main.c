#include <stdio.h>
#include <stdlib.h>

#include "../include/pcb.h"
#include "../include/queue.h"

int main() {

    // Crear cola ready
    ready_queue_t queue;

    init_queue(&queue);

// Creo procesos de prueba

    pcb_t* p1 = malloc(sizeof(pcb_t));

    pcb_t* p2 = malloc(sizeof(pcb_t));

    pcb_t* p3 = malloc(sizeof(pcb_t));

// Inicializo procesos

    p1->pid = 1;
    p1->burst_time = 5;

    p2->pid = 2;
    p2->burst_time = 8;

    p3->pid = 3;
    p3->burst_time = 3;

// Insertar en la cola

    enqueue(&queue, p1);

    enqueue(&queue, p2);

    enqueue(&queue, p3);

// Saco procesos

    pcb_t* process;

    process = dequeue(&queue);

    printf("Running process %d\n",
           process->pid);

    process = dequeue(&queue);

    printf("Running process %d\n",
           process->pid);

    process = dequeue(&queue);

    printf("Running process %d\n",
           process->pid);

// Libero memoria

    free(p1);

    free(p2);

    free(p3);

    return 0;
}