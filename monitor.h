#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>

#define MAX_RECURSOS 10

extern int recursos_disponibles;
extern pthread_mutex_t monitor_mutex;
extern pthread_cond_t condicion;

int decrease_count(int count);
int increase_count(int count);

#endif