#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 5
#define NUM_ITERATIONS 4
#define INITIAL_RESOURCES 3

sem_t semaforo;
int recursos_disponibles = INITIAL_RESOURCES;
FILE *bitacora;
pthread_mutex_t bitacora_mutex;

void *usar_recurso(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sem_wait(&semaforo);  // Solicita un recurso

        pthread_mutex_lock(&bitacora_mutex);
        recursos_disponibles--;
        fprintf(bitacora, "Thread %d: Consumió recurso. Iteración %d. Recursos disponibles: %d\n", id, i + 1, recursos_disponibles);
        pthread_mutex_unlock(&bitacora_mutex);

        sleep(rand() % 3 + 1); // Simula uso del recurso

        pthread_mutex_lock(&bitacora_mutex);
        recursos_disponibles++;
        fprintf(bitacora, "Thread %d: Liberó recurso. Iteración %d. Recursos disponibles: %d\n", id, i + 1, recursos_disponibles);
        pthread_mutex_unlock(&bitacora_mutex);

        sem_post(&semaforo);  // Libera el recurso
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    srand(time(NULL));

    bitacora = fopen("bitacoraS.txt", "w");
    if (!bitacora) {
        perror("No se pudo abrir la bitácora");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&bitacora_mutex, NULL);
    sem_init(&semaforo, 0, INITIAL_RESOURCES);

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, usar_recurso, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaforo);
    pthread_mutex_destroy(&bitacora_mutex);
    fclose(bitacora);

    return 0;
}