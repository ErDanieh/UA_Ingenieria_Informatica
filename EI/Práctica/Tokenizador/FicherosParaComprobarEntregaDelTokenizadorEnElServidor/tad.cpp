#include <iostream> 
#include <string>
#include <list> 
#include "tokenizador.h"

using namespace std;

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
list<string> lt1, lt2;
Tokenizador b(" ", false, false);
b.Tokenizar("MS DOS OS 2 high low", lt2);

imprimirListaSTL(lt2);

}
