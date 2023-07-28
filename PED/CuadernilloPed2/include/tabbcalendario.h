#ifndef _TABBCALENDARIO_H_
#define _TABBCALENDARIO_H_
#include <iostream>
#include "../include/tvectorcalendario.h"
#include "../include/tcalendario.h"
using namespace std;

class TNodoABB;

class TABBCalendario
{
	friend class TNodoABB;

private:
	// Puntero al nodo
	TNodoABB *raiz;
	// AUXILIAR: devuelve el recorrido en INORDEN
	void InordenAux(TVectorCalendario &, int &) const;
	// AUXILIAR: devuelve el recorrido en PREORDEN
	void PreordenAux(TVectorCalendario &, int &) const;
	// AUXILIAR: devuelve el recorrido en POSTORDEN
	void PostordenAux(TVectorCalendario &, int &) const;

	TCalendario TCalMax() const;

public:
	// Constructor por defecto
	TABBCalendario();
	// Constructor de copia
	TABBCalendario(const TABBCalendario &);
	// Destructor
	~TABBCalendario();
	// Sobrecarga del operador asignación
	TABBCalendario &operator=(const TABBCalendario &);
	// Sobrecarga del operador igualdad
	bool operator==(const TABBCalendario &) const;
	// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
	bool EsVacio() const;
	// Inserta el elemento en el árbol
	bool Insertar(const TCalendario &);

	// Borra el elemento en el árbol
	bool Borrar(const TCalendario &);
	// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
	bool Buscar(const TCalendario &) const;
	// Devuelve el elemento de la raíz del árbol
	TCalendario Raiz();
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
	// Devuelve el recorrido en NIVELES sobre un vector
	TVectorCalendario Niveles() const;
	// Sobrecarga del operador salida
	friend ostream &operator<<(ostream &, TABBCalendario &);
	// Suma de dos ABB
	TABBCalendario operator+(const TABBCalendario &) const;
	// Resta de dos ABB
	TABBCalendario operator-(const TABBCalendario &) const ;
};

class TNodoABB
{
	friend class TABBCalendario;

private:
	// Elemento del nodo
	TCalendario item;
	// Subárbol izquierdo y derecho
	TABBCalendario iz, de;
	//Hacemos clase amiga para

public:
	//Constructor por defecto
	TNodoABB();
	//Constructor copia
	TNodoABB(const TNodoABB &);
	//Destructor
	~TNodoABB();
	// Sobrecarga del operador asignación
	TNodoABB &operator=(const TNodoABB &);
};
#endif