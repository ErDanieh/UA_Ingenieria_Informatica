#include <iostream> 
#include <string>
#include "buscador.h"
#include "indexadorHash.h"

using namespace std;


main() {
IndexadorHash b("./StopWordsEspanyol.txt", ". ,:", false, false, "./indicePrueba", 0, false, false);

b.Indexar("./listaFicheros_corto.txt");
b.GuardarIndexacion();

Buscador a("./indicePrueba", 0);
string preg;
double kk1; double kb;

a.IndexarPregunta("pal1 pal4 pal2 pal3 pal1. pal2, pal4 pal2");

if(a.Buscar(1000))
	a.ImprimirResultadoBusqueda(10000);

a.CambiarFormulaSimilitud(1);

if(a.Buscar(100))
	a.ImprimirResultadoBusqueda(1000);

}
