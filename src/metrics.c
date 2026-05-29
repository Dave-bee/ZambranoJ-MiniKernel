#include <stdio.h>
#include "metrics.h"
#include "pcb.h"

void metrics_init(metrics_t *m){
    (*m).total = 0;
    (*m).throughput = 0.0;
    (*m).avg_response_time = 0.0;
}

void metrics_record(metrics_t *m, pcb_t *p, int t_end){
    pthread_mutex_lock(&(*m).lock);
    int i;
    i = (*m).total;

    (*m).records[i].pid = (*p).pid;
    (*m).records[i].arrival_time = (*p).arrival_time;
    (*m).records[i].completion_time = t_end;
    (*m).records[i].burst_time = (*p).burst_time;
    (*m).records[i].response_time = t_end - (*p).arrival_time;

    (*m).total++;
    printf("Proceso %d registrado, response_time: %d\n", (*p).pid,
	   (*m).records[i].response_time);
    pthread_mutex_unlock(&(*m).lock);
}

void metrics_calculate(metrics_t *m, int t_total){
    int i;
    double response_time = 0.0;

    for (i = 0; i < (*m).total; i++) {
	response_time = response_time + (*m).records[i].response_time;
    }

    if ((*m).total > 0) {
	(*m).avg_response_time = response_time / (*m).total;
    }

    if (t_total > 0) {
	(*m).throughput = (double) (*m).total / t_total;
    }
}

void metrics_print(metrics_t *m){
    int i;

    printf("\n===== METRICAS DEL SCHEDULER =====\n");
    printf("total procesos: %d\n", (*m).total);
    printf("throughput: %.2f procesos/unidad tiempo\n", (*m).throughput);
    printf("avg response time: %.2f\n", (*m).avg_response_time);

    printf("\n--- detalle por proceso ---\n");
    for (i = 0; i < (*m).total; i++) {
	printf("pid: %d | response_time: %d | completion: %d\n",
	       (*m).records[i].pid,
	       (*m).records[i].response_time,
	       (*m).records[i].completion_time);
    }
    printf("===================================\n");
}
