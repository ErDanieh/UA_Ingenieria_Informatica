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

list<string> lt1, lt2, lt3, lt4;

Tokenizador p("/.;-", kCasosEspeciales, kpasarAminusculas );
cout << p << endl;
p.Tokenizar("MS DOS OS 2 high low", lt1);
imprimirListaSTL(lt1);

p.CasosEspeciales (false);
p.Tokenizar("MS DOS OS 2 high low", lt1);
imprimirListaSTL(lt1);


Tokenizador a(" ", kCasosEspeciales, kpasarAminusculas );
a.Tokenizar("MS DOS OS 2 high low", lt1);
imprimirListaSTL(lt1);

Tokenizador b(" ", kCasosEspeciales, kpasarAminusculas  );
b.Tokenizar("M", lt2);
imprimirListaSTL(lt2);

Tokenizador c(" ", kCasosEspeciales, kpasarAminusculas  );
c.Tokenizar(" ", lt3);
imprimirListaSTL(lt3);

Tokenizador d(" ", kCasosEspeciales, kpasarAminusculas  );
d.Tokenizar("", lt4);
imprimirListaSTL(lt4);
}
