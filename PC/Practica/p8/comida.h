// Daniel Asensi Roch
#ifndef _COMIDA_H_
#define _COMIDA_H_
#include <sys/types.h>
#include <pthread.h>

#define CANT_FILOSOFOS 5

//Estructura del monitor que controla la comida de filosofos
typedef struct comida
{
    // nº de cubiertos disponibles de cada filosofo, de 0 a 2.
    int cubiertos[CANT_FILOSOFOS];
    // semaforo para acceder a la sección crítica
    pthread_mutex_t candadoSC;
    // variable de condicion por cada filosofo
    pthread_cond_t puedeComer[CANT_FILOSOFOS];
} comidaStruct;

// Inicialmente los filosofos pueden comer y los cubiertoss estan disponibles = 2
#define EMPIEZA_LA_COMIDA                                          \
    {                                                              \
        {[0 ...(CANT_FILOSOFOS - 1)] = 2},                         \
            PTHREAD_MUTEX_INITIALIZER,                             \
        {                                                          \
            [0 ...(CANT_FILOSOFOS - 1)] = PTHREAD_COND_INITIALIZER \
        }                                                          \
    }

//El filosofo del id devuelve el cubierto derecho
int cubiertoDerecho(int id);
//El filosofo del id devuelve el cubierto izquierdo
int cubiertoIzquierdo(int id);
//El filosofo del id coge los cubierto
void cogerCubierto(comidaStruct *c, int id);
//El filosofo del id deja los cubiertos
void dejarCubierto(comidaStruct *c, int id);

#endif