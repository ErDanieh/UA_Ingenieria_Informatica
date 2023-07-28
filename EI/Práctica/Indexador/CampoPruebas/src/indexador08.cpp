#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"
#include "indexadorInformacion.h"

using namespace std;

int
main(void)
{
IndexadorHash b("./StopWordsEspanyol.txt", ". ,:", false, false, "./indicePrueba", 0, false, true);

if(b.IndexarDirectorio("./directorio_que_no_existe"))
	cout << "SE HA INDEXADO EL DIRECTORIO ./directorio_que_no_existe" << endl;
else
	cout << "NO SE HA INDEXADO EL DIRECTORIO ./directorio_que_no_existe" << endl;

IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", false, false, "./indicePrueba", 0, false, true);

if(a.IndexarDirectorio("./corpus_corto"))
	cout << "SE HA INDEXADO EL DIRECTORIO ./corpus_corto" << endl;
else
	cout << "NO SE HA INDEXADO EL DIRECTORIO ./corpus_corto" << endl;

InformacionTermino inf1;

if(a.Devuelve("pal1", inf1))
	cout << "pal1 SE HA INDEXADO: " << inf1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO" << endl;

if(a.Devuelve("pal7", inf1))
	cout << "pal7 SE HA INDEXADO: " << inf1 << endl;
else
	cout << "pal7 NO SE HA INDEXADO" << endl;

InfTermDoc infDoc1;

if(a.Devuelve("pal1", "./corpus_corto/fichero1.txt", infDoc1))
	cout << "pal1 SE HA INDEXADO EN ./corpus_corto/fichero1.txt: " << infDoc1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO EN ./corpus_corto/fichero1.txt" << endl;

if(a.Devuelve("pal1", "fichero1.txt", infDoc1))
	cout << "pal1 SE HA INDEXADO EN fichero1.txt: " << infDoc1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO EN fichero1.txt" << endl;

if(a.Devuelve("pal7", "./corpus_corto/fichero1.txt", infDoc1))
	cout << "pal7 SE HA INDEXADO EN ./corpus_corto/fichero1.txt: " << infDoc1 << endl;
else
	cout << "pal7 NO SE HA INDEXADO EN ./corpus_corto/fichero1.txt" << endl;

if(a.Existe("pal1"))
	cout << "pal1 SE HA INDEXADO" << endl;
else
	cout << "pal1 NO SE HA INDEXADO" << endl;

if(a.Existe("pal7"))
	cout << "pal7 SE HA INDEXADO" << endl;
else
	cout << "pal7 NO SE HA INDEXADO" << endl;

}
