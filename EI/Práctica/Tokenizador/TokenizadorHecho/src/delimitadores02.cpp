#include <iostream>
#include <string>
#include <list>
#include "tokenizador.h"

using namespace std;

///////// Comprobación de que vacíe la lista resultado

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
        bool kCasosEspeciales = false, kpasarAminusculas = false;

        list<string> lt1, lt2;

Tokenizador a("@.&", false, false);
list<string> tokens;
a.AnyadirDelimitadoresPalabra("&_:/.?&-=#@");
cout << a << endl;

}
