// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad06.cc
// --------------------------------

// prueba destruccion.
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;

int main(void)
{
	TAVLCalendario arbolito, arbolva;
	TCalendario cal1(1, 1, 1900, NULL), cal2(1, 1, 1900, NULL);
	TColaAVLCalendario c1;
	
	int i;

	arbolito.Insertar(cal1);
	arbolito.Insertar(cal2);
	arbolva.Insertar(cal1);

	c1.~TColaAVLCalendario();
	cout << c1.Cabeza()<< endl;
	c1.EsVacia();
	c1.~TColaAVLCalendario();
	c1.EsVacia();	
	c1.Encolar(&arbolito);
	c1.Encolar(NULL);
	c1.Encolar(&arbolva);
	cout << c1.Cabeza()->Inorden() << endl;
	c1.Desencolar();
	c1.~TColaAVLCalendario();
	cout << c1.Cabeza()<< endl;

	return 0;
}
