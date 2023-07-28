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

a.IndexarPregunta("pal1 yo pal2 pal1. PaL3 el  ");

InformacionTerminoPregunta inf1;

if(a.DevuelvePregunta("Pal3", inf1))
	cout << "Pal3 SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "Pal3 NO SE HA INDEXADO EN LA PREGUNTA" << endl;

if(a.DevuelvePregunta("PaL3", inf1))
	cout << "PaL3 SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "PaL3 NO SE HA INDEXADO EN LA PREGUNTA" << endl;


if(a.DevuelvePregunta("pal3", inf1))
	cout << "pal3 SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "pal3 NO SE HA INDEXADO EN LA PREGUNTA" << endl;



}
