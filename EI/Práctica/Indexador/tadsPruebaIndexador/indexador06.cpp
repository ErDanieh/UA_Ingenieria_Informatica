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

b.Indexar("./listaFicheros_corto.txt");
b.GuardarIndexacion();

IndexadorHash a("./indicePrueba");

cout << a.DevolverDelimitadores () << endl; 
cout << a.DevolverDirIndice () << endl; 
cout << a.DevolverTipoStemming () << endl; 
cout << a.DevolverAlmEnDisco () << endl; 

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

if(a.Devuelve("pal1", "corpus_corto/fichero1.txt", infDoc1))
	cout << "pal1 SE HA INDEXADO EN corpus_corto/fichero1.txt: " << infDoc1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO EN corpus_corto/fichero1.txt" << endl;

if(a.Devuelve("pal1", "fichero1.txt", infDoc1))
	cout << "pal1 SE HA INDEXADO EN fichero1.txt: " << infDoc1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO EN fichero1.txt" << endl;

if(a.Devuelve("pal7", "corpus_corto/fichero1.txt", infDoc1))
	cout << "pal7 SE HA INDEXADO EN corpus_corto/fichero1.txt: " << infDoc1 << endl;
else
	cout << "pal7 NO SE HA INDEXADO EN corpus_corto/fichero1.txt" << endl;

if(a.Existe("pal1"))
	cout << "pal1 SE HA INDEXADO" << endl;
else
	cout << "pal1 NO SE HA INDEXADO" << endl;

if(a.Existe("pal7"))
	cout << "pal7 SE HA INDEXADO" << endl;
else
	cout << "pal7 NO SE HA INDEXADO" << endl;

}
