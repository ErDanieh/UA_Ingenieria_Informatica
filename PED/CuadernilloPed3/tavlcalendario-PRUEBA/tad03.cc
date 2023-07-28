// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad03.cc
// --------------------------------

// prueba == y != de dos colas todo lo asquerosas posibles..
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;

int main(void)
{
	TAVLCalendario va[kARBOLES];
	TCalendario vc[kCALENDARIOS];
	TColaAVLCalendario c1, c2, c3, c4;
	TAVLCalendario *aux, unoDistinto;
	TCalendario distinto(2, 2, 2002, NULL);
	int i;

	unoDistinto.Insertar(distinto);
	// 10 arboles con un solo item. desde 1-1-2000 al 1-1-2009
	for(i = 0; i < kCALENDARIOS; i++)
	{
		vc[i].ModFecha(1, 1, i + 2000);
		va[i].Insertar(vc[i]);
	}
	

	if(c1 == c2)
		cout << "0-DOS COLAS VACIAS SON IGUALES" << endl;
	else
		cout << "ERROR: SI LAS DOS VACIAS" << endl;

	for(i = 0; i < kARBOLES; i++)
	{
		c1.Encolar(&va[i]);
		c2.Encolar(&va[i]);
		if(i == 3)
			c3.Encolar(&unoDistinto);
		else
			c3.Encolar(&va[i]);
		if(i <= 5)
			c4.Encolar(&va[i]);
	}

	if(c1 == c2)
		cout << "1-DOS COLAS CON LOS MISMOS ELEMENTOS SON IGUALES" << endl;
	else
		cout << "ERROR: IGUALES Y CON ELEMENTOS" << endl;


	if(c1 == c3)
		cout << "ERROR, el 4 elemento encolado es distinto, las colas tienen la misma longitud" << endl;
	else
		cout << "2-DISTINTAS, MISMA LONGITUD, PERO EL 4 ELEMENTO ENCOLADO DISTINTO" << endl;


	if(c1 == c4)
		cout << "ERROR, ERAN IGUALES HASTA QUE UNA SE QUEDO VACIA" << endl;
	else
		cout << "3-MISMOS ELEMENTOS, PERO UNA SE QUEDA VACIA" << endl;
	

	return 0;
}
