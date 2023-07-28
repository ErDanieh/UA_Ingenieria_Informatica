// Daniel Asensi Roch

#include "comida.h"
#include <stdio.h>


int cubiertoDerecho(int id)
{
    return (id + CANT_FILOSOFOS - 1) % CANT_FILOSOFOS;
}

int cubiertoIzquierdo(int id)
{
    return (id + 1) % CANT_FILOSOFOS;
}

/**
 * @brief Coge los cubiertos
 * 
 * @param c puntero a la estructura
 * @param id del filosofo que coge los cubiertos
 */
void cogerCubierto(comidaStruct *c, int id)
{

    //Bloqueamos el acceso
    pthread_mutex_lock(&c->candadoSC);
    while (c->cubiertos[id] != 2)
    {
        //Esperamos a que los cubiertos esten disponibles
        pthread_cond_wait(&c->puedeComer[id], &c->candadoSC);
    }

    //Cogemos ambos cubiertos
    c->cubiertos[cubiertoIzquierdo(id)] -= 1;
    c->cubiertos[cubiertoDerecho(id)] -= 1;
    printf("El filosofo %d ha cogido los dos cubiertos\n", id);
    //Desbloqueamos 
    pthread_mutex_unlock(&c->candadoSC);
}


/**
 * @brief Deja los cubiertos
 * 
 * @param c puntero a la estructura
 * @param id del filosofo que coge los cubiertos
 */
void dejarCubierto(comidaStruct *c, int id)
{

    //Bloqueamos el acceso a la sección crítica
    pthread_mutex_lock(&c->candadoSC);
    printf("El filosofo %d deja los cubiertos\n", id);

    //Le damos un cubierto más a los filosofos de nuestros lados
    c->cubiertos[cubiertoIzquierdo(id)] += 1;
    c->cubiertos[cubiertoDerecho(id)] += 1;

    // si tienen 2 cubiertos disponibles, ya pueden comer.
    if (c->cubiertos[cubiertoIzquierdo(id)] == 2)
    {
        pthread_cond_signal(&c->puedeComer[cubiertoIzquierdo(id)]);
    }
    if (c->cubiertos[cubiertoDerecho(id)] == 2)
    {
        pthread_cond_signal(&c->puedeComer[cubiertoDerecho(id)]);
    }
    pthread_mutex_unlock(&c->candadoSC);
    // desbloquear acceso a la seccion critica.
}