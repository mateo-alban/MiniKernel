#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "../include/pcb.h"
#include "../include/queue.h"
#include "../include/sync.h"

// Hilo generador de procesos
void* process_generator(void* arg) {

    ready_queue_t* queue =
        (ready_queue_t*) arg;

    int pid_counter = 1;

    while(1) {

        // Esperar tiempo aleatorio
        sleep(rand() % 3 + 1);

        // Crear nuevo PCB
        pcb_t* process =
            malloc(sizeof(pcb_t));

        process->pid = pid_counter++;

        process->burst_time =
            rand() % 10 + 1;

        process->remaining_time =
            process->burst_time;

        process->priority =
            rand() % 5;

        process->arrival_time =
            time(NULL);

        process->state = READY;

        // Insertar en ready queue
        enqueue(queue, process);

        printf(
            "[GENERATOR] "
            "PID=%d BURST=%d PRIORITY=%d\n",

            process->pid,
            process->burst_time,
            process->priority
        );
    }

    return NULL;
}

// CPU simulada
void* cpu_worker(void* arg) {

    ready_queue_t* queue =
        (ready_queue_t*) arg;

    while(1) {

        // Obtener proceso
        pcb_t* process =
            dequeue(queue);

        process->state = RUNNING;

        printf(
            "\n[CPU] Running PID=%d "
            "Remaining=%d\n",

            process->pid,
            process->remaining_time
        );

        // Simular ejecución CPU
        sleep(QUANTUM);

        process->remaining_time -= QUANTUM;

        // Verificar si terminó
        if(process->remaining_time <= 0) {

            process->state = TERMINATED;

            printf(
                "[CPU] Process %d finished\n",
                process->pid
            );

            free(process);
        }
        else {

            process->state = READY;

            printf(
                "[CPU] Process %d paused "
                "Remaining=%d\n",

                process->pid,
                process->remaining_time
            );

            // Volver a ready queue
            enqueue(queue, process);
        }
    }

    return NULL;
}