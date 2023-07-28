#include "../include/tvectorcalendario.h"
//Constructor por defector
TVectorCalendario::TVectorCalendario()
{
    this->c = NULL;
    this->tamano = 0;
    this->error = TCalendario();
}

//Constructor con parametros
TVectorCalendario::TVectorCalendario(int cantd)
{
    if (cantd <= 0)
    {
        this->c = NULL;
        this->tamano = 0;
    }
    else
    {

        this->tamano = cantd;
        this->c = new TCalendario[tamano]; // Cantidad de elementos del vector
    }
}

//constructor copia
TVectorCalendario::TVectorCalendario(const TVectorCalendario &v)
{
    this->~TVectorCalendario();
    //Same (*this).~TVectorCalendario();ç
    tamano = v.Tamano();
    this->c = new TCalendario[tamano];

    for (unsigned i = 0; i < tamano; i++)
    {
        this->c[i] = v[i];
    }
}
//Destructor de TVectorCalendario
TVectorCalendario::~TVectorCalendario()
{
    if (c != NULL)
    {
        delete[] c;
        c = NULL;
        tamano = 0;
    }
}

//Operador asignación de TVectorCalendario
TVectorCalendario &TVectorCalendario::operator=(const TVectorCalendario &v)
{
    if (this != &v)
    {
        if (c != NULL) //Si el vector no esta vacio lo eliminamos
        {
            delete[] c;
            c = NULL;
            tamano = 0;
        }

        if (v.tamano != 0) //si el vector pasado como parámetro no esta vacio
        {
            tamano = v.tamano; //Asignamos el tamaño
            c = new TCalendario[tamano];
            //Copiamos el vector
            for (unsigned i = 0; i < tamano; i++)
            {
                c[i] = v.c[i];
            }
        }
    }
    return *this;
}
//Para los local Value
TCalendario &TVectorCalendario::operator[](int i)
{
    if (i >= 1 && i <= tamano)
    {
        return c[i - 1];
    }
    else
    {
        return error;
    }
}

//Comprobaciones de tipo
bool TVectorCalendario::operator!=(const TVectorCalendario &co) const
{
    if (*this == co)
        return true;
    else
        return false;
}

bool TVectorCalendario::operator==(const TVectorCalendario &co) const
{
    bool equals = false;

    if (tamano == co.Tamano())
    {
        equals = true;
        for (unsigned i = 0; i < tamano && equals; i++)
        {
            if (c[i] != co.c[i])
                equals = false;
        }
    }
    return equals;
}
//Corchetes para los restValue
TCalendario TVectorCalendario::operator[](int i) const
{
    if (i >= 1 && i <= tamano)
        return c[i - 1];
    else
        return error;
}

//Devuelve el tamaño del vector
int TVectorCalendario::Tamano() const
{
    return tamano;
}

//Busca un calendario en el vector
bool TVectorCalendario::ExisteCal(TCalendario &cal) const
{
    bool esta = false;

    for (int i = 0; i < tamano && esta == false; i++)
        if (cal == c[i])
            esta = true;

    return esta;
}

//Cantidad de celdas ocupadas en el vector
int TVectorCalendario::Ocupadas() const
{
    int cantOcupadas = 0;

    for (size_t i = 0; i < tamano; i++)
        if (c[i].EsVacio() == false)
            cantOcupadas++;

    return cantOcupadas;
}

//Operador salida para los elementos del calendario
ostream &operator<<(ostream &os,const TVectorCalendario &v)
{
    int i;
    os << "[";
    for (i = 0; i < v.tamano; i++)
    {
        // en este accedo directamente al vector
        os << "(" << i + 1 << ") " << v.c[i];

        if (i != v.tamano - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

//Redimensiona el vector y elimina los restantes
bool TVectorCalendario::Redimensionar(int tam)
{
    bool done = false;
    TCalendario *aux; //auxiliar para nuevo vector

    if (tam > 0 && tam != tamano)
    {
        done = true;
        aux = new TCalendario[tam];
        //Creamos un nuevo vector y vamos copiando los elementos
        //hasta que llegamos al nuevo tamaño
        for (size_t i = 0; i < tamano && i < tam; i++) aux[i] = c[i];
        //Tenemos que borrar el vector primero
        if (c != NULL) delete[] c;
        //Después lo asignamos
        c = aux;
        tamano = tam;
        //No se queda solo en el ambito, hacer un bucle for
        //Para copiarlo de nuevo sería redundante
    }

    return done;
}

//Muestra los mensaje anteriores a la fecha pasada como parámetro
void TVectorCalendario::MostrarMensajes(int d, int m, int a) const
{
    TCalendario fine(d, m, a, NULL);
    bool elem1 = true; //Para poner o no la primera ,
    cout << "[";
    for (size_t i = 0; i < tamano; i++)
    {
        if (c[i] > fine || c[i] == fine)
        {
            if (elem1 == false) cout << ", ";

            elem1 = false;
            cout << c[i];
        }
    }
    cout << "]";
}