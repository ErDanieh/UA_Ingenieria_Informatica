/* PROCESOS */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Cambiamos la cantidad de procesos
#define NUM_PROCESOS 2


//Cambiamos lo que debe de imprimir cada uno de los hijos ejercicio 3
void codigo_del_proceso(int id)
{
    printf("Proceso(id=%d): %d \n", id,id);
}


int main()
{
    int p;
    int id[NUM_PROCESOS] = {1, 2};
    int pid;
    int salida;

    for (p = 0; p < NUM_PROCESOS; p++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("Error al crear un proceso: ");
            exit(-1);
        }
        else if (pid == 0){ // Codigo del hijo
            //ejercicio 3
            codigo_del_proceso(id[p]);
            //Nos salimos del proceso
            exit(id[p]);
        }
    }

    // Codigo del padre este no cambia
    for (p = 0; p < NUM_PROCESOS; p++)
    {
        pid = wait(&salida);
        printf("Proceso(pid=%d) con id = %x terminado y status = %d \n", pid,
               salida >> 8, WEXITSTATUS(salida));
    }
    return 0;
}