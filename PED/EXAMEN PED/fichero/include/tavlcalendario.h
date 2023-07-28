#ifndef _TAVLCALENDARIO_H_
#define _TAVLCALENDARIO_H_
#include <iostream>
#include "../include/tvectorcalendario.h"
#include "../include/tcalendario.h"
using namespace std;

class TNodoAVL;
class TAVLCalendario;

class TAVLCalendario
{
    friend class TNodoAVL;

private:
    // Puntero al nodo raíz
    TNodoAVL *raiz;
    // AUXILIAR: devuelve el recorrido en INORDEN
    void InordenAux(TVectorCalendario &, int &) const;
    // AUXILIAR: devuelve el recorrido en PREORDEN
    void PreordenAux(TVectorCalendario &, int &) const;
    // AUXILIAR: devuelve el recorrido en POSTORDEN
    void PostordenAux(TVectorCalendario &, int &) const;

    bool Insertar(const TCalendario &, bool &);

    void DerechaDerecha();

    void DerechaIzquierda();

    void IzquierdaIzquierda();

    void IzquierdaDerecha();

    bool Borrar(const TCalendario &, bool &);

    TCalendario TCalMax() const;

public:
    // Constructor por defecto
    TAVLCalendario();
    // Constructor de copia
    TAVLCalendario(const TAVLCalendario &);
    // Destructor
    ~TAVLCalendario();
    // Sobrecarga del operador asignación
    TAVLCalendario &operator=(const TAVLCalendario &);

    // Sobrecarga del operador igualdad
    bool operator==(const TAVLCalendario &) const;
    // Sobrecarga del operador desigualdad
    bool operator!=(const TAVLCalendario &) const;
    // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
    bool EsVacio();
    // Inserta el elemento en el árbol
    bool Insertar(const TCalendario &);
    // Devuelve TRUE si el elemento está en el árbol, false en caso contrario
    bool Buscar(const TCalendario &) const;
    // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
    int Altura() const;
    // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
    int Nodos() const;
    // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
    int NodosHoja() const;
    // Devuelve el recorrido en INORDEN sobre un vector
    TVectorCalendario Inorden() const;
    // Devuelve el recorrido en PREORDEN sobre un vector
    TVectorCalendario Preorden() const;
    // Devuelve el recorrido en POSTORDEN sobre un vector
    TVectorCalendario Postorden() const;
    // Borra un TCalendario del árbol AVL
    bool Borrar(const TCalendario &);
    // Devuelve el elemento TCalendario raíz del árbol AVL
    TCalendario Raiz() const;
    // Sobrecarga del operador salida
    friend ostream &operator<<(ostream &, const TAVLCalendario &);
};

class TNodoAVL
{
    friend class TAVLCalendario;

private:
    // El elemento (etiqueta) del nodo
    TCalendario item;
    // Subárbol izquierdo y derecho
    TAVLCalendario iz, de;
    // Factor de equilibrio
    int fe;

public:
    //Constructor por defecto
    TNodoAVL();
    //Constructor copia
    TNodoAVL(const TNodoAVL &);
    //Destructor
    ~TNodoAVL();
    // Sobrecarga del operador asignación
    TNodoAVL &operator=(const TNodoAVL &);
};
#endif