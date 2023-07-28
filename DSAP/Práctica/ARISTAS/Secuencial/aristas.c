#include <stdlib.h>

// Estructura que contiene lo necesario para almacenar una imagen en formato PGM
typedef struct {
    int row;  // número de filas en la imagen
    int col;  // número de columnas en la imagen
    int max_gray; // maximo valor gray
    int **matrix; // matriz de pixeles entre 0 y 255
} PGMData;

int **CrearArray2D_int(int, int);
void LiberarArray2D_int(int, double **);
void readPGM(char *, PGMData *);
void writePGM(char *, PGMData *);
void Filtro_Laplace(int **, int **, int, int);
void crea_pgm(int, int, int, int **, PGMData *);

int main(int argc, char **argv)
{
	char archivo_imagen_ori[100] = "logo.pgm";
	char archivo_imagen_aristas[100] = "logo_edge.pgm";

	PGMData img_data, img_edge;

	switch (argc)
        {
                case 2: strcpy(archivo_imagen_ori, argv[1]);
                        strcat(archivo_imagen_ori, ".pgm");
                        strcpy(archivo_imagen_aristas, argv[1]);
                        strcat(archivo_imagen_aristas, "_edge.pgm");
			break;
                case 1: break;
                default: printf("Demasiados parametros\n");
                         return 0;
        }

	printf("\n  *************** DATOS DE LA EJECUCION ***************************\n");
	printf("  * Archivo imagen original   : %25s         *\n", archivo_imagen_ori);
	printf("  * Archivo imagen con aristas: %25s         *\n", archivo_imagen_aristas);
	printf("  *****************************************************************\n\n");
	printf("  Leyendo imagen \"%s\" ... \n", archivo_imagen_ori);

	readPGM(archivo_imagen_ori, &img_data);
	printf("  Dimension de la imagen: %d x %d\n", img_data.row, img_data.col);
 
	printf("  Aplicando el filtro de Laplace ...\n");
	img_edge.matrix = CrearArray2D_int(img_data.row,img_data.col);
	img_edge.row = img_data.row;
	img_edge.col = img_data.col;
	img_edge.max_gray = img_data.max_gray;
	Filtro_Laplace(img_data.matrix, img_edge.matrix, img_data.row, img_data.col);
	printf("  Guardando la imagen con la detección de aristas en \"%s\"\n\n",archivo_imagen_aristas);
	writePGM(archivo_imagen_aristas, &img_edge);

	LiberarArray2D_int(img_data.row, img_data.matrix);
	LiberarArray2D_int(img_edge.row, img_edge.matrix);
}
