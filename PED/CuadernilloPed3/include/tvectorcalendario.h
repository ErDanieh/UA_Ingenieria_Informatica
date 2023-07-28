#ifndef _TVECTORCALENDARIO_H_
#define _TVECTORCALENDARIO_H_
#include <iostream>
#include "../include/tcalendario.h"
using namespace std;

class TVectorCalendario
{
    // Sobrecarga del operador salida
    friend ostream &operator<<(ostream &,const TVectorCalendario &);

private:
    TCalendario *c;
    int tamano;
    TCalendario error;

public:
    // Constructor por defecto
    TVectorCalendario();

    // Constructor a partir de un tamaño
    TVectorCalendario(int);

    // Constructor de copia
    TVectorCalendario(const TVectorCalendario &);

    // Destructor
    ~TVectorCalendario();

    // Sobrecarga del operador asignación
    TVectorCalendario &operator=(const TVectorCalendario &);

    // Sobrecarga del operador igualdad
    bool operator==(const TVectorCalendario &co) const;

    // Sobrecarga del operador desigualdad
    bool operator!=(const TVectorCalendario &) const;

    // Sobrecarga del operador corchete (parte IZQUIERDA)
    TCalendario &operator[](int);

    // Sobrecarga del operador corchete (parte DERECHA)
    TCalendario operator[](int) const;

    // Tamaño del vector (posiciones TOTALES)
    int Tamano() const;

    // Cantidad de posiciones OCUPADAS (no vacías) en el vector
    int Ocupadas() const;

    // Devuelve TRUE si existe el calendario en el vector
    bool ExisteCal(TCalendario &) const;

    // Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O
    //POSTERIOR a la pasada
    void MostrarMensajes(int, int, int) const;

    // REDIMENSIONAR el vectorde TCalendario
    bool Redimensionar(int);

    //Comprobador de existe un calendario concreto en el vector
    bool ExisteCal(const TCalendario &cal) const;
};
#endif
