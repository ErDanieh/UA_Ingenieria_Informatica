#include <iostream>
#include <cstring>
#include "../include/tabbcalendario.h"
#include "../include/tvectorcalendario.h"
#include "../include/tcalendario.h"
#include <queue>

/**
 * @brief Construct a new TNodoABB::TNodoABB object
 * 
 */
TNodoABB::TNodoABB()
{
    //Todo se inicializa con el constructor por defecto
}

/**
 * @brief Construct a new TNodoABB::TNodoABB object
 * 
 * @param parametros a adjudicar
 */
TNodoABB::TNodoABB(const TNodoABB &n) : iz(n.iz), de(n.de), item(n.item)
{
}

/**
 * @brief Sobrecarga de operador asignación
 * 
 * @param n parametro a asignar
 * @return TNodoABB& this
 */
TNodoABB &TNodoABB::operator=(const TNodoABB &n)
{
    de = n.de;
    iz = n.iz;
    item = n.item;
    return *this;
}

/**
 * @brief Destroy the TNodoABB::TNodoABB object
 * 
 */
TNodoABB::~TNodoABB()
{
}
////////////////////////////////////////////////////////////////////////////

/**
 * @brief Construct a new TABBCalendario::TABBCalendario object
 * 
 */
TABBCalendario::TABBCalendario()
{
    raiz = NULL;
}

/**
 * @brief Construct a new TABBCalendario::TABBCalendario object
 * 
 * @param copyArb 
 */
TABBCalendario::TABBCalendario(const TABBCalendario &copyArb)
{
    if (copyArb.raiz == NULL)
        raiz = NULL;
    else
        raiz = new TNodoABB(*(copyArb.raiz));
}

/**
 * @brief Buscar el TCalendario más grand de las ramas
 * 
 * @return TCalendario 
 */
TCalendario TABBCalendario::TCalMax() const
{
    TCalendario biggerThan;
    if (raiz->de.raiz == NULL)
    {
        biggerThan = raiz->item;
    }
    else
    {
        biggerThan = raiz->de.TCalMax();
    }
    return biggerThan;
}

/**
 * @brief Sobrecarga operador asignación 
 * 
 * @param toCopy asignador
 * @return TABBCalendario& 
 */
TABBCalendario &TABBCalendario::operator=(const TABBCalendario &toCopy)
{
    //SI el arbol es diferente
    if (this != &toCopy)
    {
        //Lo destruyo
        this->~TABBCalendario();
        //Y si la raiz no es nula
        if (toCopy.raiz != NULL)
        {
            //Creo un nuevo nodo y asigno el nuevo nodo
            raiz = new TNodoABB();
            *raiz = *(toCopy.raiz);
        }
    }
    return *this;
}

/**
 * @brief Destroy the TABBCalendario::TABBCalendario object
 * 
 */
TABBCalendario::~TABBCalendario()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

//Comprueba si el arbol es vacio o no
bool TABBCalendario::EsVacio() const
{
    if (raiz == NULL)
        return true;
    else
        return false;
}

/**
 * @brief Inserta un nuevo nodo en el arbol
 * 
 * @param ins 
 * @return true si se inserta
 * @return false si no se inserta
 */
bool TABBCalendario::Insertar(const TCalendario &ins)
{
    bool insertado = false;
    if (raiz != NULL) //Si tenemos nodos comparamos
    {
        if (raiz->item == ins) //Si lo encontramos no lo metemos
            insertado = false;
        else
        {
            //Si es menor se va para la izquierda
            if (ins < raiz->item)
                insertado = raiz->iz.Insertar(ins);
            else //Si es biggerThan se va para la derecha
                insertado = raiz->de.Insertar(ins);
        }
    }
    else
    { //Cuando encontramos un final de arbol lo metemos
        raiz = new TNodoABB();
        raiz->item = ins;
        insertado = true;
    }
    return insertado;
}

/**
 * @brief Cantidad de nodos de un arbol
 * 
 * @return int nodos
 */
int TABBCalendario::Nodos() const
{
    int count = 0;
    if (raiz != NULL)
    {
        count = 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    }
    else
    {
        return count;
    }
    return count;
}

/**
 * @brief Devuelve el vector con el recorrido inorden
 * 
 * @return TVectorCalendario 
 */
TVectorCalendario TABBCalendario::Inorden() const
{
    int pos;
    //Inicializamos el vector con la cantidad de nodos que tenemos
    TVectorCalendario vec(Nodos());
    pos = 1;              //Inicializamos la posicion
    InordenAux(vec, pos); //Se realiza el inorden
    return vec;
}

// AUXILIAR: devuelve el recorrido en INORDEN
void TABBCalendario::InordenAux(TVectorCalendario &vec, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.InordenAux(vec, pos); //Visitamos arbol izquierdo
        vec[pos] = raiz->item;         //Visitamos la raiz
        pos++;
        raiz->de.InordenAux(vec, pos); //Visitamos la derecha
    }
}

/**
 * @brief Devuebe el vector con el recorrido Preorden
 * 
 * @return TVectorCalendario 
 */
TVectorCalendario TABBCalendario::Preorden() const
{
    int pos;
    //Inicializamos el vector con la cantidad de nodos que tenemos
    TVectorCalendario vec(Nodos());
    pos = 1;               //Inicializamos la posicion
    PreordenAux(vec, pos); //Se realiza el inorden
    return vec;
}

// AUXILIAR: devuelve el recorrido en Preorden RZ IZ DE
void TABBCalendario::PreordenAux(TVectorCalendario &vec, int &pos) const
{
    if (raiz != NULL)
    {
        vec[pos] = raiz->item; //Visitamos la raiz
        pos++;
        raiz->iz.PreordenAux(vec, pos); //Visitamos arbol izquierdo
        raiz->de.PreordenAux(vec, pos); //Visitamos la derecha
    }
}

/**
 * @brief Devuelce el vector con el recorrido Postorden
 * 
 * @return TVectorCalendario 
 */
TVectorCalendario TABBCalendario::Postorden() const
{
    int pos;
    pos = 1;
    TVectorCalendario vec(Nodos());
    PostordenAux(vec, pos);
    return vec;
}

// AUXILIAR: devuelve el recorrido en Postorden IZ DE RZ
void TABBCalendario::PostordenAux(TVectorCalendario &vec, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.PostordenAux(vec, pos); //Visitamos arbol izquierdo
        raiz->de.PostordenAux(vec, pos); //Visitamos la derecha
        vec[pos] = raiz->item;           //Visitamos la raiz
        pos++;
    }
}

/**
 * @brief Saca la altura del arbol binario
 * 
 * @return int altura
 */
int TABBCalendario::Altura() const
{
    int alt = 0;
    int altd = 0;
    int alti = 0;

    if (raiz != NULL)
    {
        alti = raiz->iz.Altura();
        altd = raiz->de.Altura();

        if (altd < alti)
            alt = alti + 1; //+1 del nodo actual
        else
            alt = altd + 1;
    }
    //Devolvemos la altura máxima entre el arbol izq y der
    return alt;
}

/**
 * @brief Cantidad de nos hojas de un arbol
 * 
 * @return int 
 */
int TABBCalendario::NodosHoja() const
{
    if (raiz != NULL)
    {
        if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
            return 1; //Si no tiene nodo izquierdo ni derecho es hoja y suma
        else
            return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
        //Sino pasamos a sus nodos hijos
    }
    else
        return 0;
}

/**
 * @brief Sobrecarga del operador == 
 * 
 * @param arbolBinario comparar
 * @return true 
 * @return false 
 */
bool TABBCalendario::operator==(const TABBCalendario &arbolBinario) const
{
    if (Inorden() == arbolBinario.Inorden())
        return true;
    else
        return false;
}

/**
 * @brief Busca un TCalendario a traves de los nodos del arbol
 * 
 * @param buscado 
 * @return true 
 * @return false 
 */
bool TABBCalendario::Buscar(const TCalendario &buscado) const
{
    bool found;
    found = false;

    if (raiz == NULL)
    {
        return found;
    }
    else
    {
        if (raiz->item == buscado) //Si lo encuentras
            found = true;
        else
        {
            //Si es más pequeño nos vamos a la izquierda
            if (buscado < raiz->item)
                found = raiz->iz.Buscar(buscado);
            else
                found = raiz->de.Buscar(buscado);
        }
    }
    return found;
}
/**
 * @brief Devuelve la raiz de un arbol
 * 
 * @return TCalendario 
 */
TCalendario TABBCalendario::Raiz()
{
    return raiz->item;
}

/**
 * @brief Borra un TCalendario o nodo de un arbol y lo reordena
 * 
 * @param borrador 
 * @return true 
 * @return false 
 */
bool TABBCalendario::Borrar(const TCalendario &borrador)
{
    bool eliminado = false;
    TCalendario biggerThan;
    TNodoABB *pibot;

    if (raiz != NULL)
    {
        if (borrador < raiz->item)
            eliminado = raiz->iz.Borrar(borrador); //Si el elemento es menor vamos a la izquerda
        else
        {
            if (borrador > raiz->item)
                eliminado = raiz->de.Borrar(borrador); //Si el elemento es mayor vamos a la derecha
            else if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
            {
                delete raiz;
                raiz = NULL;
                eliminado = true;
            }
            else if (raiz->iz.raiz != NULL && raiz->de.raiz == NULL)
            {
                eliminado = true;
                pibot = raiz;
                raiz = raiz->iz.raiz;
                pibot->iz.raiz = NULL;
                delete pibot;
            }
            else if (raiz->iz.raiz == NULL && raiz->de.raiz != NULL)
            {
                eliminado = true;
                pibot = raiz;
                raiz = raiz->de.raiz;
                pibot->de.raiz = NULL;
                delete pibot;
            }
            else
            {
                eliminado = true;
                biggerThan = raiz->iz.TCalMax();
                raiz->item = biggerThan;
                raiz->iz.Borrar(biggerThan);
            }
        }
    }

    return eliminado;
}

/**
 * @brief Recorrido por niveles del Arbol 
 * 
 * @return TVectorCalendario 
 */
TVectorCalendario TABBCalendario::Niveles() const
{
    TVectorCalendario calendariosVector(Nodos());
    int posible = 1;
    queue<TNodoABB *> colab;
    TNodoABB *sacaCal;

    if (raiz != NULL)
    {
        colab.push(raiz); // encolo la raiz del arbol
        while (!colab.empty())
        {
            sacaCal = colab.front();
            colab.pop();
            calendariosVector[posible] = sacaCal->item;
            posible++;
            if (sacaCal->iz.raiz != NULL)
                colab.push(sacaCal->iz.raiz);

            if (sacaCal->de.raiz != NULL)
                colab.push(sacaCal->de.raiz);
        }
    }
    return calendariosVector;
}

/**
 * @brief Operador suma un arbol binario a this
 * 
 * @param ToSuma 
 * @return TABBCalendario 
 */
TABBCalendario TABBCalendario::operator+(const TABBCalendario &ToSuma) const
{
    //Realizamos una copia del arbol original
    TABBCalendario copiaOriginal(*this);

    //Sacamos su inorden
    TVectorCalendario vectorInorden = ToSuma.Inorden();
    //Modificamos el inorden
    for (int i = 1; i <= vectorInorden.Tamano(); i++)
        copiaOriginal.Insertar(vectorInorden[i]);
    return copiaOriginal;
}

/**
 * @brief Operador Resta Quita un arbolbinario a this
 * 
 * @param ToResta Arbol a restar
 * @return TABBCalendario
 */
TABBCalendario TABBCalendario::operator-(const TABBCalendario &ToResta) const
{
    TABBCalendario resultado;
    TVectorCalendario vectorInorden = Inorden();
    for (int i = 1; i <= vectorInorden.Tamano(); i++)
    {
        if (!ToResta.Buscar(vectorInorden[i]))
            resultado.Insertar(vectorInorden[i]);
    }
    return resultado;
}

ostream &operator<<(ostream &os, const TABBCalendario &c)
{
    
    TVectorCalendario aux(c.Nodos());
    aux = c.Niveles();
    return os << aux;
}