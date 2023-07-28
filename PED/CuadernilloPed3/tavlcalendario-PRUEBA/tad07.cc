// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad07.cc
// --------------------------------

// prueba longitud.
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;

int main(void)
{
	TAVLCalendario arbolito;
	TCalendario cal1(1, 1, 1900, NULL), cal2(1, 1, 1900, NULL);
	TColaAVLCalendario c1;
	
	int i;

	arbolito.Insertar(cal1);
	arbolito.Insertar(cal2);

	cout << "LONGITUD VACIA: " << c1.Longitud() << endl;	
	c1.Encolar(&arbolito);
	c1.Encolar(NULL);
	c1.Encolar(&arbolito);
	c1.Encolar(NULL);
	cout << "LONGITUD: " << c1.Longitud() << endl;
	c1.Desencolar();
	cout << "LONGITUD UNO MENOS: " << c1.Longitud() << endl;
	c1.~TColaAVLCalendario();
	cout << "LONGITUD DE DESTRUIDA: " << c1.Longitud() << endl;


	return 0;
}
