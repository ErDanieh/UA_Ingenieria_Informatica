#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int numero_primos_par(int n, int rank, int num_procs);
int esPrimo(int p);

int main(int argc, char *argv[])
{
    int n, n_factor, n_min, n_max;
    int primos, primos_parte;
    double t0, t1, tiempo_secuencial;
    int rank, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    n_min = 500;
    n_max = 5000000;
    n_factor = 10;
    printf("\n");
    printf(" Programa PARALELO para contar el número de primos menores que un valor.\n");
    printf("\n");
    n = n_min;
    while (n <= n_max)
    {
        // Tiempo de ejecución secuencial
        if (rank == 0) {
            t0 = MPI_Wtime();
            primos = 0;
            for (int i = 2; i <= n; i++) {
                if (esPrimo(i) == 1)
                    primos++;
            }
            t1 = MPI_Wtime();
            tiempo_secuencial = t1 - t0;
        }

        MPI_Barrier(MPI_COMM_WORLD);

        // Tiempo de ejecución paralela
        t0 = MPI_Wtime();
        primos_parte = numero_primos_par(n, rank, num_procs);
        MPI_Reduce(&primos_parte, &primos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        t1 = MPI_Wtime();

        if (rank == 0)
        {
            printf(" Primos menores que %10d: %10d.\n Tiempo secuencial: %5.2f segundos.\n Tiempo paralelo: %5.2f segundos. ", n, primos, tiempo_secuencial, t1 - t0);
            printf("\nSpeedup: %5.2f. Eficiencia: %5.2f\n", tiempo_secuencial / (t1 - t0), (tiempo_secuencial / (t1 - t0)) / num_procs);
            printf("\n-----------------------------------------------\n");
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
