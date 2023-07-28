/* PROCESOS */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Cambiamos el numero de procesos
#define NUM_PROCESOS 3
#define VECES_IMPRIME 5

// Cambiamos el valor pasado por parametro
void codigo_del_proceso(char c)
{
    for (int i = 0; i < VECES_IMPRIME; i++)
    {
        printf("%c", c);
    }
    printf("\n");
}

int main()
{
    int p;
    //Cambiamos lo que deben de imprimir los procesos
    int id[NUM_PROCESOS] = {'A', 'B', 'C'};
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
        else if (pid == 0)
        { // Codigo del hijo
            codigo_del_proceso(id[p]);
            exit(id[p]);
        }
    }

    // Codigo del padre
    for (p = 0; p < NUM_PROCESOS; p++)
    {
        pid = wait(&salida);
        printf("Proceso(pid=%d) con id = %x terminado y status = %d \n", pid,
               salida >> 8, WEXITSTATUS(salida));
    }
    return 0;
}