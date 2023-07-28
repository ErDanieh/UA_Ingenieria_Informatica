#include <iostream>
#include "tcalendario.h"
#include "tvectorcalendario.h"
#include "tlistacalendario.h"
using namespace std;

int main(void){
	TCalendario a(10,10,2006, (char*) "mensaje 1");
	TCalendario b(11,10,2006, (char*) "mensaje 2");
	TCalendario c(12,10,2006, (char*) "mensaje 3");
	TCalendario d(13,10,2006, (char*) "mensaje 4");
	TCalendario e(14,10,2006, (char*) "mensaje 5");
	TCalendario f(15,10,2006, (char*) "mensaje 6");
	TCalendario g(16,10,2006, (char*) "mensaje 7");
	TCalendario h(17,10,2006, (char*) "mensaje 8");
	TCalendario i(18,10,2006, (char*) "mensaje 9");
	TCalendario j(19,10,2006, (char*) "mensaje 10");
	TCalendario k(20,10,2006, (char*) "mensaje 11");
	TCalendario l(21,10,2006, (char*) "mensaje 12");
	TListaCalendario lista;
	TListaCalendario lista2;
	
	lista.Insertar(a);
	lista.Insertar(b);
	lista.Insertar(c);
	

	cout << "original: " << lista << endl;

	lista2 = lista.ExtraerRango(1, lista.Longitud());
	cout << "despues de extraer la original: " << lista << endl;
	cout << "extraida: " << lista2 << endl;


	lista.Insertar(a);
	lista.Insertar(b);
	lista.Insertar(c);
	lista.Insertar(d);
	
	TListaCalendario primeros, ultimos;

	cout << "antes de partirla en 2: " << lista << endl;
	primeros = lista.ExtraerRango(-1, 2);
	ultimos = lista.ExtraerRango(3, 100);

	cout << "ultimos: " << ultimos << endl;
	cout << "primeros: " << primeros << endl;
	cout << "original: " << lista << endl;
	
	

	return 0;
}
