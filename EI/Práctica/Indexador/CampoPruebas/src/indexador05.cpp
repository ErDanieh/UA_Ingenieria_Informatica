#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"
#include "indexadorInformacion.h"

using namespace std;

/////////////////////////////////////////////////////////
// ATENCION: Actualizar convenientemente en el fichero indexador05.cpp.sal los tamanyos en bytes de los archivos y de la colecciOn
/////////////////////////////////////////////////////////

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", false, false, "./indicePrueba", 0, false, true);

a.Indexar("./listaFicheros_corto.txt");

if(a.BorraDoc("corpus_corto/fichero1.txt"))
	cout << "SE HA BORRADO DE LA INDEXACION: corpus_corto/fichero1.txt" << endl;
else
	cout << "NO SE HA BORRADO DE LA INDEXACION: corpus_corto/fichero1.txt" << endl;


InformacionTermino inf1;

if(a.Devuelve("pal2", inf1))
	cout << "pal2 SE HA INDEXADO: " << inf1 << endl;
else
	cout << "pal2 NO SE HA INDEXADO" << endl;

if(a.Devuelve("pal1", inf1))
	cout << "pal1 SE HA INDEXADO: " << inf1 << endl;
else
	cout << "pal1 NO SE HA INDEXADO" << endl;

cout << a.NumPalIndexadas() << endl;

a.ListarDocs("corpus_corto/fichero1.txt");
a.ListarDocs("corpus_corto/fichero2.txt");
if(a.ListarDocs("corpus_corto/fichero1.txt"))
	cout << "Existe el archivo corpus_corto/fichero1.txt" << endl;
else
	cout << "NO Existe el archivo corpus_corto/fichero1.txt" << endl;

a.ListarInfColeccDocs();

if(a.BorraDoc("corpus_corto/fichero1.txt"))
	cout << "SE HA BORRADO DE LA INDEXACION: corpus_corto/fichero1.txt" << endl;
else
	cout << "NO SE HA BORRADO DE LA INDEXACION: corpus_corto/fichero1.txt" << endl;

if(a.BorraDoc("corpus_corto/fichero7.txt"))
	cout << "SE HA BORRADO DE LA INDEXACION: corpus_corto/fichero7.txt" << endl;
else
	cout << "NO SE HA BORRADO DE LA INDEXACION: corpus_corto/fichero7.txt" << endl;


}
