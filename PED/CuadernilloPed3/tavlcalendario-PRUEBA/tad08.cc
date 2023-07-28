// --------------------------------
// correctores: www.auladoce.com
// autor: jose manuel baldo pujante
// email: jmbp10m@msn.com
// corrector levelcola/tad08.cc
// --------------------------------

// prueba concatenacion.
#include <iostream>
#include "tavlcalendario.h"
const int kARBOLES = 10;
const int kCALENDARIOS = 10;
using namespace std;

void ImprimirColas(const TColaAVLCalendario &c)
{
	TColaAVLCalendario aux(c);
	TAVLCalendario *b;

	while(!aux.EsVacia())
	{
		b = aux.Cabeza();
		if(b)
			cout << b->Inorden() << ' ';
		aux.Desencolar();
	}
	cout << endl;

}

int main(void)
{
	TAVLCalendario va[kARBOLES];
	TCalendario vc[kCALENDARIOS];
	TColaAVLCalendario c1, c2, cR;
	int i;

	
	// copia de una vacia;
	cR = c1 + c2;
	
	if(cR.EsVacia())
		cout << "CONCATENACION DE VACIAS TAMBIEN ESTARÁ VACIA" << endl;

	for(i = 0; i < kCALENDARIOS; i++)
	{
		vc[i].ModFecha(1, 1, i + 2000);
		va[i].Insertar(vc[i]);
	}
	
	for(i = 0; i < kARBOLES; i++)
	{
		if(i < kCALENDARIOS / 2)
			c1.Encolar(&va[i]);
		else
			c2.Encolar(&va[i]);
	}

	// CONCATENACION DE DOS LLENAS.
	cout << endl << "CONCATENANDO DOS LLENAS" << endl;
	cR = c1 + c2;
	cout << "c1: "; 
	ImprimirColas(c1);
	cout << "c2: "; 
	ImprimirColas(c2);
	cout << "cR: "; 
	ImprimirColas(cR);

	// CONCATENACION DE VACIA + LLENA
	cout << endl << "CONCATENANDO VACIA + LLENA" << endl;
	c1.~TColaAVLCalendario();
	cR = c1 + c2;
	cout << "c1: "; 
	ImprimirColas(c1);
	cout << "c2: "; 
	ImprimirColas(c2);
	cout << "cR: "; 
	ImprimirColas(cR);

	cout << endl << "CONCATENANDO LLENA + VACIA" << endl;
	// CONCATENACION DE LLENA + VACIA
	cR = c2 + c1;	
	cout << "c1: "; 
	ImprimirColas(c1);
	cout << "c2: "; 
	ImprimirColas(c2);
	cout << "cR: "; 
	ImprimirColas(cR);

	return 0;
}
