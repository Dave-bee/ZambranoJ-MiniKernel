#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "metrics.h"
#include "pcb.h"
#include "sync.h"

#define QUANTUM 2

extern ready_queue_t ready_queue;
extern metrics_t metrics;
extern int simulacion_activa;
extern sync_t print_lock;

void *cpu_run(void *arg){
    int cpu_id;
    pcb_t *p;

    cpu_id = *(int *) arg;

    sync_lock(&print_lock);
    printf("[CPU %d] prendido \n", cpu_id);
    sync_unlock(&print_lock);

    while (simulacion_activa) {
	p = queue_remove(&ready_queue);

	if (p == NULL) {
	    break;
	}

	if ((*p).state == TERMINATED) {
	    continue;
	}

	sync_lock(&print_lock);
	printf("[CPU %d] ejecutando pid:%d burst:%d remaining:%d\n",
	       cpu_id, (*p).pid, (*p).burst_time, (*p).remaining_time);
	sync_unlock(&print_lock);

	if ((*p).remaining_time > QUANTUM) {
	    sleep(QUANTUM);
	    (*p).remaining_time = (*p).remaining_time - QUANTUM;
	    (*p).state = READY;
	    sync_lock(&print_lock);
	    printf("[CPU %d] context switch pid:%d remaining:%d\n",
		   cpu_id, (*p).pid, (*p).remaining_time);
	    sync_unlock(&print_lock);
	    queue_insert(&ready_queue, p);
	} else {
	    sleep((*p).remaining_time);
	    (*p).remaining_time = 0;
	    (*p).state = TERMINATED;
	    sync_lock(&print_lock);
	    printf("[CPU %d] pid:%d DONE\n", cpu_id, (*p).pid);
	    sync_unlock(&print_lock);
	    metrics_record(&metrics, p,
			   (*p).arrival_time + (*p).burst_time);
	    free(p);
	}
    }

    sync_lock(&print_lock);
    printf("[CPU %d] apagado\n", cpu_id);
    sync_unlock(&print_lock);

    return NULL;
}
