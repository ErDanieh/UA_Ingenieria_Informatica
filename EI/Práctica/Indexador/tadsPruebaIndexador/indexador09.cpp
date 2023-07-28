#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"
#include "indexadorInformacion.h"

using namespace std;

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", false, false, "./indicePrueba", 0, false, true);

string preg1;
InformacionPregunta infPreg1;

if(a.DevuelvePregunta(preg1))
	cout << "ESTA INDEXADA LA PREGUNTA: " << preg1 << endl;
else
	cout << "NO HAY INDEXADA NINGUNA PREGUNTA" << endl;

if(a.DevuelvePregunta(infPreg1))
	cout << "ESTA INDEXADA LA PREGUNTA: " << infPreg1 << endl;
else
	cout << "NO HAY INDEXADA NINGUNA PREGUNTA" << endl;

a.IndexarPregunta("pal1 yo pal2 pal1. pal3 el  ");

if(a.DevuelvePregunta(preg1))
	cout << "ESTA INDEXADA LA PREGUNTA: " << preg1 << endl;
else
	cout << "NO HAY INDEXADA NINGUNA PREGUNTA" << endl;

InformacionTerminoPregunta inf1;

if(a.DevuelvePregunta("pal1", inf1))
	cout << "pal1 SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO EN LA PREGUNTA" << endl;

if(a.DevuelvePregunta("pal7", inf1))
	cout << "pal7 SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "pal7 NO SE HA INDEXADO EN LA PREGUNTA" << endl;

if(a.DevuelvePregunta(infPreg1))
	cout << "ESTA INDEXADA LA PREGUNTA: " << infPreg1 << endl;
else
	cout << "NO HAY INDEXADA NINGUNA PREGUNTA" << endl;


}
