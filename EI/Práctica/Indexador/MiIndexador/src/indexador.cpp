#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"

using namespace std;

/////////////////////////////////////////////////////////
// ATENCIÓN: Actualizar convenientemente en el fichero indexador03.cpp.sal los tamanyos en bytes de los archivos y de la colección
/////////////////////////////////////////////////////////

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", false, false, "./indicePrueba", 0, false, true);

if(a.Indexar("./listaFicheros_corto.txt"))
	cout << "Indexacion terminada" << endl;
else
	cout << "Indexacion NO terminada" << endl;
cout << a.NumPalIndexadas() << endl;

a.ListarDocs("corpus_corto/fichero1.txt");
a.ListarDocs("corpus_corto/fichero2.txt");
if(a.ListarDocs("corpus_corto/fichero3.txt"))
	cout << "Existe el archivo corpus_corto/fichero3.txt" << endl;
else
	cout << "NO Existe el archivo corpus_corto/fichero3.txt" << endl;

a.ListarInfColeccDocs();

}
