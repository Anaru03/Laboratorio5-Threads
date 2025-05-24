#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "monitor.h"

#define NUM_THREADS 4
#define NUM_ITERATIONS 3
#define INITIAL_RESOURCES 5

int recursos_disponibles = INITIAL_RESOURCES;
pthread_mutex_t monitor_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condicion = PTHREAD_COND_INITIALIZER;
FILE *bitacora;

int decrease_count(int count) {
    pthread_mutex_lock(&monitor_mutex);
    while (recursos_disponibles < count) {
        fprintf(bitacora, "Esperando recursos: solicitados=%d, disponibles=%d\n", count, recursos_disponibles);
        pthread_cond_wait(&condicion, &monitor_mutex);
    }
    recursos_disponibles -= count;
    fprintf(bitacora, "Recursos consumidos: %d. Quedan: %d\n", count, recursos_disponibles);
    pthread_mutex_unlock(&monitor_mutex);
    return 0;
}

int increase_count(int count) {
    pthread_mutex_lock(&monitor_mutex);
    recursos_disponibles += count;
    fprintf(bitacora, "Recursos liberados: %d. Ahora disponibles: %d\n", count, recursos_disponibles);
    pthread_cond_broadcast(&condicion);
    pthread_mutex_unlock(&monitor_mutex);
    return 0;
}

void *thread_func(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int cantidad = rand() % 3 + 1;
        decrease_count(cantidad);
        fprintf(bitacora, "Thread %d usando %d recurso(s)\n", id, cantidad);
        sleep(rand() % 3 + 1);
        increase_count(cantidad);
        fprintf(bitacora, "Thread %d liberó %d recurso(s)\n", id, cantidad);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    srand(time(NULL));

    bitacora = fopen("bitacoraM.txt", "w");
    if (!bitacora) {
        perror("No se pudo abrir la bitácora");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    fclose(bitacora);
    return 0;
}