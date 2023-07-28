#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"

using namespace std;

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol_corto1.txt", ". ,:", true, true, "./indicePrueba", 1, false, true);
a.ListarPalParada(); 
cout << a.DevolverFichPalParada () << " " << a.NumPalParada() << endl;

IndexadorHash b("./StopWordsEspanyol_corto2.txt", ". ,:", true, true, "./indicePrueba", 1, false, true);
b.ListarPalParada(); 
cout << b.DevolverFichPalParada () << " " << b.NumPalParada() << endl;
}
