// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad04.cc
// --------------------------------

// prueba CONSTRUCTOR COPIA.
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;

int main(void)
{
	TAVLCalendario va[kARBOLES];
	TCalendario vc[kCALENDARIOS];
	TColaAVLCalendario c1;
	int i;

	
	// copia de una vacia;
	TColaAVLCalendario copiaVacia(c1);
	if(c1 == copiaVacia && copiaVacia.EsVacia() && copiaVacia.Cabeza() == NULL)
		cout << "COPIA DE VACIA BIEN" << endl;
	else
		cout << "ERROR EN COPIA DE VACIA" << endl;



	for(i = 0; i < kCALENDARIOS; i++)
	{
		vc[i].ModFecha(1, 1, i + 2000);
		va[i].Insertar(vc[i]);
	}
	
	for(i = 0; i < kARBOLES; i++)
		c1.Encolar(&va[i]);

	// copia de una llena.
	TColaAVLCalendario copiaLLena(c1);
	
	if(c1 == copiaLLena && c1.Cabeza() == copiaLLena.Cabeza())
		cout << "COPIA DE LLENAS BIEN" << endl;
	else
		cout << "FALLO EN COPIA, O EN OPERADOR == O EN CABEZA" << endl;


	return 0;
}
