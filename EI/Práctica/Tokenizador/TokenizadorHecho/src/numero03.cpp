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

a.DelimitadoresPalabra("@.,&");
a.Tokenizar("pal1 10.000,34 10,000.34 10.000.123.456.789.009,34 10,000,123,456,789,009.34 20.03 40,03 2005 10. 20, 10.0 20,0 La 20,12.456,7.8.9,", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar(".34 ,56", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1 10.00a 10.000.a.000 10/12/85 1,23E+10", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar("pal1&10.00@10.000&aaa@10/12/85", tokens);
	imprimirListaSTL(tokens);

a.Tokenizar(".34@@&,56", tokens);
	imprimirListaSTL(tokens);


a.PasarAminuscSinAcentos(true);
a.Tokenizar("Pal1&10.00@10.000&aaa@10/12/85 La", tokens);
	imprimirListaSTL(tokens);

a.CasosEspeciales (false);
a.Tokenizar("Pal1&10.00@10.000&000@10/12/85 La", tokens);
	imprimirListaSTL(tokens);


}
