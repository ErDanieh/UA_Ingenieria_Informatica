#include "../include/tlistacalendario.h"
//Constructor de TListaCalendario
TListaCalendario::TListaCalendario()
{
    primero = NULL;
}

//Constructor copia de TListaCalendario
TListaCalendario::TListaCalendario(const TListaCalendario &lista)
{
    primero = NULL;
    *this = lista;
}

//Destructor de TListaCalendario
TListaCalendario::~TListaCalendario()
{
    TNodoCalendario *puntero;
    //Reinicia el puntero a la primera posición
    puntero = primero;

    //Vamos eliminando las posiones una a una hasta
    //la que primera se nula
    while (primero)
    {
        primero = primero->siguiente;
        delete puntero;
        puntero = primero;
    }
}

//Constructor ListaPos
TListaPos::TListaPos()
{
    pos = NULL;
}

//Constructor sobrecargado ListaPos
TListaPos::TListaPos(const TListaPos &p)
{
    pos = p.pos;
}

//Destructor de ListaPos
TListaPos::~TListaPos()
{
    pos = NULL;
}

//Constructor de TNodoCalendario
TNodoCalendario::TNodoCalendario()
{
    siguiente = NULL;
}

//Constructir copia de TNodoCalendario
TNodoCalendario::TNodoCalendario(const TNodoCalendario &copia)
{
    siguiente = copia.siguiente;
    c = copia.c;
}

//Destructor de TNodoCalendario
TNodoCalendario::~TNodoCalendario()
{
    siguiente = NULL;
}

//Especifica el nodo en el que se encuentra un calendario
TNodoCalendario::TNodoCalendario(const TCalendario &c)
{
    siguiente = NULL;
    this->c = c;
}

//Sobrecarga de operador =
TListaPos &TListaPos::operator=(const TListaPos &pe)
{
    pos = pe.pos;
    return *this;
}
//sobrecarga operador ==
bool TListaPos::operator==(const TListaPos &cop) const
{
    return pos == cop.pos;
}

//sobrecarga operado !=
bool TListaPos::operator!=(const TListaPos &dif) const
{
    return pos != dif.pos;
}

//Sacamos la siguiente posicón de la lista
TListaPos TListaPos::Siguiente()
{
    TListaPos sigui;
    if (pos->siguiente != NULL)
    {
        sigui.pos = pos->siguiente;
    }
    return sigui;
}

//Comprueba si la lista es vacia
bool TListaPos::EsVacia() const
{
    return pos == NULL;
}

//Saca la primera posición de la lista
TListaPos TListaCalendario::Primera() const
{
    TListaPos prim;
    prim.pos = primero;
    return prim;
}

//Consigue la ultima posición de la lista de calendarios
TListaPos TListaCalendario::Ultima() const
{
    TListaPos ulti;

    if (primero)
    {
        ulti.pos = primero;
        while (ulti.pos->siguiente != NULL)
            ulti.pos = ulti.pos->siguiente;
    }
    return ulti;
}

TCalendario TListaCalendario::Obtener(const TListaPos &pos) const
{
    TCalendario result;
    TNodoCalendario *ptl;
    bool found;

    if (primero != NULL)
    {
        found = false;
        ptl = primero;

        while (ptl && found == false)
        {
            if (ptl == pos.pos)
                found = true;
            else
                ptl = ptl->siguiente;
        }
        //Una vez encontrado devolvemos su posición
        if (found == true)
            result = pos.pos->c;
    }
    return result;
}

//Sobrecarga de operador =
TNodoCalendario &TNodoCalendario::operator=(const TNodoCalendario &n)
{
    siguiente = n.siguiente;
    c = n.c;
    return *this;
}

//Inserta un nuevo nodo dentro de la lista de Calendario
bool TListaCalendario::Insertar(const TCalendario &c)
{
    bool insertado = false;
    bool mayor = false;
    bool encontrado = false;
    TNodoCalendario *ptl = primero;
    TNodoCalendario *pta = NULL;
    TNodoCalendario *ptn;

    while (mayor == false && encontrado == false && ptl != NULL)
    {
        if (c != ptl->c) //Si no es igual comparamos si es mayor o menor
        {
            if (c < ptl->c) //Si es mayot insertamos el nodo
            {
                mayor = true;
            }
            else
            {
                pta = ptl;
                ptl = ptl->siguiente;
            }
        }
        else
        {
            encontrado = true; //Si ya esta dentro no lo metemos
        }
    }
    //si no lo encontramos entonces si que lo insertamos
    if (encontrado == false)
    {
        insertado = true;
        //Creamos el nuevo nodo
        ptn = new TNodoCalendario(c);
        //Le adjudicamos los valores al nuevo nodo
        if (pta == NULL)
            primero = ptn;
        else
            pta->siguiente = ptn;
        //Pasamos al siguiente
        ptn->siguiente = ptl;
    }
    else
    {
        insertado = false;
    }
    return insertado;
}

TListaCalendario &TListaCalendario::operator=(const TListaCalendario &lista)
{
    TNodoCalendario *ptu, *ptn, *ptl;
    if (this != &lista)
    {
        //
        this->~TListaCalendario();
        ptl = lista.primero;
        ptu = NULL;
        primero = NULL;
        while (ptl)
        {
            ptn = new TNodoCalendario(ptl->c);
            if (primero == NULL)
            {
                primero = ptn;
            }
            else
            {
                ptu->siguiente = ptn;
            }
            ptu = ptn;
            ptl = ptl->siguiente;
            //Hay que pasar al siguiente que quiero copiar
        }
    }
    return *this;
}

bool TListaCalendario::Borrar(TCalendario &calendario)
{
    bool encontrado;
    bool mayor;
    TNodoCalendario *ptl;
    TNodoCalendario *pta;

    ptl = primero;
    mayor = false;
    encontrado = false;
    pta = NULL;
    while (ptl && encontrado == false && mayor == false)
    {
        if (ptl->c == calendario)
        {
            encontrado = true;
        }
        else
        {
            if (ptl->c > calendario)
            {
                mayor = true;
            }
            else
            {
                pta = ptl;
                ptl = ptl->siguiente;
            }
        }
    }
    if (encontrado == true)
    {
        if (ptl == primero)
            primero = primero->siguiente;
        else
            pta->siguiente = ptl->siguiente;
    }

    return encontrado;
}

bool TListaCalendario::Borrar(int dia, int mes, int anyo)
{
    bool borrado = false;
    TNodoCalendario *pta, *ptl;
    TCalendario buscado(dia, mes, anyo, NULL);

    ptl = primero;
    pta = NULL;
    while (ptl)
    {
        if (ptl->c < buscado)
        {
            borrado = true;

            if (primero == ptl)
            {
                primero = primero->siguiente;
                delete ptl;
                ptl = primero;
            }
            else
            {
                pta->siguiente = ptl->siguiente;
                delete ptl;
                ptl = pta->siguiente;
            }
        }
        else
        {
            pta = ptl;
            ptl = ptl->siguiente;
        }
    }
    return borrado;
}

bool TListaCalendario::Borrar(TListaPos &posicion)
{
    bool encontrado;
    TNodoCalendario *ptl, *pta;
    ptl = primero;
    encontrado = false;
    pta = NULL;

    while (ptl && encontrado == false)
    {
        if (ptl == posicion.pos)
        {
            encontrado = true;
        }
        else
        {
            pta = ptl;
            ptl = ptl->siguiente;
        }
    }

    if (encontrado == true)
    {
        if (ptl == primero)
            primero = primero->siguiente;
        else
            pta->siguiente = ptl->siguiente;
        posicion.pos = NULL;
    }

    return encontrado;
}

bool TListaCalendario::EsVacia() const
{
    return primero == NULL;
}

int TListaCalendario::Longitud() const
{
    int cantidad = 0;
    TNodoCalendario *ptl;
    ptl = primero;

    while (ptl)
    {
        cantidad++;
        //Vamos pasando entre los nodos hasta que
        //encontremos un nulo
        ptl = ptl->siguiente;
    }
    return cantidad;
}

//Operador de asiganción de TListaCalendario
bool TListaCalendario::operator==(const TListaCalendario &comp) const
{
    bool iguales;
    TNodoCalendario *ptlizq, *ptlder;
    ptlizq = primero;
    ptlder = comp.primero;

    while (ptlizq && ptlder && ptlizq->c == ptlder->c)
    {
        ptlizq = ptlizq->siguiente;
        ptlder = ptlder->siguiente;
    }

    if (!ptlder && !ptlizq)
        iguales = true;

    return iguales;
}

ostream &operator<<(ostream &os, const TListaCalendario &lista)
{
    TNodoCalendario *ptl;
    os << "<";
    ptl = lista.primero;
    while (ptl != NULL)
    {
        os << ptl->c;
        ptl = ptl->siguiente;

        if (ptl)
            os << " ";
    }
    os << ">";
    return os;
}

bool TListaCalendario::Buscar(const TCalendario &calendario) const
{
    bool encontrado = false;
    TNodoCalendario *ptl;

    ptl = primero;

    while (ptl && encontrado == false)
    {
        if (ptl->c == calendario)
            encontrado = true;
        else
            ptl = ptl->siguiente;
    }

    return encontrado;
}

//Sumador de sublistas de forma ordenada suma this con L2
TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, const TListaCalendario &L2, int I_L2, int F_L2)
{
    TListaCalendario sumada;
    TNodoCalendario *p = primero;
    int j = 1;

    while (p)
    {
        //Insertamos
        if (j >= I_L1 && j <= F_L1)
            sumada.Insertar(p->c);

        p = p->siguiente;
        j++;
    }
    //Volvemos a empezar a recorrer la lista
    j = 1;
    p = L2.primero;
    while (p)
    {
        //Insertamos
        if (j >= I_L2 && j <= F_L2)
            sumada.Insertar(p->c);

        p = p->siguiente;
        j++;
    }
    return sumada;
}

//Operador suma de listas
TListaCalendario TListaCalendario::operator+(const TListaCalendario &sum) const
{
    TListaCalendario sumada(*this);
    TListaPos q;
    TListaPos p;
    q = sum.Primera();

    while (q.EsVacia() == false)
    {
        if (sumada.Buscar(q.pos->c) == false)
            sumada.Insertar(q.pos->c);

        p = q;
        q = q.Siguiente();
    }

    return sumada;
}

//Operador
TListaCalendario TListaCalendario::operator-(const TListaCalendario &rest) const
{
    TListaCalendario lista;
    TNodoCalendario *ptl;

    ptl = primero;
    while (ptl)
    {
        if (!rest.Buscar(ptl->c))
        {
            lista.Insertar(ptl->c);
        }
        ptl = ptl->siguiente;
    }

    return lista;
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2)
{
    TListaCalendario ranked;
    TCalendario c;
    TNodoCalendario *pq = primero;
    int i = 1;

    while (pq)
    {
        if (i >= n1 && i <= n2)
        {
            ranked.Insertar(pq->c);
            c = pq->c;
            pq = pq->siguiente;
            Borrar(c);
            i++;
        }
        else
        {
            i++;
            pq = pq->siguiente;
        }
    }
    return ranked;
}