#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "../include/metrics.h"

// Procesos terminados
int completed_processes = 0;

// Tiempo inicio sistema
time_t system_start_time;

// Mutex métricas
pthread_mutex_t metrics_mutex;

// Inicializar métricas
void init_metrics() {

    system_start_time =
        time(NULL);

    pthread_mutex_init(
        &metrics_mutex,
        NULL
    );
}

// Registrar proceso completado
void register_completed_process() {

    pthread_mutex_lock(
        &metrics_mutex
    );

    completed_processes++;

    pthread_mutex_unlock(
        &metrics_mutex
    );
}

// Mostrar throughput
void print_throughput() {

    time_t current_time =
        time(NULL);

    double elapsed_time =

        difftime(
            current_time,
            system_start_time
        );

    if(elapsed_time <= 0) {

        elapsed_time = 1;
    }

    double throughput =

        completed_processes
        / elapsed_time;

    printf(
        "[METRICS] Throughput = "
        "%.2f processes/sec\n",

        throughput
    );
}