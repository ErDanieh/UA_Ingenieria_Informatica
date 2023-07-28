// Daniel Asensi Roch
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rangoProcesos, totalProcesos, numero = 0;
    
    // argc: puntero al número de argumentos en la línea de comando.
    // argv: puntero a una matriz de argumentos en la línea de comando.
    /**
     * debe ser llamada antes de cualquier otra función MPI en un proceso MPI
     * . La función inicializa el entorno MPI, establece la identidad del proceso
     * MPI y prepara el proceso para comunicarse con otros procesos MPI.
     */
    MPI_Init(&argc, &argv);
    // MPI_COMM_WORLD = incluye a todos los procesos MPI iniciados en la aplicación MPI.
    MPI_Comm_size(MPI_COMM_WORLD, &totalProcesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rangoProcesos);

    MPI_Status status;

    if (totalProcesos < 2)
    {
        printf("La cantidad de procesos no es suficiente");
        MPI_Finalize();
    }

    if (rangoProcesos == 0)
    {
        printf("Introduce numero a transferir:\n");
        scanf("%d", &numero);


        printf("Se ha introducido %d en root \n", numero);
        numero++;
        // Argumentos:
        /**
         * 1-> buffer de los datos a enviar
         * 2-> numero de elementos
         * 3-> Tipo de elementos (MPI_INT)
         * 4-> Proceso destino
         * 5-> Etiqueta para el mensaje
         * 6-> Grupo de comunicacion (MPI_COMM_WORLD)
         */
        MPI_Send(&numero, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

        // Recibimos el mensaje del ultimo proceso para cerrar el anillo
        //  Argumentos:
        /**
         * 1-> buffer de los datos recibidos
         * 2-> numero de elementos
         * 3-> Tipo de elementos (MPI_INT)
         * 4-> Proceso del que nos llega el mensaje
         * 5-> Etiqueta para el mensaje
         * 6-> Grupo de comunicacion (MPI_COMM_WORLD)
         * 7-> puntero a status
         */
        MPI_Recv(&numero, 1, MPI_INT, totalProcesos - 1, 1, MPI_COMM_WORLD, &status);
        printf("Soy el proceso root El entero que he recibido es: %d\n", numero);
    }
    else
    {
        MPI_Recv(&numero, 1, MPI_INT, rangoProcesos - 1, 1, MPI_COMM_WORLD, &status);
        printf("Soy el proceso %d he recibido %d \n", rangoProcesos, numero);
        numero++;
        if (rangoProcesos != (totalProcesos - 1))
        {
            MPI_Send(&numero, 1, MPI_INT, rangoProcesos + 1, 1, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Send(&numero, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}