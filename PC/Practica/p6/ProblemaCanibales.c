/**
 * @file ProblemaCanibales.c
 * @author Daniel Asensi Roch  (dar33@alu.ua.es)
 * @brief
 * @version 0.1
 * @date 2022-11-27
 * @compile gcc -o ProblemaCanibales ProblemaCanibales.c -lpthread
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define M 5
#define C 20
int olla = M;

sem_t mutex;
sem_t espera;
sem_t coci;

void *canibal(void *id)
{
    sem_wait(&mutex);
    // Si no nos quedan misioneros entonces
    if (olla == 0)
    {
        // Despertamos al cocinero
        sem_post(&coci);
        // Los canibales se esperan
        sem_wait(&espera);
    }
    // Nos comemos un misionero
    olla--;
    printf("Canibal %d comiendo, misioneros restantes: %d\n", *(int *)id, olla);
    sem_post(&mutex);
}

void *cocinero()
{

    while (1)
    {
        // Esperamos a que los canibales nos despierten
        sem_wait(&coci);
        olla = M;
        printf("Cocinero cocinando, misioneros restantes: %d\n", olla);
        // Despertamos a los canibales
        sem_post(&espera);
        printf("Canibales a cenar!!\n");
    }
}

// Funcion principal
int main()
{

    pthread_t tidcanibal[C];
    pthread_t thCocinero;
    int id_canibal[C];

    int h;
    int error;
    int *salida;

    // Inicializacion de semaforos
    sem_init(&mutex, 0, 1);
    sem_init(&espera, 0, 0);
    sem_init(&coci, 0, 0);

    // crear canibales
    for (h = 0; h < C; h++)
    {
        id_canibal[h] = h;
        error = pthread_create(&tidcanibal[h], NULL, canibal, &id_canibal[h]);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // Cocinero
    pthread_create(&thCocinero, NULL, cocinero, NULL);

    // terminar canibales
    for (h = 0; h < C; h++)
    {
        error = pthread_join(tidcanibal[h], (void **)&salida);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }

    printf("Todos los miembros de la tribu han cenado\n");

    // Cerrar todos los semaforos
    sem_destroy(&mutex);
    sem_destroy(&espera);
    sem_destroy(&coci);

    return 0;
}