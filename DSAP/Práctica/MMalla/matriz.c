#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBLOQTAM 100
#define rmax 4

int main(int argc, char **argv) {

  int myrank, numprocs, bloqtam, r, tamBuffer;
  int fila, columna, error;
  double *a, *b, *c, *buffer;
  double *atmp;

  int *mifila;
  MPI_Status estado;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  if (myrank == 0) {

    // Hacemos el calculo de R
    r = sqrt(numprocs);

    if (r > rmax) {
      printf("La dimension de las matrices no puede ser mayor de 4 \n");
      MPI_Finalize();
      return 0;
    }

    if (r * r != numprocs) {
      printf("El numprocs debe de ser un cuadrado perfecto \n");
      MPI_Finalize();
      return 0;
    }

    // Lectura del tamano del bloque
    printf("Introduce el tamaño del bloque: ");
    while ((bloqtam <= 0) || (bloqtam > MAXBLOQTAM)) {

      scanf("%d", &bloqtam);

      if (bloqtam > MAXBLOQTAM) {
        printf("El valor introducido debe ser menor de %d \n", MAXBLOQTAM);
      }
    }
  }

  // Envio del temano del bloque y de r para todos los procesos
  MPI_Bcast(&r, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&bloqtam, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // Inicializamos los bloques de las matrices
  a = malloc(bloqtam * bloqtam * sizeof(double));
  b = malloc(bloqtam * bloqtam * sizeof(double));
  c = malloc(bloqtam * bloqtam * sizeof(double));
  atmp = malloc(bloqtam * bloqtam * sizeof(double));

  // Inicializamos las variables necesarias para el Algoritmo
  fila = myrank / r;
  columna = myrank % r;
  int arriba, abajo;

  // BLOQUE A
  for (int i = 0; i < bloqtam * bloqtam; i++) {
    a[i] = i * pow((double)(fila * columna + 1), (double) 2) / pow(bloqtam,2);
  }

  // BLOQUE B -> Matriz IDENTIDAD
  for (int i = 0; i < bloqtam; i++) {
    for (int j = 0; j < bloqtam; j++) {
      if (i == j && columna == fila) {
        b[i * bloqtam + j] = 2.0;
      } else {
        b[i * bloqtam + j] = 0.0;
      }
    }
  }

  // BLOQUE C
  for (int i = 0; i < bloqtam * bloqtam; i++) {
    c[i] = 0.0;
  }

  // Estoy en la primera fila
  if (fila == 0) {
    arriba =
        (r - 1) * r + columna; // el proceso arriba estará en la ultima fila
    abajo = (fila + 1) * r + columna;

  } else if (fila == r - 1) { // Estoy en la ultima fila

    arriba = (fila - 1) * r + columna;
    abajo = columna; // el proceso abajo estará en la primera fila (0 + columna)

  } else { // resto de casos
    arriba = (fila - 1) * r + columna;
    abajo = (fila + 1) * r + columna;
  }

  // Calculo de los procesos en la misma fila
  mifila = malloc((r - 1) * sizeof(int));
  int j = 0;
  for (int i = 0; i < numprocs; i++) {
    // Misma fila y distinto proceso
    if (fila == i / r && columna != i % r) {
      mifila[j] = i;
      j++;
    }
  }

  // Creamos los buffer para el envio de los bloques
  MPI_Pack_size(bloqtam * bloqtam, MPI_DOUBLE, MPI_COMM_WORLD, &tamBuffer);
  //Ajusto el tamaño del buffer a la cantidad de procesos mas la cantidad de espacio que necesita bsend
  tamBuffer = numprocs * (tamBuffer + MPI_BSEND_OVERHEAD);
  //Alojo la memoria dinamicamente 
  buffer = malloc(tamBuffer * sizeof(double));
  MPI_Buffer_attach(buffer, tamBuffer);

  // Algoritmo de cannon
  for (int k = 0; k < r; k++) { // k iteraciones

    // Si la columna=mod(fila + k, r)
    if (columna == (fila + k) % r) {
      // Mandar a; a todos los procesadores de mi fila
      for (int i = 0; i < r - 1; i++) {
        MPI_Send(a, bloqtam * bloqtam, MPI_DOUBLE, mifila[i], k,
                 MPI_COMM_WORLD);
      }
      // C = C + A * B
      mult(a, b, c, bloqtam);
    } else {

      // Recibir A del procesador que envia en mi fila
      MPI_Recv(atmp, bloqtam * bloqtam, MPI_DOUBLE, fila * r + ((fila + k) % r),
               k, MPI_COMM_WORLD, &estado);
      // C = C + ATMP * B
      mult(atmp, b, c, bloqtam);
    }

    // Hacer una rotacion de los bloques columna de B, es decir, Pij manda su
    // bloque B a Pi-1,j.El proceso P0ij manda su bloque B a Pr-1,j
    MPI_Bsend(b, bloqtam * bloqtam, MPI_DOUBLE, arriba, 2 * k,
              MPI_COMM_WORLD); 
    MPI_Recv(b, bloqtam * bloqtam, MPI_DOUBLE, abajo, 2 * k, MPI_COMM_WORLD,
             &estado); 
  }

  //Libero el buffer
  MPI_Buffer_detach(&buffer, &tamBuffer); 

  // CALCULO DE ERRORES
  for (int i = 0; i < bloqtam * bloqtam; i++) { 
    if (abs(a[i] - c[i]) > 0.0000001) {
      error++;
    }
  }

  // Imprimimos los errores
  if (error != 0) {
    printf("El error obtenido por el proceso %d es de %d.\n", myrank, error);
  } else {
    printf("OK en el proceso %d. Errores cometidos = %d\n", myrank, error);
  }


  imprimirMatriz(a, bloqtam * bloqtam, "bloque a");
  imprimirMatriz(c, bloqtam * bloqtam, "bloque c");

  free(a);
  free(b);
  free(c);
  free(atmp);
  free(mifila);
  free(buffer);

  MPI_Finalize();
  return 0;
}

void mult(double a[], double b[], double *c, int m) {
  int i, j, k;
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++) {
      for (k = 0; k < m; k++) {
        c[i * m + j] = c[i * m + j] + a[i * m + k] * b[k * m + j];
      }
    }
  }
}


void imprimirMatriz(double a[], int m, char nombre[]) {
  int i;
  printf("%6s = ", nombre);
  for (i = 0; i < m; i++) {
    printf("%7.3f ", a[i]);
    if ((i + 1) % 5 == 0)
      printf("\n         ");
  }
  printf("\n");
}
