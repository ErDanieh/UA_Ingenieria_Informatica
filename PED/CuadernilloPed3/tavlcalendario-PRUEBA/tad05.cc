// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad05.cc
// --------------------------------

// prueba OPERADOR ASIGNACION.
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;

int main(void)
{
	TAVLCalendario va[kARBOLES];
	TCalendario vc[kCALENDARIOS];
	TColaAVLCalendario c1, c2;
	int i;

	
	// copia de una vacia;
	TColaAVLCalendario copiaVacia;
	copiaVacia = c1;
	if(c1 == copiaVacia && copiaVacia.EsVacia() && copiaVacia.Cabeza() == NULL)
		cout << "0-ASIGNACION DE VACIA BIEN" << endl;
	else
		cout << "ERROR EN ASIGNACION DE VACIA" << endl;



	for(i = 0; i < kCALENDARIOS; i++)
	{
		vc[i].ModFecha(1, 1, i + 2000);
		va[i].Insertar(vc[i]);
	}
	
	for(i = 0; i < kARBOLES; i++)
	{
		c1.Encolar(&va[i]);
		if(i%2)
			c2.Encolar(&va[i]);
	}
	// copia de una llena.
	TColaAVLCalendario copiaLLena;
	copiaLLena = c1;
	
	if(c1 == copiaLLena && c1.Cabeza() == copiaLLena.Cabeza())
		cout << "1-ASIGNACION DE LLENA BIEN" << endl;
	else
		cout << "FALLO EN ASIGNACION, O EN OPERADOR == O EN CABEZA" << endl;

	// asignar una vacia a una llena;
	copiaLLena = copiaVacia;
	if(copiaLLena == copiaVacia && copiaLLena.EsVacia() && copiaLLena.Cabeza() == NULL)
		cout << "2-ASIGNACION DE LLENA A VACIA" << endl;
	else
		cout << "ERROR EN ASIGNACION DE LLENA A VACIA" << endl;

	// asignar dos llenas distintas.
	c1 = c2;
	if(c1 == c2 && c1.Cabeza() == c2.Cabeza() && !c1.EsVacia() && !c2.EsVacia())
		cout << "3-ASIGNACION DE UNA LLENA A OTRA LLENA" << endl;
	else
		cout << "ERROR EN ASGINACION DE UNA LLENA A OTRA"  << endl;

	// autoAsignacion.
	c1 = c1;
	if(!c1.EsVacia() && c1 == c2)
		cout << "4-TODO BIEN" << endl;
	else
		cout << "REPAMPANOS, NO EVISTASTE LA AUTOASIGANCIOOOON!!!" << endl;
	return 0;
}
