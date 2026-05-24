# MiniKernel

MiniKernel es un mini sistema operativo desarrollado en C y POSIX Threads que simula procesos concurrentes y planificación de CPU mediante el algoritmo Round Robin.

El proyecto fue desarrollado como proyecto para sistemas operativos para asi comprender cómo funcionan internamente los schedulers, la sincronización entre CPUs y la administración de procesos en sistemas operativos.

---

# Características

- Simulación de procesos mediante PCB (Process Control Block)
- Planificación CPU usando Round Robin
- CPUs simuladas mediante hilos POSIX
- Cola de procesos compartida (Ready Queue)
- Sincronización con mutex y variables condicionales
- Detección y prevención de race conditions
- Métricas de rendimiento:
  - Response Time
  - Turnaround Time
  - Throughput
- Protección contra overflow en la cola

---

# Arquitectura del sistema

El sistema está compuesto por tres componentes principales:

## 1. Process Generator

Hilo encargado de:

- crear procesos aleatorios,
- asignar burst time,
- asignar prioridades,
- insertar procesos en la ready queue.

---

## 2. Ready Queue

Cola compartida entre los hilos CPU y el generador de procesos.

La cola utiliza:

- pthread_mutex_t
- pthread_cond_t

para evitar condiciones de carrera y sincronizar acceso concurrente.

---

## 3. CPU Threads

Cada CPU es simulada mediante un hilo POSIX.

Las CPUs:

- toman procesos de la cola,
- ejecutan un quantum,
- actualizan el remaining time,
- reinsertan procesos si no terminan,
- terminan procesos completados.

---

# Estructura del proyecto

```text
MiniKernel/
├── include/
│   ├── pcb.h
│   ├── queue.h
│   ├── metrics.h
│   └── sync.h
├── src/
│   ├── main.c
│   ├── queue.c
│   ├── cpu.c
│   └── metrics.c
├── tests/
├── Makefile
└── README.md
```

---

# PCB utilizado

```c
typedef struct {

    int pid;

    int burst_time;

    int remaining_time;

    int priority;

    int arrival_time;

    process_state_t state;

    time_t first_run_time;

    time_t completion_time;

    int has_started;

} pcb_t;
```

---

# Algoritmo de planificación

MiniKernel utiliza:

## Round Robin (RR)

Características:

- quantum fijo,
- fairness entre procesos,
- requeue automático,
- context switching simulado.

---

# Métricas implementadas

## Response Time

Tiempo desde la llegada del proceso hasta su primera ejecución.

---

## Turnaround Time

Tiempo total desde creación hasta finalización.

---

## Throughput

Cantidad de procesos completados por segundo.

---

# Compilación

```bash
make
```

---

# Ejecución

```bash
./minikernel
```

---

# Ejemplo de salida

```text
[GENERATOR] PID=1 BURST=5 PRIORITY=2

[CPU] Running PID=1 Remaining=5

[CPU] Process 1 finished

[METRICS] PID=1 Turnaround=4 sec

[METRICS] Throughput = 0.50 processes/sec
```

---

# Tecnologías utilizadas

- Lenguaje C
- POSIX Threads (pthreads)
- Mutex
- Condition Variables
- Linux / WSL
- GCC

---

# Objetivos académicos

Este proyecto busca comprender:

- planificación CPU,
- administración de procesos,
- concurrencia,
- sincronización,
- race conditions,
- métricas de scheduling,
- funcionamiento interno de sistemas operativos.

---

# Autor

Mateo Alban Monteros