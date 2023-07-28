#include <iostream> 
#include <string>
#include <list> 
#include "tokenizador.h"
#include <ctime> 

using namespace std;

///////// Comprobaci n de que vac e la lista resultado

void imprimirListaSTL(const list<string>& cadena)
{
        list<string>::const_iterator itCadena;
        for(itCadena=cadena.begin();itCadena!=cadena.end();itCadena++)
        {
                cout << (*itCadena) << ", ";
        }
        cout << endl;
}

int
main(void)
{
	bool kCasosEspeciales = true, kpasarAminusculas = false;

	list<string> lt1, lt2;
unsigned t0, t1;
 
t0=clock();
Tokenizador a("", true, false); 
list<string> tokens; 


a.TokenizarListaFicheros("listaFicheros.txt");
t1 = clock();

double time = (double(t1-t0)/CLOCKS_PER_SEC);
cout << "Execution Time: " << time << endl;
}
