#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mpi.h>

typedef struct
{
    int row;
    int col;
    int max_gray;
    int **matrix;
} PGMData;

int **CrearArray2D_int(int, int);
void LiberarArray2D_int(int, double **);
void readPGM(char *, PGMData *);
void writePGM(char *, PGMData *);
void init_pgm(int, int, int, int **, PGMData *);

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int num_procs, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char archivo_imagen_ori[100] = "logo.pgm";
    char archivo_imagen_aristas[100] = "logo_edge.pgm";

    PGMData img_data, img_edge;

    if (argc == 2)
    {
        strcpy(archivo_imagen_ori, argv[1]);
        strcat(archivo_imagen_ori, ".pgm");
        strcpy(archivo_imagen_aristas, argv[1]);
        strcat(archivo_imagen_aristas,
               "_edge.pgm");
    }
    if (rank == 0)
    {
        printf("\n  *************** DATOS DE LA EJECUCION ***************************\n");
        printf("  * Archivo imagen original   : %25s         *\n", archivo_imagen_ori);
        printf("  * Archivo imagen con aristas: %25s         *\n", archivo_imagen_aristas);
        printf("  *****************************************************************\n\n");
        printf("  Leyendo imagen \"%s\" ... \n", archivo_imagen_ori);

        readPGM(archivo_imagen_ori, &img_data);
        printf("  Dimension de la imagen: %d x %d\n", img_data.row, img_data.col);
    }

    int row, col;
    if (rank == 0)
    {
        row = img_data.row;
        col = img_data.col;
    }
    // Le decimos a todos los procesos la cantidad de filas y columnas
    MPI_Bcast(&row, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&col, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // La cantidad de filas que van a tener que enviar cada uno
    int rowlocal = row / num_procs;
    int extraProceso0 = row % num_procs;
    

    int **matrix, **matrix_edge;
    if (rank == 0)
        matrix_edge = CrearArray2D_int(row, col);

    if (rank == 0)
    {
        int start_row, end_row;

        for (int i = 1; i < num_procs; i++)
        {
            start_row = i * rowlocal - 1 + extraProceso0;
            end_row = (i + 1) * rowlocal + (i == num_procs - 1 ? 0 : 1) + extraProceso0;

            printf("Rank 0 enviando a %d filas %d a %d \n", i, start_row, end_row);

            int rows_to_send = end_row - start_row;

            for (int j = 0; j < rows_to_send; j++)
            {
                // printf("Rank 0 enviando fila %d \n", start_row + j);
                MPI_Send(&(img_data.matrix[start_row + j][0]), col, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
            // printf("Rank 0 enviando a Rank %d %d filas \n", i, rows_to_send);
            // MPI_Send(&(img_data.matrix[start_row][0]), rows_to_send * col, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

        printf("Rank %d ejecutando Filtro_Laplace \n", rank);

        // El rango 0 ejecuta el filtro en las filas que le corresponden + 1
        Filtro_Laplace(img_data.matrix, matrix_edge, rowlocal + 1 + extraProceso0, col); // +1 para incluir el solapamiento
        printf("Rank %d recibiendo resultados \n", rank);

        for (int i = 1; i < num_procs; i++)
        {
            //printf("ROWLOCAL %d \n", rowlocal);
            int recv_rows = rowlocal + (i == num_procs - 1 ? 0 : 1);

            //int recv_size = recv_rows * col;

            //printf("Recibo del Rank %d esta cantidad de filas %d pixeles \n", i, recv_size);

            // HACER QUE LA RECEPCION DE LAS FILAS SEA EN ORDEN
            for (int j = 0; j < recv_rows; j++)
            {
                MPI_Recv(&(matrix_edge[(i * rowlocal) + j + extraProceso0][0]), col, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            // MPI_Recv(&(matrix_edge[i * rowlocal][0]), recv_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Se han pintado las filas %d a %d \n", i * rowlocal, (i + 1) * rowlocal);
        }

        init_pgm(row, col, img_data.max_gray, matrix_edge, &img_edge);
        writePGM(archivo_imagen_aristas, &img_edge);
    }
    else
    {

        // Me dicen cuantas filas voy a recibir
        int rows_to_receive = rowlocal + (rank == num_procs - 1 ? 1 : 2);

        printf("Rank %d recibiendo %d filas \n", rank, rows_to_receive);

        // Creo los arrays para almacenarlas y las recibo
        matrix = CrearArray2D_int(rows_to_receive, col);
        matrix_edge = CrearArray2D_int(rows_to_receive, col);

        for (int i = 0; i < rows_to_receive; i++)
        {
            // printf("Rank %d recibiendo fila %d \n", rank, i);
            MPI_Recv(&(matrix[i][0]), col, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("Rank %d ejecutando Filtro_Laplace con %d filas\n", rank, rows_to_receive);
        Filtro_Laplace(matrix, matrix_edge, rows_to_receive, col);

        printf("Rank %d enviando resultado \n", rank);
        int rows_to_send = rowlocal + (rank == num_procs - 1 ? 0 : 1);

        printf("Rank %d enviando a Rank 0 %d filas \n", rank, rows_to_send);

        printf("Rank %d enviando a Rank 0 %d pixeles \n", rank, rows_to_send * col);

        for (int i = 1; i < rows_to_send + 1; i++)
        {
            //printf("Rank %d enviando fila %d \n", rank, i);
            MPI_Send(&(matrix_edge[i][0]), col, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        // MPI_Send(&(matrix_edge[1][0]), rows_to_send * col, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

void init_pgm(int row, int col, int max_gray, int **matrix, PGMData *pgm)
{
    pgm->row = row;
    pgm->col = col;
    pgm->max_gray = max_gray;
    pgm->matrix = matrix;
}