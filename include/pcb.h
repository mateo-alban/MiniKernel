#ifndef PCB_H
#define PCB_H
#include <time.h>

typedef enum{

    READY, // Estados del proceso
    RUNNING, 
    TERMINATED

} process_state_t;

typedef struct {

    int pid;

    int burst_time;

    int remaining_time;

    int priority;

    int arrival_time;

    process_state_t state;

    // Primera vez ejecutado
    time_t first_run_time;

    // Tiempo finalización
    time_t completion_time;

    // Evita registrar varias veces
    int has_started;

} pcb_t;

#endif