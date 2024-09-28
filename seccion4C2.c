#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>  // Para usar syscall y obtener el TID
#include <sys/sysinfo.h>  // Para obtener el número de núcleos

void *simular_carga(void *arg) {
    long id = (long)arg;
    
    // Obtener el PID del hilo
    pid_t pid_hilo = syscall(SYS_gettid);
    
    // Imprimir el ID del hilo y su PID
    printf("Hilo ID: %ld, PID del Hilo: %d\n", id, pid_hilo);

    // Simular carga de trabajo en el procesador
    long long contador = 0;
    while (contador < 1e10) {
        contador++;
    }
    
    return NULL;
}

int main() {
    int num_nucleos = get_nprocs();  // Obtener el número de núcleos del sistema
    pthread_t hilos[num_nucleos];

    printf("Creando %d hilos, uno por cada núcleo del sistema...\n", num_nucleos);

    // Crear los hilos
    for (long i = 0; i < num_nucleos; i++) {
        if (pthread_create(&hilos[i], NULL, simular_carga, (void *)i) != 0) {
            perror("Error al crear el hilo");
            return 1;
        }
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < num_nucleos; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Todos los hilos han terminado.\n");
    return 0;
}
