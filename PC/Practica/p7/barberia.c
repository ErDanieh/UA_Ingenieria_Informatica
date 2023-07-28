// Daniel Asensi Roch
/**
 * @brief Problema de la barberia con 3 barberos y 25 clientes.
 *
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

// Constantes para barberos y clientes
const int NUM_BARBEROS = 3;
const int NUM_CLIENTES = 20;

// Semaforos definidos en el enunciado
sem_t max_capacidad;       // Inicializado a  20
sem_t sofa;                // Inicializado a  4
sem_t silla_barbero;       // Inicializado a 3
sem_t cliente_listo;       // cliente ya esta sentado en la silla.
sem_t terminado;           // corte de pelo ha terminado. Inicializado a 0.
sem_t dejar_silla_barbero; // Inicializado a 0.
sem_t pago;                // controla el pago de los clientes. Inicializado a 0.
sem_t recibo;              // entrega al cliente de un recibo de pago. Inicializado a 0.
sem_t coord;               // controla la ocupación de los barberos, Inicializado a 3.

void *barbero(void *id)
{
    while (1)
    {
        // Esperamos a que haya un cliente en la silla
        sem_wait(&cliente_listo);
        // Ocupamos el barbero
        sem_wait(&coord);
        // Cortamos el pelo
        printf("Barbero %d cortando pelo\n", *(int *)id);
        sleep(2);
        // liberar ocupacion.
        sem_post(&coord);
        // corte de pelo finalizado
        sem_post(&terminado);
        // el cliente deja la silla
        sem_wait(&dejar_silla_barbero);
        // silla del barbero libre
        sem_post(&silla_barbero);
    }
    pthread_exit(id);
}

void *cajero(void *id)
{

    while (1)
    {
        // Esperar algun pago
        sem_wait(&pago);
        // cajero ocupado
        sem_wait(&coord);
        // cobrar
        printf("Cobrando ... \n");
        sleep(2);
        // cajero ocupado
        sem_post(&coord);
        // pago aceptado, entrega de recibo
        sem_post(&recibo);
    }
    pthread_exit(id);
}

void *cliente(void *id)
{

    int i = *(int *)id;

    // Si esta la barberia llena se espera max 20 clientes
    sem_wait(&max_capacidad);
    // Entrar a barberia
    printf("Cliente %d entra\n", i);
    sleep(1);
    // Si el sofa tiene hueco libre se sienta y espera
    sem_wait(&sofa);
    printf("Cliente %d se sienta en el sofa\n", i);
    sleep(1);
    // Esperamos a que tengamos un sitio con el barbero
    sem_wait(&silla_barbero);
    // Cuando tengamos sitio nos levantamos del sofa y dejamos el hueco
    printf("Cliente %d se levanta del sofa\n", i);
    sleep(1);
    // Lanzamos la senal de que estamos de pie
    sem_post(&sofa);
    // Nos sentamos en la silla del barbero
    printf("Cliente %d se sienta en la silla del barbero\n", i);
    sleep(1);
    sem_post(&cliente_listo); // cliente listo, se encuentra en la silla.
    // Esperamos a que nos terminen de cortar el pelo
    sem_wait(&terminado);
    // levantarse silla barbero
    printf("Cliente %d se levanta de la silla del barbero\n", i);
    sleep(1);
    // Nos levantamos la silla del barbero
    sem_post(&dejar_silla_barbero);
    // El clienta lanza la senal de pagar
    printf("Cliente %d realiza el pago\n", i);
    sleep(1);
    sem_post(&pago);
    // Esperamos a recibir el ricibo del barbero
    sem_wait(&recibo); // esperando recibo.
    printf("Cliente %d sale de la barbería\n", i);
    sleep(1);
    // Lanzamos la senal de que salimos de la tienda y del hilo
    sem_post(&max_capacidad);
    pthread_exit(id);
}

int main()
{
    pthread_t thCliente[NUM_CLIENTES];
    pthread_t thBarbero[NUM_BARBEROS];
    pthread_t thCajero;

    int id_cliente[NUM_CLIENTES];
    int id_barbero[NUM_BARBEROS];

    int h;
    int error;
    int *salida;


    // INICIALIZACIÓN DE SEMÁFOROS, primer valor a 0, inidica que son hilos,
    // el segundo valor indica el número al que se inicializan los semáforos.

    // se inicializa a 20, ya que esta será la capacidad máxima, los primeros 20
    // sem_waits que se produzcan podrán entrar, pero al llegar al 20, el valor del semáforo
    // sera 0 y habrá que esperar un post, de esta manera, siempre habrá 20 clientes como
    // máximo
    sem_init(&max_capacidad, 0, 20);
    sem_init(&sofa, 0, 4);
    sem_init(&silla_barbero, 0, 3);
    sem_init(&cliente_listo, 0, 0);
    sem_init(&terminado, 0, 0);
    sem_init(&dejar_silla_barbero, 0, 0);
    sem_init(&pago, 0, 0);
    sem_init(&recibo, 0, 0);
    sem_init(&coord, 0, 3);

    // crear barberos
    for (h = 0; h < NUM_BARBEROS; h++)
    {
        id_barbero[h] = h;
        error = pthread_create(&thBarbero[h], NULL, barbero, &id_barbero[h]);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // crear clientes
    for (h = 0; h < NUM_CLIENTES; h++)
    {
        id_cliente[h] = h;
        error = pthread_create(&thCliente[h], NULL, cliente, &id_cliente[h]);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // Cajero
    pthread_create(&thCajero, NULL, cajero, &h);

    // terminar clientes
    for (h = 0; h < NUM_CLIENTES; h++)
    {
        error = pthread_join(thCliente[h], (void **)&salida);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }
}
