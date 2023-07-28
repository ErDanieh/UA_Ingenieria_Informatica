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
	TListaCalendario lista3;
	TListaPos p;

	lista.Insertar(a);
	lista.Insertar(b);
	lista.Insertar(c);
	lista.Insertar(l);

	lista2.Insertar(c);
	lista2.Insertar(d);
	lista2.Insertar(j);
	lista2.Insertar(i);
	lista2.Insertar(k);

	cout << "L=" << lista << endl;
	cout << "L2=" << lista2 << endl;
	lista3 = lista.SumarSubl(2, 4, lista2, 3, 100);
	cout << lista3 << endl;

	lista3 = lista.SumarSubl(-1, 1, lista2, lista2.Longitud(), lista2.Longitud() + 1);
	cout << lista3 << endl;


	lista3 = lista.SumarSubl(-1, 1000, lista2, 3, -2);
	cout << lista3 << endl;


	TListaCalendario nueva1;
	TListaCalendario nueva2;
	nueva1.Insertar(c);
	nueva1.Insertar(b);
	nueva1.Insertar(a);
	nueva2 = nueva1;
	lista3 = nueva1.SumarSubl(-1, 1000, nueva2, -1, 1000);
	cout << lista3 << endl;	


	return 0;
}
