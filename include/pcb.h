#ifndef PCB_H
#define PCB_H
#include <time.h>

typedef enum{

    READY, // Estados del proceso
    RUNNING, 
    TERMINATED

} process_state_t;

typedef struct {

    int pid; // identificador del proceso

    int burst_time; // Tiempo de uso del CPU del proceso

    int remaining_time; // Tiempo restante de uso

    int priority; // Prioridad de proceso

    int arrival_time; // Momento de llegada del prceso

    process_state_t state;

    // Primera vez ejecutado
    time_t first_run_time;

    // Tiempo finalización
    time_t completion_time;

    // Evita registrar varias veces
    int has_started;

} pcb_t;

#endif