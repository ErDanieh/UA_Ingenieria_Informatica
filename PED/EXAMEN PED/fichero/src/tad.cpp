#include "tabbcalendario.h"
#include "tlistacalendario.h"
#include <iostream>
using namespace std;

int main()
{
    	TCalendario cales [] ={
		TCalendario(20, 1, 1900, NULL),
		TCalendario(10, 1, 1900, NULL),
		TCalendario(30, 1, 1900, NULL),			
		TCalendario(5, 1, 1900, NULL),
		TCalendario(15, 1, 1900, NULL),
		TCalendario(22, 1, 1900, NULL),
		TCalendario(3, 1, 1900, NULL),
		TCalendario(25, 1, 1900, NULL),
		TCalendario(24, 1, 1900, NULL),
		TCalendario(26, 1, 1900, NULL)
	};
	cout<<"WTF";
	TABBCalendario ab;
	for(int i = 0; i < 9; i++){
		ab.Insertar(cales[i]);
	}
	cout << ab.Inorden() << endl;
	cout << ab.Niveles() << endl;

	TListaCalendario lista;

	lista.Insertar(TCalendario(21, 1, 1900, NULL));
	lista.Insertar(TCalendario(22, 1, 1900, NULL));
	lista.Insertar(TCalendario(31, 1, 1900, NULL));
    lista.Insertar(TCalendario());

	cout << "la lista: " << lista << endl;

	TVectorCalendario v;

	cout << "Vector resultado: ";
	v = ab.ABBCamino(lista);
	for(int i = 1; i <= v.Tamano(); i++){
		cout << v[i];
		if(i != v.Tamano() - 1){
			cout << ", ";
		}
	}

	return 0;
}