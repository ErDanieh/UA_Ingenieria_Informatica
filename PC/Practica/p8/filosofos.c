// Daniel Asensi Roch
//  # Compilación : gcc -o filosofos filosofos.c comida.c -lpthread

#include "comida.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

// veces que come un filosofo
#define VECES_COME 5

// puntero al monitor
comidaStruct *c;

void pensar(int id)
{
    printf("El filosofo %d se encuentra pensando\n", id);
    sleep(1);
}

void comer(int id)
{
    printf("El filosofo %d se ha puesto a comer\n", id);
    sleep(1);
    printf("El filosofo %d ha llenado la barriga\n", id);
}

void *filosofoHace(void *id)
{

    int i = *(int *)id;

    for (int h = 0; h < VECES_COME; h++)
    {
        // Se pone a pensar
        pensar(i);
        // Coge los cubiertos para comer
        cogerCubierto(c, i);
        // Se pone a comer
        comer(i);
        // Deja los palillos y vuelve a empezar
        dejarCubierto(c, i);
    }
    // Si ya ha comido sus 5 veces nos salimos del hilo
    pthread_exit(id);
}

int main()
{
    pthread_t hiloFilosofo[CANT_FILOSOFOS];
    int filosofos[CANT_FILOSOFOS];

    int h;
    int error;
    int *salida;

    // inicializar el monitor que controla la comida
    comidaStruct comida = EMPIEZA_LA_COMIDA;
    c = &comida;

    // crear filosofos
    for (h = 0; h < CANT_FILOSOFOS; h++)
    {
        filosofos[h] = h;
        error = pthread_create(&hiloFilosofo[h], NULL, filosofoHace, &filosofos[h]);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // terminar filosofos
    for (h = 0; h < CANT_FILOSOFOS; h++)
    {
        error = pthread_join(hiloFilosofo[h], (void **)&salida);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }

    return 0;
}