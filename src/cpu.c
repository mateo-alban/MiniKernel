#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "../include/metrics.h"
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

        process->burst_time =  rand() % 10 + 1;

        process->remaining_time = process->burst_time;

        process->priority = rand() % 5;

        process->arrival_time = time(NULL);

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

    ready_queue_t* queue = (ready_queue_t*) arg;

    while(1) {

        // Obtener proceso
        pcb_t* process = dequeue(queue);

        process->state = RUNNING;

// Registrar primera ejecución
if(!process->has_started) {

    process->first_run_time =  time(NULL);

    process->has_started = 1;

    int response_time =  process->first_run_time - process->arrival_time;

    printf("[METRICS] PID=%d " "Response Time=%d sec\n", process->pid, response_time);
}
        
    printf( "\n[CPU] Running PID=%d " "Remaining=%d\n", process->pid, process->remaining_time);

        // Simular ejecución CPU
        sleep(QUANTUM);

        process->remaining_time -= QUANTUM;

        // Verificar si terminó
        if(process->remaining_time <= 0) {

            process->state = TERMINATED;

            process->completion_time = time(NULL);

            int turnaround_time = process->completion_time - process->arrival_time;

            printf("[CPU] Process %d finished\n", process->pid);

            printf("[METRICS] PID=%d " "Turnaround=%d sec\n", process->pid, turnaround_time);
            register_completed_process();

            print_throughput();

            free(process);
        }else {

        process->state = READY;

         // Vuelve a ready queue
         enqueue(queue, process);
        }
    }

    return NULL;
}