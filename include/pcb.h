#ifndef PCB_H
#define PCB_H
typedef enum{

    READY, // Estados del proceso
    RUNNING, 
    TERMINATED

} process_state_t;

typedef struct {

    int pid; // Id del proceso

    int burst_time; // Tiempo total del CPU

    int remaining_time; // Tiempo restante

    int priority; // Prioridad

    int arrival_time; // Tiempo de llegada

    process_state_t state; // estado actual

} pcb_t;

#endif