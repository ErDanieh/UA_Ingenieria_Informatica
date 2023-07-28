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
	bool kCasosEspeciales = true, kpasarAminusculas = false;

	list<string> lt1, lt2;

Tokenizador a("-#", true, false); 
list<string> tokens; 

a.Tokenizar("MS-DOS p1 p2 UN-DOS-TRES", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1 -MS-DOS p1 p2", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1 MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1#MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);

a.DelimitadoresPalabra("/ ");
a.Tokenizar("MS-DOS p1 p2", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1 -MS-DOS p1 p2", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1 MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1#MS-DOS#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);


a.PasarAminuscSinAcentos(true);
a.Tokenizar("pal1#MS-DOSaA#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);

a.DelimitadoresPalabra("/-");
a.CasosEspeciales (false);
a.Tokenizar("pal1#MS-DOSaA#p3 p1 p2", tokens);
	imprimirListaSTL(tokens);


}
