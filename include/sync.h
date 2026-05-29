#ifndef SYNC_H
#define SYNC_H

#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t condition;
} sync_t;

void sync_init(sync_t * s);
void sync_lock(sync_t * s);
void sync_unlock(sync_t * s);
void sync_wait(sync_t * s);
void sync_signal(sync_t * s);
void sync_broadcast(sync_t * s);
void sync_destroy(sync_t * s);

#endif
