#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int numero_primos_par(int n, int rank, int num_procs);
int esPrimo(int p);

int main(int argc, char *argv[])
{
    // valores para el rango de valores para los cuales se contará el número de primos.
    int n, n_factor, n_min, n_max;
    // variables que contienen el número de primos para el rango de valores que se está considerando en la ejecución.
    int primos, primos_parte;
    // variables que se utilizan para medir el tiempo de ejecución del programa.
    double t0, t1, tiempo_secuencial, tiempo_parcial_total;
    // variables que contienen el identificador del proceso y el número total de procesos en la ejecución paralela, respectivamente.
    int rank, num_procs;

    printf("\n");
    printf(" Programa PARALELO para contar el número de primos menores que un valor.\n");
    printf("\n");

    /**
     * inicializa MPI y se obtiene el identificador del proceso y el número total de procesos.
     */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    n_min = 500;
    n_max = 50000000;
    n_factor = 10;

    n = n_min;
    while (n <= n_max)
    {
        // Tiempo de ejecución secuencial
        if (rank == 0)
        {
            t0 = MPI_Wtime();
            primos = 0;
            for (int i = 2; i <= n; i++)
            {
                if (esPrimo(i) == 1)
                    primos++;
            }
            t1 = MPI_Wtime();
            tiempo_secuencial = t1 - t0;
        }

        /**
         * Se utiliza la función "MPI_Barrier" para sincronizar todos los procesos antes de comenzar el tiempo de ejecución paralela.
         */
        MPI_Barrier(MPI_COMM_WORLD);

        // Tiempo de ejecución paralela
        t0 = MPI_Wtime();
        primos_parte = numero_primos_par(n, rank, num_procs);
        double tiempo_parcial = MPI_Wtime() - t0;

        int primos_total;
        MPI_Reduce(&primos_parte, &primos_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0)
        {
            double tiempos_parciales[num_procs];
            tiempos_parciales[0] = tiempo_parcial;
            for (int i = 1; i < num_procs; i++)
            {
                MPI_Recv(&tiempos_parciales[i], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            t1 = MPI_Wtime();
            tiempo_parcial_total = t1 - t0;

            printf(" Primos menores que %10d: %10d.\n Tiempo secuencial: %5.2f segundos.\n", n, primos, tiempo_secuencial);
            printf("Tiempos parciales: ");
            for (int i = 0; i < num_procs; i++)
            {
                printf(" %5.2f,", tiempos_parciales[i]);
            }
            printf("\n Tiempo paralelo total: %5.2f segundos. ", tiempo_parcial_total);
            printf("\nSpeedup: %5.2f. Eficiencia: %5.2f\n", tiempo_secuencial / tiempo_parcial_total, (tiempo_secuencial / tiempo_parcial_total) / num_procs);
            printf("\n-----------------------------------------------\n");
        }
        else
        {
            MPI_Send(&tiempo_parcial, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
        n = n * n_factor;
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}

// Devuelve el numero de primos menores que n
int numero_primos_par(int n, int rank, int num_procs)
{
    int primo, total = 0;
    for (int i = 2 + rank; i <= n; i += num_procs)
    {
        if (esPrimo(i) == 1)
            total++;
    }
    return total;
}

int esPrimo(int p)
{
    for (int i = 2; i <= sqrt(p); i++)
    {
        if (p % i == 0)
            return 0;
    }
    return 1;
}
