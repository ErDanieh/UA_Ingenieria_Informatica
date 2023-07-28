#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
const int SIZE = 1000;
using namespace std;
int main()
{
 // A:
 clock_t begin = clock();
 // declarar una matriz de tamaño SIZExSIZE.
 int a[SIZE][SIZE];
 // una matriz in c se almacena en memoria como un array de una única
 // dimensión por filas.
 // Para una matriz de 3x3:
 // 1 2 3
 // 4 5 6
 // 7 8 9
 // se almacena en memoria como el array: 1 2 3 4 5 6 7 8 9
 // si recorremos la matriz por columnas, visitamos las celdas en el siguiente
 // orden: 1 4 7 2 5 8 3 6 9
 for(int i=0;i<SIZE;i++)
 {
    for(int j=0;j<SIZE;j++)
        a[j][i] = i+j;
 }
 
 double aTime = double(clock() - begin) / CLOCKS_PER_SEC;
 cout<<"Elapsed time: "<<aTime<<"s"<<endl;
 
 // B:
 begin = clock();
 int b[SIZE][SIZE];
 
 // si recorremos la matriz por filas, visitamos las celdas en el siguiente
 // orden: 1 2 3 4 5 6 7 8 9
 for(int i=0;i<SIZE;i++)
 {
    for(int j=0;j<SIZE;j++)
        b[i][j] = i+j;
 }
 
 double bTime = double(clock() - begin) / CLOCKS_PER_SEC;
 cout<<"Elapsed time: "<<bTime<<"s"<<endl;
 cout<<"Gain: "<<aTime/bTime<<endl;
}