#ifndef _TCALENDARIO_H_
#define _TCALENDARIO_H_
#include <iostream>
using namespace std;

class TCalendario
{

    friend ostream &operator<<(ostream &os, const TCalendario &c);

private:
    int dia, mes, anyo;
    char *mensaje;
    static bool FechaCorrecta(int d, int m, int a);
    static bool esBisiesto(int a);

public:
    //Constructor por defecto: inicializa dia, mes y anyo a 1/1/1900 y mensaje a NULL
    TCalendario();
    
    //Constructor que inicializa calendario con parámetros pasados
    TCalendario(int, int, int,const char *);

    //Constructor copia
    TCalendario(const TCalendario &);

    //Destructor
    ~TCalendario();

    // Sobrecarga del operador asignación
    TCalendario &operator=(const TCalendario &);

    //METODOS
    // Sobrecarga del operador: SUMA de fecha + un número de dias;
    TCalendario operator+(int) const;

    // Sobrecarga del operador: RESTA de fecha - un número de dias;
    TCalendario operator-(int) const;

    // Modifica la fecha incrementándola en un dia (con postincremento);
    TCalendario operator++(int);

    // Modifica la fecha incrementándola en un dia (con preincremento);
    TCalendario &operator++();

    // Modifica la fecha decrementándola en un dia (con postdecremento);
    TCalendario operator--(int);

    // Modifica la fecha decrementándola en un día (con predecremento);
    TCalendario &operator--();

    // Modifica la fecha
    bool ModFecha(int, int, int);

    // Modifica el mensaje
    bool ModMensaje(char *);

    // Sobrecarga del operador igualdad;
    bool operator==(const TCalendario &)const;

    // Sobrecarga del operador desigualdad;
    bool operator!=(const TCalendario &)const;
    
    // Sobrecarga del operador >; (ver ACLARACIÓN sobre ORDENACIÓN)
    bool operator>(const TCalendario &)const;

    // Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
    bool operator<(const TCalendario &)const;

    //TCalendario vacío
    bool EsVacio() const;

    // Devuelve el día del calendario;
    int Dia() const;

    // Devuelve el mes del calendario;
    int Mes() const;

    // Devuelve el año del calendario;
    int Anyo() const;

    // Devuelve el mensaje del calendario;
    char *Mensaje() const;
};
#endif
