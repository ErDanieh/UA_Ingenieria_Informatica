#include <iostream>
#include "tlistacalendario.h"
using namespace std;
int main(){
	TListaCalendario lista1, lista2;
	
	lista1.Insertar(TCalendario(1, 3, 1976, "jose"));
	lista1.Insertar(TCalendario(1, 3, 1976, "fran"));
	lista1.Insertar(TCalendario(1, 3, 1976, NULL));
	lista1.Insertar(TCalendario(2, 2, 1980, "pepico"));
	lista1.Insertar(TCalendario(3, 4, 2000, "juan"));

	lista2.Insertar(TCalendario(2, 3, 1976, NULL));
	lista2.Insertar(TCalendario(4, 4, 1981, "soy negro"));
	lista2.Insertar(TCalendario(3, 3, 1988, "soy azul"));
	lista2.Insertar(TCalendario());
	lista2.Insertar(TCalendario(3, 3, 1976, NULL));


	cout << "Lista 1: " << lista1 << endl;
	cout << "lista 2: " << lista2 << endl;
	
	cout << lista1.SumarSubl(1, 2, lista2, 3, 10) << endl;

	cout << lista1.SumarSubl(-1, 3, lista2, -2, 4) << endl;
	return 0;
}

