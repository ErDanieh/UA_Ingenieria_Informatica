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
		bool kCasosEspeciales = true, kpasarAminusculas = false;

		list<string> lt1, lt2, lt3;

		Tokenizador a("[]# ", kCasosEspeciales, kpasarAminusculas);
		a.Tokenizar("MS#DOS OS_2 [high low]", lt1);
		imprimirListaSTL(lt1);

		a.AnyadirDelimitadoresPalabra("_ []");
		a.Tokenizar("MS#DOS OS_2 [high low]", lt2);
		imprimirListaSTL(lt2);

		a.DelimitadoresPalabra("_");
		a.Tokenizar("MS#DOS OS_2 [high low]", lt3);
		imprimirListaSTL(lt3);

}
