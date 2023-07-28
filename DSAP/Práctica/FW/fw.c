#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXN = 1000;
const int MAXNUMPROCS = 8;

float **Crear_matriz_pesos_consecutivo(int Filas, int Columnas);
int **Crear_matriz_caminos_consecutivo(int Filas, int Columnas);
void Definir_Grafo(int n, float **dist, int **caminos);
void printMatrizCaminos(int **a, int fila, int col);
void printMatrizPesos(float **a, int fila, int col);
void calcula_camino(float **a, int **b, int n);

int main(int argc, char **argv)
{
  int myrank = 0, numprocs = 0, numeroVertices = 0, filasProceso = 0, rest = 0,
      **caminos;
  float **distancia;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  // Comprombamos que el numero de procesos es correcto
  if (numprocs > MAXNUMPROCS)
  {
    if (myrank == 0)
      printf("Superado el numero maximo de procesos.\n");

    MPI_Finalize();
    exit(1);
  }

  // Comprobamos que el numero de procesos es correcto
  if (numprocs < 2)
  {
    printf("Tiene que haber minimo 2 procesadores en uso.\n");
    MPI_Finalize();
    exit(1);
  }

  // Introducimos el numero de vertices
  if (myrank == 0)
  {
    printf("Numero de vertices: \n");
    if (!scanf("%d", &numeroVertices))
    {
      printf("Debes introducir un numero.\n");
      MPI_Finalize();
      exit(1);
    }
  }

  MPI_Bcast(&numeroVertices, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if (numeroVertices > MAXN)
  {
    if (myrank == 0)
      printf("numero maximo de vertices superado.\n");

    MPI_Finalize();
    exit(1);
  }
  else if (numeroVertices <= 0)
  {
    if (myrank == 0)
      printf("Cantidad incorrecta de vertices.\n");

    MPI_Finalize();
    exit(1);
  }

  // Empieza el algoritmo
  filasProceso = numeroVertices / numprocs;
  distancia = Crear_matriz_pesos_consecutivo(numeroVertices, numeroVertices);
  caminos = Crear_matriz_caminos_consecutivo(numeroVertices, numeroVertices);

  if (myrank == 0)
  {
    Definir_Grafo(numeroVertices, distancia, caminos);
    rest = numeroVertices % numprocs;
  }

  // Barrera para sincronizacion!!!
  MPI_Barrier(MPI_COMM_WORLD);

  if (myrank != 0)
  {
    // Distribución de datos a procesos: Utiliza MPI_Scatter para distribuir las filas de las matrices dist y paths entre los diferentes procesos.
    MPI_Scatter(&distancia[0][0], filasProceso * numeroVertices, MPI_FLOAT,
                &distancia[0][0], filasProceso * numeroVertices, MPI_FLOAT, 0,
                MPI_COMM_WORLD);
    MPI_Scatter(&caminos[0][0], filasProceso * numeroVertices, MPI_INT,
                &caminos[0][0], filasProceso * numeroVertices, MPI_INT, 0,
                MPI_COMM_WORLD);
  }
  else
  {
    MPI_Scatter(&distancia[rest][0], filasProceso * numeroVertices, MPI_FLOAT,
                MPI_IN_PLACE, filasProceso * numeroVertices, MPI_FLOAT, 0,
                MPI_COMM_WORLD);
    MPI_Scatter(&caminos[rest][0], filasProceso * numeroVertices, MPI_INT,
                MPI_IN_PLACE, filasProceso * numeroVertices, MPI_INT, 0,
                MPI_COMM_WORLD);
  }

  // Almacenar distancias entre nodos
  float *d = (float *)malloc(numeroVertices * sizeof(float));
  // Almacenar caminos entre nodos
  int *c = (int *)malloc(numeroVertices * sizeof(int));

  // Encargado de enviar la informacion
  int sender = 0;
  // Fila que me encuentro procesando
  int filaProcesandoAhora = 0;

  /*Cálculo de los caminos más cortos: Implementa el algoritmo de Floyd-Warshall en paralelo. Para cada vértice k, cada
   proceso calcula el camino más corto entre todos los pares de vértices en su subconjunto de filas.*/
  for (int k = 0; k < numeroVertices; k++)
  {
    sender = (k < filasProceso + numeroVertices % numprocs)
                 ? 0
                 : numprocs - 1 - ((numeroVertices - k - 1) / filasProceso);
    filaProcesandoAhora =
        (sender == 0) ? k
                      : k - (filasProceso * sender) - numeroVertices % numprocs;

    if (myrank == sender)
    {
      memcpy(&d[0], &distancia[filaProcesandoAhora][0],
             numeroVertices * sizeof(float));
      memcpy(&c[0], &caminos[filaProcesandoAhora][0],
             numeroVertices * sizeof(int));
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&d[0], numeroVertices, MPI_FLOAT, sender, MPI_COMM_WORLD);
    MPI_Bcast(&c[0], numeroVertices, MPI_INT, sender, MPI_COMM_WORLD);

    for (int i = 0; i < filasProceso + rest; i++)
      for (int j = 0; j < numeroVertices; j++)
        if (distancia[i][k] * d[j] != 0)
          if ((distancia[i][k] + d[j] < distancia[i][j]) ||
              (distancia[i][j] == 0))
          {
            distancia[i][j] = distancia[i][k] + d[j];
            caminos[i][j] = c[j];
          }
  }

  free(d);
  free(c);

  if (myrank != 0)
  {
    // Recolección de datos: Utiliza MPI_Gather para recolectar las filas de las matrices dist y paths desde los diferentes procesos.
    MPI_Gather(&distancia[0][0], filasProceso * numeroVertices, MPI_FLOAT,
               &distancia[0][0], filasProceso * numeroVertices, MPI_FLOAT, 0,
               MPI_COMM_WORLD);
    MPI_Gather(&caminos[rest][0], filasProceso * numeroVertices, MPI_INT,
               &caminos[rest][0], filasProceso * numeroVertices, MPI_INT, 0,
               MPI_COMM_WORLD);
  }
  else
  {
    // Recolección de datos: Utiliza MPI_Gather para recolectar las filas de las matrices dist y paths desde los diferentes procesos.
    MPI_Gather(MPI_IN_PLACE, filasProceso * numeroVertices, MPI_FLOAT,
               &distancia[rest][0], filasProceso * numeroVertices, MPI_FLOAT, 0,
               MPI_COMM_WORLD);
    MPI_Gather(MPI_IN_PLACE, filasProceso * numeroVertices, MPI_INT,
               &caminos[rest][0], filasProceso * numeroVertices, MPI_INT, 0,
               MPI_COMM_WORLD);
  }

  //Imprimir resultados
  if (myrank == 0)
  {
    if (numeroVertices < 10)
    {
      printMatrizCaminos(caminos, numeroVertices, numeroVertices);
      printMatrizPesos(distancia, numeroVertices, numeroVertices);
    }
    calcula_camino(distancia, caminos, numeroVertices);
  }
  MPI_Finalize();
}

float **Crear_matriz_pesos_consecutivo(int Filas, int Columnas)
{
  // crea un array de 2 dimensiones en posiciones contiguas de memoria
  float *mem_matriz;
  float **matriz;
  int fila, col;
  if (Filas <= 0)
  {
    printf("El numero de filas debe ser mayor que cero\n");
    return;
  }
  if (Columnas <= 0)
  {
    printf("El numero de filas debe ser mayor que cero\n");
    return;
  }
  mem_matriz = malloc(Filas * Columnas * sizeof(float));
  if (mem_matriz == NULL)
  {
    printf("Insuficiente espacio de memoria\n");
    return;
  }
  matriz = malloc(Filas * sizeof(float *));
  if (matriz == NULL)
  {
    printf("Insuficiente espacio de memoria\n");
    return;
  }
  for (fila = 0; fila < Filas; fila++)
    matriz[fila] = mem_matriz + (fila * Columnas);
  return matriz;
}

int **Crear_matriz_caminos_consecutivo(int Filas, int Columnas)
{
  // crea un array de 2 dimensiones en posiciones contiguas de memoria
  int *mem_matriz;
  int **matriz;
  int fila, col;
  if (Filas <= 0)
  {
    printf("El numero de filas debe ser mayor que cero\n");
    return;
  }
  if (Columnas <= 0)
  {
    printf("El numero de filas debe ser mayor que cero\n");
    return;
  }
  mem_matriz = malloc(Filas * Columnas * sizeof(int));
  if (mem_matriz == NULL)
  {
    printf("Insuficiente espacio de memoria\n");
    return;
  }
  matriz = malloc(Filas * sizeof(int *));
  if (matriz == NULL)
  {
    printf("Insuficiente espacio de memoria\n");
    return;
  }
  for (fila = 0; fila < Filas; fila++)
    matriz[fila] = mem_matriz + (fila * Columnas);
  return matriz;
}

void Definir_Grafo(int n, float **dist, int **caminos)
{
  // Inicializamos la matriz de pesos y la de caminos para el algoritmos de
  // Floyd-Warshall. Un 0 en la matriz de pesos indica que no hay arco. Para la
  // matriz de caminos se supone que los vertices se numeran de 1 a n.
  int i, j;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      if (i == j)
        dist[i][j] = 0;
      else
      {
        dist[i][j] =
            (11.0 * rand() / (RAND_MAX + 1.0)); // aleatorios 0 <= dist < 11
        dist[i][j] =
            ((double)((int)(dist[i][j] * 10))) / 10; // truncamos a 1 decimal
        if (dist[i][j] < 2)
          dist[i][j] = 0; // establecemos algunos a 0
      }
      if (dist[i][j] != 0)
        caminos[i][j] = i + 1;
      else
        caminos[i][j] = 0;
    }
  }
}

void printMatrizCaminos(int **a, int fila, int col)
{
  int i, j;
  char buffer[10];
  printf("     ");
  for (i = 0; i < col; ++i)
  {
    j = sprintf(buffer, "%c%d", 'V', i + 1);
    printf("%5s", buffer);
  }
  printf("\n");
  for (i = 0; i < fila; ++i)
  {
    j = sprintf(buffer, "%c%d", 'V', i + 1);
    printf("%5s", buffer);
    for (j = 0; j < col; ++j)
      printf("%5d", a[i][j]);
    printf("\n");
  }
  printf("\n");
}

void printMatrizPesos(float **a, int fila, int col)
{
  int i, j;
  char buffer[10];
  printf("     ");
  for (i = 0; i < col; ++i)
  {
    j = sprintf(buffer, "%c%d", 'V', i + 1);
    printf("%5s", buffer);
  }
  printf("\n");
  for (i = 0; i < fila; ++i)
  {
    j = sprintf(buffer, "%c%d", 'V', i + 1);
    printf("%5s", buffer);
    for (j = 0; j < col; ++j)
      printf("%5.1f", a[i][j]);
    printf("\n");
  }
  printf("\n");
}

void calcula_camino(float **a, int **b, int n)
{
  int i, count = 2, count2;
  int anterior;
  int *camino;
  int inicio = -1, fin = -1;

  while ((inicio < 0) || (inicio > n) || (fin < 0) || (fin > n))
  {
    printf("Vertices inicio y final: (0 0 para salir) ");
    getchar(); // Eliminar el car�cter de nueva l�nea o caracteres no deseados
    scanf("%d %d", &inicio, &fin);
  }

  while ((inicio != 0) && (fin != 0))
  {
    anterior = fin;
    while (b[inicio - 1][anterior - 1] != inicio)
    {
      anterior = b[inicio - 1][anterior - 1];
      count = count + 1;
    }
    count2 = count;
    camino = malloc(count * sizeof(int));
    anterior = fin;
    camino[count - 1] = fin;
    while (b[inicio - 1][anterior - 1] != inicio)
    {
      anterior = b[inicio - 1][anterior - 1];
      count = count - 1;
      camino[count - 1] = anterior;
    }
    camino[0] = inicio;
    printf("\nCamino mas corto de %d a %d:\n", inicio, fin);
    printf("          Peso: %5.1f\n", a[inicio - 1][fin - 1]);
    printf("        Camino: ");
    for (i = 0; i < count2; i++)
      printf("%d ", camino[i]);
    printf("\n");
    free(camino);

    inicio = -1;
    fin = -1;
    while ((inicio < 0) || (inicio > n) || (fin < 0) || (fin > n))
    {
      getchar(); // Eliminar el car�cter de nueva l�nea o caracteres no deseados
      printf("Vertices inicio y final: (0 0 para salir) ");
      scanf("%d %d", &inicio, &fin);
    }
  }
}
