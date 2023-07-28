// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad02.cc
// --------------------------------

// prueba Encolar, Desencolar sucesivamente.
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
	

	if(c.Encolar(&va[0]))
		cout << "encolado" << endl;
	if(c.Encolar(&va[1]))
		cout << "encolado" << endl;
	
	aux = c.Cabeza();
	if(c.Desencolar())
	{
		cout << "desencolado" << aux->Inorden() << endl;
	}
	aux = c.Cabeza();
	if(c.Desencolar())
	{
		c.Desencolar();
		cout << "desencolado" << aux->Inorden() << endl;
	}
	if(!c.Desencolar())
		cout << "NO DESENCOLA" << endl;
	else
		cout << "ERROR: DESENCOLA DE VACIA" << endl;


	if(c.Encolar(&va[2]))
		cout << "ENCOLADO SOBRE UNA COLA VACIA DESPUES DE DESENCOLAR:" << c.Cabeza()->Inorden() << endl;
	else
		cout << "ERROR AL INTENTAR ENCOLAR EN UNA COLA QUE DESENCOLAR DEJA VACIA." << endl;

	return 0;
}
