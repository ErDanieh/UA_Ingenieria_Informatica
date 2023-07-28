#include <iostream>
#include <cstring>
#include "../include/tavlcalendario.h"
#include "../include/tvectorcalendario.h"
#include "../include/tcalendario.h"
#include <queue>

/**
 * @brief Construct a new TNodoAVL::TNodoAVl object
 * 
 */
TNodoAVL::TNodoAVL()
{
    //Factor de equilibrio se inicializa a 0
    fe = 0;
}

/**
 * @brief Construct a new TNodoAVL::TNodoAVL object
 * 
 * @param n arbol a copiar
 */
TNodoAVL::TNodoAVL(const TNodoAVL &n) : iz(n.iz), de(n.de), item(n.item), fe(n.fe) {}

/**
 * @brief Operador Asignacioón
 * 
 * @param n 
 * @return TNodoAVL& 
 */
TNodoAVL &TNodoAVL::operator=(const TNodoAVL &n)
{
    de = n.de;
    iz = n.iz;
    item = n.item;
    fe = n.fe;
    return *this;
}

/**
 * @brief Destroy the TNodoAVL::TNodoAVL object
 * 
 */
TNodoAVL::~TNodoAVL()
{
}
//////////////////////////////////////////////////////////////////////////

/**
 * @brief Construct a new TAVLCalendario::TAVLCalendario object
 * 
 */
TAVLCalendario::TAVLCalendario()
{
    raiz = NULL;
}

/**
 * @brief Destroy the TAVLCalendario::TAVLCalendario object
 * 
 */
TAVLCalendario::~TAVLCalendario()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

/**
 * @brief Construct a new TAVLCalendario::TAVLCalendario object
 * 
 * @param copyArb 
 */
TAVLCalendario::TAVLCalendario(const TAVLCalendario &copyArb)
{
    //Copiamos el arbol si no es vacio
    if (copyArb.raiz == NULL)
        raiz = NULL;
    else
        raiz = new TNodoAVL(*(copyArb.raiz));
}

/**
 * @brief Operador asignación de arbolAVL
 * 
 * @param toCopy 
 * @return TAVLCalendario& 
 */
TAVLCalendario &TAVLCalendario::operator=(const TAVLCalendario &toCopy)
{
    //SI el arbol es diferente
    if (this != &toCopy)
    {
        //Lo destruyo
        this->~TAVLCalendario();
        //Y si la raiz no es nula
        if (toCopy.raiz != NULL)
        {
            //Creo un nuevo nodo y asigno el nuevo nodo
            raiz = new TNodoAVL();
            *raiz = *(toCopy.raiz);
        }
    }
    return *this;
}

/**
 * @brief Inserta un nuevo nodo en el arbol
 * 
 * @param cale 
 * @return true 
 * @return false 
 */
bool TAVLCalendario::Insertar(const TCalendario &cale)
{
    bool growup = false;
    //Devolvemos la función auxiliar que lo inserta y reorganiza el arbol
    return Insertar(cale, growup);
}

/**
 * @brief Manera auxiliar de ordenar un arbol mirando si crece de izquierda o derecha
 * 
 * @param cale Insertar 
 * @param grow Crece
 * @return true 
 * @return false 
 */
bool TAVLCalendario::Insertar(const TCalendario &cale, bool &grow)
{
    //Inicializamos todo a false
    bool growIz = false;
    bool growDe = false;
    bool ins = false;
    if (raiz == NULL)
    {
        raiz = new TNodoAVL();
        raiz->item = cale;
        ins = true;
        grow = true;
    }
    else
    {
        //Miramos donde debemos insertar el arbol si izquierda o derecha
        if (raiz->item != cale)
        {
            if (cale < raiz->item)
            {
                ins = raiz->iz.Insertar(cale, growIz);
            }
            else
            {
                ins = raiz->de.Insertar(cale, growDe);
            }
        }
        else
        {
            ins = false;
        }
        //Hasta aqui solo hemos llegado al nodo donde vamos a insertar
        //Procedemos a reequilibrar el arbol
        if (growDe) //Si crece el derecho
        {
            raiz->fe++; //Incrementamos el factor de equilibrio del nodo
            switch (raiz->fe)
            {
            case 2: //No crece el arbol y lo reorganizamos
                grow = false;
                switch (raiz->de.raiz->fe)
                {
                case -1:
                    DerechaIzquierda();
                    break;
                case 1:
                    DerechaDerecha();
                    break;
                }
                break;
            case 0: //No crece el arbol ya esta equilibrado
                grow = false;
                break;
            case 1: //Si que crece pero no esta desequilibrado
                grow = true;
                break;
            }
        }
        else if (growIz)
        {

            raiz->fe--; //Decrementamos su factor de equilibrio
            switch (raiz->fe)
            {
            case -2: //Se ha desequilibrado el arobol entonces
                grow = false;
                switch (raiz->iz.raiz->fe)
                {
                case -1:
                    IzquierdaIzquierda(); //Si cuelga desde la izquierda rotamos 
                    break;
                case 1:
                    IzquierdaDerecha();//Si es desde la derecha rotamos a la derecha
                    break;
                }
                break;
            case 0:
                grow = false;
                break;
            case -1:
                grow = true;
                break;
            }
        }
        else
        {
            grow = false;
        }
    }

    return ins;
}

/**
 * @brief Reordenación del arbol mediante nodo auxiliar
 * 
 */
void TAVLCalendario::DerechaDerecha()
{
    TNodoAVL *nodoAux;

    nodoAux = raiz;
    raiz = nodoAux->de.raiz;
    nodoAux->de.raiz = raiz->iz.raiz;
    raiz->iz.raiz = nodoAux;

    if (raiz->fe != 0)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
    }
    else //DerechaDerecha para el borrado de nodos
    {
        raiz->fe = -1;
        raiz->iz.raiz->fe = 1;
    }
}

/**
 * @brief Reordenación del arbol desde la derecha hacia la izquierda
 * 
 */
void TAVLCalendario::DerechaIzquierda()
{
    TNodoAVL *auxNodoRaiz;
    TNodoAVL *auxIzquierdo;
    TNodoAVL *auxDerecho;
    //Asignamos nuestros nodos auxiliare para poder moverlos más adelante
    auxNodoRaiz = raiz;
    raiz = raiz->de.raiz->iz.raiz;
    auxIzquierdo = raiz->iz.raiz;
    auxDerecho = raiz->de.raiz;

    raiz->de.raiz = auxNodoRaiz->de.raiz;
    raiz->iz.raiz = auxNodoRaiz;
    auxNodoRaiz->de.raiz = auxIzquierdo;
    raiz->de.raiz->iz.raiz = auxDerecho;
    //Comprobamos los factores de equilibrio miramoz la rotación que debemos hacer de los nodos

    //Reorganizamos los factores de equilibrio
    if (raiz->fe == 0)
        raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
    else if (raiz->fe == -1)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
        raiz->de.raiz->fe = 1;
    }
    else
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = -1;
        raiz->de.raiz->fe = 0;
    }
}

/**
 * @brief Reordenación del subarbol izquierda hacia izquierda
 * 
 */
void TAVLCalendario::IzquierdaIzquierda()
{
    TNodoAVL *auxNodoRaiz;

    auxNodoRaiz = raiz;
    raiz = auxNodoRaiz->iz.raiz;
    auxNodoRaiz->iz.raiz = raiz->de.raiz;
    raiz->de.raiz = auxNodoRaiz;
    if (raiz->fe != 0)
    {
        raiz->fe = 0;
        raiz->de.raiz->fe = 0;
    }
    else
    {
        raiz->fe = 1;
        raiz->de.raiz->fe = -1;
    }
}

/**
 * @brief Reordenación del arbol de izquierda a derecha
 * 
 */
void TAVLCalendario::IzquierdaDerecha()
{
    TNodoAVL *auxNodoRaiz;
    TNodoAVL *auxIzquierdo;
    TNodoAVL *auxDerecho;
    //Asignamos nuestros nodos auxiliare para poder moverlos más adelante
    auxNodoRaiz = raiz;
    raiz = raiz->iz.raiz->de.raiz;
    auxIzquierdo = raiz->iz.raiz;
    auxDerecho = raiz->de.raiz;

    raiz->iz.raiz = auxNodoRaiz->iz.raiz;
    raiz->de.raiz = auxNodoRaiz;
    auxNodoRaiz->iz.raiz = auxDerecho;
    raiz->iz.raiz->de.raiz = auxIzquierdo;
    //Comprobamos los factores de equilibrio miramoz la rotación que debemos hacer de los nodos

    //Reorganizamos los factores de equilibrio
    if (raiz->fe == 0)
        raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
    else if (raiz->fe == -1)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
        raiz->de.raiz->fe = 1;
    }
    else
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = -1;
        raiz->de.raiz->fe = 0;
    }
}

/**
 * @brief Contador de la cantidad de nodos que tiene el arbol
 * Es el mismo para los arboles binarios
 * 
 * @return int 
 */
int TAVLCalendario::Nodos() const
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
 * @brief Contador de todos los nodos que son hoja
 * es el mismo para los arboles binarios
 * @return int 
 */
int TAVLCalendario::NodosHoja() const
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
 * @brief Altura del arbol AVL es la misma para los arboles binarios
 * 
 * @return int 
 */
int TAVLCalendario::Altura() const
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
 * @brief Realiza el algoritmo inorden la igual que en arbol binario
 * 
 * @return TVectorCalendario 
 */
TVectorCalendario TAVLCalendario::Inorden() const
{
    int pos;
    //Inicializamos el vector con la cantidad de nodos que tenemos
    TVectorCalendario vec(Nodos());
    pos = 1;              //Inicializamos la posicion
    InordenAux(vec, pos); //Se realiza el inorden
    return vec;
}

// AUXILIAR: devuelve el recorrido en INORDEN
void TAVLCalendario::InordenAux(TVectorCalendario &vec, int &pos) const
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
 * @brief Algoritmo de Preorden igual que en arboles binarios
 * 
 * @return TVectorCalendario 
 */
TVectorCalendario TAVLCalendario::Preorden() const
{
    int pos;
    //Inicializamos el vector con la cantidad de nodos que tenemos
    TVectorCalendario vec(Nodos());
    pos = 1;               //Inicializamos la posicion
    PreordenAux(vec, pos); //Se realiza el inorden
    return vec;
}

// AUXILIAR: devuelve el recorrido en Preorden RZ IZ DE
void TAVLCalendario::PreordenAux(TVectorCalendario &vec, int &pos) const
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
 * @brief Algoritmo PostOrden igual que en arboles binarios
 * 
 * @return TVectorCalendario 
 */
TVectorCalendario TAVLCalendario::Postorden() const
{
    int pos;
    pos = 1;
    TVectorCalendario vec(Nodos());
    PostordenAux(vec, pos);
    return vec;
}

// AUXILIAR: devuelve el recorrido en Postorden IZ DE RZ
void TAVLCalendario::PostordenAux(TVectorCalendario &vec, int &pos) const
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
 * @brief Operador comparación de arboles AVL, compara sus recorridos inorden
 * 
 * @param arbolBinario 
 * @return true 
 * @return false 
 */
bool TAVLCalendario::operator==(const TAVLCalendario &arbolBinario) const
{
    if (Inorden() == arbolBinario.Inorden())
        return true;
    else
        return false;
}

/**
 * @brief Operador != compara los recorridos inorden
 * 
 * @param arbolAVL 
 * @return true 
 * @return false 
 */
bool TAVLCalendario::operator!=(const TAVLCalendario &arbolAVL) const
{
    return Inorden() != arbolAVL.Inorden();
}

/**
 * @brief Devuelve la raiz del arbol
 * 
 * @return TCalendario 
 */
TCalendario TAVLCalendario::Raiz() const
{
    return raiz->item;
}

/**
 * @brief Comprueba si el arbol esta vacio solo mirando la raiz
 * 
 * @return true 
 * @return false 
 */
bool TAVLCalendario::EsVacio()
{
    if (raiz == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Busqueda de un TCalendario en el arbol igual que en los arboles binarios
 * 
 * @param buscado 
 * @return true 
 * @return false 
 */
bool TAVLCalendario::Buscar(const TCalendario &buscado) const
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
 * @brief Metodo de borrado "auxiliar" ya que es el principal todo se realiza en 
 * la sobrecarga
 * 
 * @param cale 
 * @return true 
 * @return false 
 */
bool TAVLCalendario::Borrar(const TCalendario &cale)
{
    bool decrece = false;
    return Borrar(cale, decrece);
}

bool TAVLCalendario::Borrar(const TCalendario &borrador, bool &decrece)
{
    bool eliminado = false;
    bool decreIzquierda = false;
    bool decreDerecha = false;
    TCalendario biggerThan;
    TNodoAVL *pibot;

    if (raiz != NULL)
    {
        if (borrador < raiz->item)
            eliminado = raiz->iz.Borrar(borrador, decreIzquierda); //Si el elemento es menor vamos a la izquerda
        else
        {
            if (borrador > raiz->item)
                eliminado = raiz->de.Borrar(borrador, decreDerecha); //Si el elemento es mayor vamos a la derecha
            else if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
            {
                delete raiz;
                raiz = NULL;
                decrece = true;
                eliminado = true;
            }
            else if (raiz->iz.raiz != NULL && raiz->de.raiz == NULL)
            {
                eliminado = true;
                pibot = raiz;
                raiz = raiz->iz.raiz;
                pibot->iz.raiz = NULL;
                delete pibot;
                decrece = true;
            }
            else if (raiz->iz.raiz == NULL && raiz->de.raiz != NULL)
            {
                eliminado = true;
                pibot = raiz;
                raiz = raiz->de.raiz;
                pibot->de.raiz = NULL;
                delete pibot;
                decrece = true;
            }
            else
            {
                eliminado = true;
                biggerThan = raiz->iz.TCalMax();
                raiz->item = biggerThan;
                raiz->iz.Borrar(biggerThan, decreIzquierda);
            }
        }
        //Hasta aqui es igual que en el borrado de los arboles binarios
        //Ahora procemos a reorganizar el arbol igual que en el insertado
        if (decreIzquierda)
        {
            raiz->fe++;
            switch (raiz->fe)
            {
            case 0:
                decrece = true;
                break;
            case 1:
                decrece = false;
                break;
            case 2:
                switch (raiz->de.raiz->fe)
                {
                case 0:
                    DerechaDerecha();
                    decrece = false;
                    break;
                case 1:
                    DerechaDerecha();
                    decrece = true;
                    break;
                case -1:
                    DerechaIzquierda();
                    decrece = true;
                    break;
                }
            }
        }
        else if (decreDerecha)
        {
            raiz->fe--;
            switch (raiz->fe)
            {
            case 0:
                decrece = true;
                break;
            case -1:
                decrece = false;
                break;
            case -2:
                switch (raiz->iz.raiz->fe)
                {
                case 0:
                    IzquierdaIzquierda();
                    decrece = false;
                    break;
                case -1:
                    IzquierdaIzquierda();
                    decrece = true;
                    break;
                case 1:
                    IzquierdaDerecha();
                    decrece = true;
                    break;
                }
                break;
            }
        }
    }
    return eliminado;
}

/**
 * @brief Función auxiliar utilizada en Borrado para encontrar el mayor de todos
 * los TCalendario del arbol
 * 
 * @return TCalendario 
 */
TCalendario TAVLCalendario::TCalMax() const
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
 * @brief Operador salida muestra el recorrido inorden 
 * 
 * @param os 
 * @param c 
 * @return ostream& 
 */
ostream &operator<<(ostream &os, const TAVLCalendario &c)
{
    
    TVectorCalendario aux(c.Nodos());
    aux = c.Inorden();
    return os << aux;
}