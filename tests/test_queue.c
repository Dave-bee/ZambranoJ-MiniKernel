#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"
#include "../include/pcb.h"

int simulacion_activa = 1;

// ejemplo de GeeksForGeeks - Round Robin con different arrival times
// quantum = 2
// P1: burst=5, arrival=0 -> completion=7, waiting=2
// P2: burst=2, arrival=4 -> completion=6, waiting=0
// P3: burst=4, arrival=5 -> completion=11, waiting=2

void test_fifo_order(){
    ready_queue_t q;
    pcb_t p1, p2, p3;
    pcb_t *r;

    queue_init(&q);

    p1.pid = 1;
    p1.burst_time = 5;
    p1.remaining_time = 5;
    p1.arrival_time = 0;
    p1.state = NEW;

    p2.pid = 2;
    p2.burst_time = 2;
    p2.remaining_time = 2;
    p2.arrival_time = 4;
    p2.state = NEW;

    p3.pid = 3;
    p3.burst_time = 4;
    p3.remaining_time = 4;
    p3.arrival_time = 5;
    p3.state = NEW;

    queue_insert(&q, &p1);
    queue_insert(&q, &p2);
    queue_insert(&q, &p3);

    r = queue_remove(&q);

    printf("test_fifo 1: pid=%d ", (*r).pid);
    if ((*r).pid == 1) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    r = queue_remove(&q);

    printf("test_fifo 2: pid=%d ", (*r).pid);
    if ((*r).pid == 2) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    r = queue_remove(&q);

    printf("test_fifo 3: pid=%d ", (*r).pid);
    if ((*r).pid == 3) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    queue_destroy(&q);
}

void test_round_robin(){
    ready_queue_t q;
    pcb_t p1, p2, p3;
    pcb_t *r;

    int quantum = 2;
    int time = 0;

    int completion[4];
    completion[0] = 0;
    completion[1] = 0;
    completion[2] = 0;
    completion[3] = 0;

    queue_init(&q);

    p1.pid = 1;
    p1.burst_time = 5;
    p1.remaining_time = 5;
    p1.arrival_time = 0;
    p1.state = NEW;

    p2.pid = 2;
    p2.burst_time = 2;
    p2.remaining_time = 2;
    p2.arrival_time = 4;
    p2.state = NEW;

    p3.pid = 3;
    p3.burst_time = 4;
    p3.remaining_time = 4;
    p3.arrival_time = 5;
    p3.state = NEW;

    queue_insert(&q, &p1);

    printf("\n--- simulacion Round Robin ---\n");

    while (!queue_empty(&q)) {

	r = queue_remove(&q);

	if ((*r).remaining_time > quantum) {

	    time = time + quantum;

	    (*r).remaining_time = (*r).remaining_time - quantum;

	    (*r).state = READY;

	    if ((*r).pid == 1) {

		if (time >= p2.arrival_time) {

		    if (p2.state == NEW) {
			queue_insert(&q, &p2);
			p2.state = READY;
		    }
		}

		if (time >= p3.arrival_time) {

		    if (p3.state == NEW) {
			queue_insert(&q, &p3);
			p3.state = READY;
		    }
		}
	    }

	    queue_insert(&q, r);

	} else {

	    time = time + (*r).remaining_time;

	    (*r).remaining_time = 0;

	    (*r).state = TERMINATED;

	    completion[(*r).pid] = time;

	    printf("pid:%d terminado en t=%d\n", (*r).pid, time);

	    if (time >= p2.arrival_time) {

		if (p2.state == NEW) {
		    queue_insert(&q, &p2);
		    p2.state = READY;
		}
	    }

	    if (time >= p3.arrival_time) {

		if (p3.state == NEW) {
		    queue_insert(&q, &p3);
		    p3.state = READY;
		}
	    }
	}
    }

    printf("\n--- resultados ---\n");

    printf("pid:1 completion=%d ", completion[1]);

    if (completion[1] == 7) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    printf("pid:2 completion=%d ", completion[2]);

    if (completion[2] == 6) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    printf("pid:3 completion=%d ", completion[3]);

    if (completion[3] == 11) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    int wait1;
    int wait2;
    int wait3;

    wait1 = completion[1]
	- p1.arrival_time - p1.burst_time;

    wait2 = completion[2]
	- p2.arrival_time - p2.burst_time;

    wait3 = completion[3]
	- p3.arrival_time - p3.burst_time;

    printf("\nwaiting times:\n");

    printf("pid:1 waiting=%d ", wait1);

    if (wait1 == 2) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    printf("pid:2 waiting=%d ", wait2);

    if (wait2 == 0) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    printf("pid:3 waiting=%d ", wait3);

    if (wait3 == 2) {
	printf("OK\n");
    } else {
	printf("FAIL\n");
    }

    queue_destroy(&q);
}

int main(){

    printf("\n===== TESTS QUEUE =====\n");

    test_fifo_order();

    test_round_robin();

    printf("=======================\n");

    return 0;
}
