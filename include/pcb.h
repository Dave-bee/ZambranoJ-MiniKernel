#ifndef PCB_H

#define PCB_H
#define NEW	 0
#define READY	 1
#define RUNNING	 2
#define TERMINATED 3

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int arrival_time;
    int state;
} pcb_t;

#endif
