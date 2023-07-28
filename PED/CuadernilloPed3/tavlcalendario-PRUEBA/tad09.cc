// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad09.cc
// --------------------------------

// prueba el operador << .
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;


int main(void)
{
	TColaAVLCalendario cola;
	cout << cola << endl;


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
	{
		if(i != 3 && i != 5)
			c.Encolar(&va[i]);
		else
			c.Encolar(NULL);
	}
	
	cout << c << endl;

	return 0;
}
