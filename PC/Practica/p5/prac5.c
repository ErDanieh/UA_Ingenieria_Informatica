/**
 * @file prac5.c
 * @author Daniel Asensi Roch  (da33@alu.ua.es)
 * @brief Cuando haya algun lector en la sección critica otro lectores podrán entrar pero no escritores
 *  estos solo podrán entrar cuando no haya ningún lector ni escritor en la sección critica.
 * @version 0.1
 * @date 2022-11-24
 * @compile gcc -o prac5 prac5.c -lpthread
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// Variables globales para el número de lectores y escritores
int LECTORES = 10;
int ESCRITORES = 5;

// Semaforos
sem_t mutex;
sem_t writer;

// nº lectores en la seccion critica
int readers = 0;

// recurso
int recurso = -1;

// Prioridad lector
void bloqueoLector()
{
    sem_wait(&mutex);
    readers++;

    if (readers == 1)
    {
        sem_wait(&writer);
    }
    sem_post(&mutex);
}

void desbloqueoLector()
{
    sem_wait(&mutex);
    readers--;

    if (readers == 0)
    {
        sem_post(&writer);
    }
    sem_post(&mutex);
}

// Funciones lector-escritor

void *lector(void *id)
{

    for (int i = 0; i < LECTORES; i++)
    {
        bloqueoLector();
        printf("El lector %d ha leido un valor de %d\n", *(int *)id, recurso);
        desbloqueoLector();
        sleep(1);
    }
    pthread_exit(id);
}

// Funcion del escritor
void *escritor(void *id)
{

    for (int i = 0; i < ESCRITORES; i++)
    {
        sem_wait(&writer);
        printf("El escritor %d ha actualizado el recurso\n", *(int *)id);
        recurso = *(int *)id; // modificar el recurso
        sem_post(&writer);
        sleep(1);
    }
    pthread_exit(id);
}

void creacionHilos(pthread_t hilos[], int id[], int num, void *(*func)(void *))
{

    for (int i = 0; i < num; i++)
    {
        id[i] = i;
        int error = pthread_create(&hilos[i], NULL, func, &id[i]);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }
}

void finalizarHilos(pthread_t hilos[], int num)
{

    int *salida;

    for (int i = 0; i < num; i++)
    {
        int error = pthread_join(hilos[i], (void **)&salida);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }
}

// Funcion principal
int main()
{
    pthread_t tidlector[LECTORES];
    pthread_t tidescritor[ESCRITORES];
    int idsLectores[LECTORES];
    int idEscritores[ESCRITORES];

    // Inicializacion de semaforos
    sem_init(&mutex, 0, 1);
    sem_init(&writer, 0, 1);

    // Se crean los hilos
    creacionHilos(tidescritor, idEscritores, ESCRITORES, escritor);
    creacionHilos(tidlector, idsLectores, LECTORES, lector);

    // Se espera a que los hilos terminen
    finalizarHilos(tidlector, LECTORES);
    finalizarHilos(tidescritor, ESCRITORES);

    // Cerrar todos los semaforos
    sem_destroy(&mutex);
    sem_destroy(&writer);

    return 0;
}
