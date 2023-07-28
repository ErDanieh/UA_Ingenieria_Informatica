#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"

using namespace std;

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", true, true, "./indicePrueba", 1, false, true);
cout << "IndexadorHash a:\n################\n" << a << endl;

IndexadorHash b("./StopWordsIngles.txt", ". ,:", true, false, "./indicePruebaIngles", 2, true, true);
cout << "IndexadorHash b:\n################\n" << b << endl;

cout << b.DevolverDelimitadores () << endl; 
cout << b.DevolverDirIndice () << endl; 
cout << b.DevolverTipoStemming () << endl; 
cout << b.DevolverAlmEnDisco () << endl; 
cout << b.DevolverAlmacenarPosTerm () << endl; 
cout << b.DevolverPasarAminuscSinAcentos () << endl; 
cout << b.DevolverCasosEspeciales () << endl; 

}
