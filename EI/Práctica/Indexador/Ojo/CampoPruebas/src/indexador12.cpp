#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"
#include "indexadorInformacion.h"

using namespace std;

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", false, true, "./indicePrueba", 0, false, true);

string preg1;
InformacionPregunta infPreg1;

a.IndexarPregunta("pal1 Yo pal2 pal1. pal3 EL  ");

InformacionTerminoPregunta inf1;

if(a.DevuelvePregunta("pal1", inf1))
	cout << "pal1 SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO EN LA PREGUNTA" << endl;

if(a.DevuelvePregunta("Yo", inf1))
	cout << "Yo SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "Yo NO SE HA INDEXADO EN LA PREGUNTA" << endl;

if(a.DevuelvePregunta("EL", inf1))
	cout << "EL SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "EL NO SE HA INDEXADO EN LA PREGUNTA" << endl;



}
