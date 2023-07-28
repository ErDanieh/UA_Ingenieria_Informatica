// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad01.cc
// --------------------------------

// prueba Encolar, Desencolar y Cabeza, 10 encolamientos, 10 desencolamientos.
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;

int main(void)
{
	TAVLCalendario va[kARBOLES];
	TCalendario vc[kCALENDARIOS];
	TColaAVLCalendario c;
	TAVLCalendario *aux;
	int i;

	
	// 10 arboles con un solo item. desde 1-1-2000 al 1-1-2009
	for(i = 0; i < kCALENDARIOS; i++)
	{
		vc[i].ModFecha(1, 1, i + 2000);
		va[i].Insertar(vc[i]);
	}
	
	for(i = 0; i < kARBOLES; i++)
		cout << va[i].Inorden() << ' ';

	cout << endl;
	
	for(i = 0; i < kARBOLES; i++)
		c.Encolar(&va[i]);

	if(!c.EsVacia())
	{
		cout << "--COLA" << endl;
		for(i = 0; i < kARBOLES; i++)
		{
			aux = c.Cabeza();
			c.Desencolar();
			cout << aux->Inorden() << ' ';
		}
		cout << endl << "--FIN COLA" << endl;
		if(c.EsVacia())
			cout << "COLA VACIA" << endl;
	}
	else
		cout << "la cola esta vacia y tendria que tener 10 elementos" << endl;

	return 0;
}
