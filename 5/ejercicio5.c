#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Definir el número de términos y el número de threads (procesadores) a utilizar
#define NUM_TERMINOS 1000000
#define NUM_THREADS 3

double resultado_parcial[NUM_THREADS];

void* calcular_pi(void* arg) {
    int id = *(int*)arg;
    double sum = 0.0;
    
    for (int i = id; i < NUM_TERMINOS; i += NUM_THREADS) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        sum += term;
    }
    
    resultado_parcial[id] = sum;
    pthread_exit(0);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, calcular_pi, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double pi = 0.0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pi += resultado_parcial[i];
    }

    pi *= 4.0;
    
    printf("El valor aproximado de pi es: %.15f\n", pi);
    
    return 0;
}
