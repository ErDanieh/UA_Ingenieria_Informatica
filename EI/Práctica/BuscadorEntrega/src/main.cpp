#include <iostream>
#include <string>
#include <list>
#include <sys/resource.h>
#include "tokenizador.h"
#include "indexadorHash.h"
#include "buscador.h"

using namespace std;
double getcputime(void)
{
    struct timeval tim;
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    tim = ru.ru_utime;
    double t = (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
    tim = ru.ru_stime;
    t += (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
    return t;
}
main()
{
    IndexadorHash b("./StopWordsEspanyol.txt", ". ,:", false, false,
                    "./indicePruebaEspanyol", 0, false, false);
    b.Indexar("ficherosTimes.txt");
    b.GuardarIndexacion();
    Buscador a("./indicePruebaEspanyol", 0);
    a.IndexarPregunta("KENNEDY ADMINISTRATION PRESSURE ON NGO DINH DIEM TO STOP SUPPRESSING THE BUDDHISTS . ");
    double aa = getcputime();
    a.Buscar(423);
    a.ImprimirResultadoBusqueda(423);
    double bb = getcputime() - aa;
    cout << "\nHa tardado " << bb << " segundos\n\n";
	#if 0
    time_t inicioB, finB;
    time(&inicioB);
    double aaB = getcputime();
    a.Buscar("CorpusTime/Preguntas/", 423, 1, 83);
    a.ImprimirResultadoBusqueda(423);
    double bbB = getcputime() - aaB;
    cout << "\nHa tardado " << bbB << " segundos\n\n";
	#endif
}