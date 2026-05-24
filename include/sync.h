#ifndef SYNC_H
#define SYNC_H

#define QUANTUM 2

void* process_generator(void* arg);

void* cpu_worker(void* arg);

#endif