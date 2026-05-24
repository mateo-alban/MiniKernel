#ifndef METRICS_H
#define METRICS_H

#include <pthread.h>
#include <time.h>

// Procesos terminados
extern int completed_processes;

// Tiempo inicial del sistema
extern time_t system_start_time;

// Mutex para métricas
extern pthread_mutex_t metrics_mutex;

// Inicializa métricas
void init_metrics();

// Registro proceso completado
void register_completed_process();

// Mostrar throughput
void print_throughput();

#endif