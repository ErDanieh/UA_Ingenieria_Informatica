#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"
#include "indexadorInformacion.h"

using namespace std;

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", false, true, "./indicePrueba", 1, false, true);

string preg1;
InformacionPregunta infPreg1;

a.IndexarPregunta("pal1 conseguimo conseguimos pal2 pal1. pal3 EL  ");

InformacionTerminoPregunta inf1;

if(a.DevuelvePregunta("pal1", inf1))
	cout << "pal1 SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO EN LA PREGUNTA" << endl;

if(a.DevuelvePregunta("conseguimos", inf1))
	cout << "conseguimos SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "conseguimos NO SE HA INDEXADO EN LA PREGUNTA" << endl;

if(a.DevuelvePregunta("conseguimo", inf1))
	cout << "conseguimo SE HA INDEXADO EN LA PREGUNTA: " << inf1 << endl;
else
	cout << "conseguimo NO SE HA INDEXADO EN LA PREGUNTA" << endl;



}
