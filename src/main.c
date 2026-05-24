#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "../include/metrics.h"
#include "../include/pcb.h"
#include "../include/queue.h"
#include "../include/sync.h"

#define N_CPUS 2

int main() {

    srand(time(NULL));

    ready_queue_t queue;

    init_queue(&queue);
    init_metrics();

// Generador de hilos
    pthread_t generator_thread;

    pthread_create(
        &generator_thread,
        NULL,
        process_generator,
        &queue
    );

// CPU simulado
    pthread_t cpu_threads[N_CPUS];

    for(int i = 0; i < N_CPUS; i++) {

        pthread_create(
            &cpu_threads[i],
            NULL,
            cpu_worker,
            &queue
        );
    }

// Espera los hilos
    pthread_join(
        generator_thread,
        NULL
    );

    for(int i = 0; i < N_CPUS; i++) {

        pthread_join(
            cpu_threads[i],
            NULL
        );
    }

    return 0;
}