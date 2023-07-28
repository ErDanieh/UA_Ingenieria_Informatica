#include <iostream>
#include <cstring>
#include "../include/tcalendario.h"

//Meses con 30 días
#define abril 4
#define junio 6
#define septiembre 9
#define noviembre 11
//meses con 31 días
#define enero 1
#define marzo 3
#define mayo 5
#define julio 7
#define agosto 8
#define octubre 10
#define diciembre 12
//meses con 28 dias
#define febrero 2

using namespace std;

bool TCalendario::esBisiesto(int a)
{
    if (a % 4 == 0 && a % 100 != 0 || a % 400 == 0)
    {
        return true;
    }
    return false;
}

bool TCalendario::FechaCorrecta(int d, int m, int a)
{
    //Comprobamos si los numeros son menores a las bases
    if (d < 0 || d > 31 || m < 1 || m > 12 || a < 1900)
    {
        return false;
    }
    else
    {
        if (m != febrero)
        {
            if (m == abril || m == junio || m == septiembre || m == noviembre)
            {
                if (d > 30)
                {
                    return false;
                }
            }
            else
            {
                if (d > 31)
                {
                    return false;
                }
            }
        }
        else
        {
            if (esBisiesto(a) == true)
            {
                if (d > 29)
                {
                    return false;
                }
            }
            else
            {
                if (d > 28)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

TCalendario::TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

//Apunte: strdup asigna memoria para la nueva cadena en el montón,
//durante el uso de strcpy (o su seguro strncpy varient) puedo copiar
// una cadena a una memoria pre asignado ya sea el montón o la pila.

TCalendario::TCalendario(int dia, int mes, int anyo,const char *mens)
{
    if (FechaCorrecta(dia, mes, anyo) == true)
    {
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;

        if (mens != NULL)
        {
            mensaje = new char[strlen(mens) + 1];
            strcpy(mensaje, mens);
        }
        else
        {
            mensaje = NULL;
        }
    }
    else
    {
        this->dia = 1;
        this->mes = enero;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
}

TCalendario::TCalendario(const TCalendario &c)
{
    dia = c.dia;
    mes = c.mes;
    anyo = c.anyo;

    if (c.mensaje != NULL)
    {
        //strdup duplica la cadena del mensaje pasado como parámetro
        mensaje = strdup(c.mensaje);
    }
    else
    {
        mensaje = NULL;
    }
}

TCalendario::~TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1900;
    if (mensaje != NULL)
    {
        delete[] mensaje;
        mensaje = NULL;
    }
}

// & : devuelve *this
TCalendario &TCalendario::operator=(const TCalendario &cal)
{
    if (this != &cal)
    {
        dia = cal.dia;
        mes = cal.mes;
        anyo = cal.anyo;

        //si this mensaje no esta vacio lo vaciamos
        if (mensaje != NULL)
        {
            delete[] mensaje;
            mensaje = NULL;
        }

        if (cal.mensaje != NULL)
            mensaje = strdup(cal.mensaje);
    }

    return *this;
}

int TCalendario::Dia() const
{
    return dia;
}

int TCalendario::Mes() const
{
    return mes;
}

int TCalendario::Anyo() const
{
    return anyo;
}

char *TCalendario::Mensaje() const
{
    return mensaje;
}

bool TCalendario::operator==(const TCalendario &cal) const
{
    bool iguales = false;
    if (dia == cal.dia && mes == cal.mes && anyo == cal.anyo)
    {
        if((cal.mensaje != NULL && mensaje == NULL) || (cal.mensaje == NULL && mensaje != NULL))
            return false;

        if (mensaje == NULL && cal.mensaje == NULL)
            return true;
        else
        {
            if (mensaje != NULL && cal.mensaje != NULL)
                if (strcmp(mensaje, cal.mensaje) == 0)
                    iguales = true;
        }
    }
    return iguales;
}

bool TCalendario::operator!=(const TCalendario &cal) const
{
    //Esta función comprueba el tipo al ser this de tipo TCalendario
    return !(*this == cal);
}

bool TCalendario::operator>(const TCalendario &cal) const
{
    bool big = false;

    if (anyo > cal.anyo || anyo == cal.anyo && mes > cal.mes || anyo == cal.anyo && mes == cal.mes && dia > cal.dia)
    {
        return true;
    }
    else
    {
        //Si el que pasamos como parámetro tiene mensaje es mayor
        if (anyo == cal.anyo && mes == cal.mes && dia == cal.dia)
        {
            if (mensaje != NULL && cal.mensaje == NULL)
                return true;
            else
            {
                if (mensaje != NULL && cal.mensaje != NULL)
                    if (strcmp(mensaje, cal.mensaje) > 0)
                        return true;
            }
        }
    }
    return big;
}

bool TCalendario::operator<(const TCalendario &cal) const
{
    return !(*this > cal) && !(*this == cal);
}

TCalendario TCalendario::operator++(int diasIncrementados)
{
    TCalendario copiado(*this); // guardo el antiguo
    ++(*this);
    return copiado;
}

TCalendario &TCalendario::operator++()
{
    //Incrementamos el día
    dia++;
    if (dia == 32) //Nos pasamos de mes
    {
        mes++;
        dia = 1;
        if (mes == 13)
        {
            mes = enero;
            anyo++;
        }
    }

    if (dia == 31 && (mes == abril || mes == junio || mes == septiembre || mes == noviembre))
    {
        mes++;
        dia = 1;
    }
    //Caso especial para febrero
    if (mes == febrero)
    {
        if (esBisiesto(anyo) == true)
        {
            if (dia == 30)
            {
                mes = marzo;
                dia = 1;
            }
        }
        else
        {
            if (dia == 29)
            {
                mes = marzo;
                dia = 1;
            }
        }
    }

    return *this;
}

TCalendario TCalendario::operator+(int dias) const
{
    TCalendario fecha;
    fecha.dia = dia;
    fecha.mes = mes;
    fecha.anyo = anyo;
    fecha.ModMensaje(mensaje);

    for (unsigned i = 1; i <= dias; i++)
    {
        fecha++;
    }
    return fecha;
}

ostream &operator<<(ostream &os, const TCalendario &c)
{
    if (c.dia < 10)
    {
        os << "0" << c.dia << "/";
    }
    else
    {
        os << c.dia << "/";
    }

    if (c.mes < 10)
    {
        os << "0" << c.mes << "/";
    }
    else
    {
        os << c.mes << "/";
    }
    os << c.anyo << " ";
    os << '"';
    if (c.mensaje != NULL)
    {
        os << c.mensaje;
    }
    os << '"';

    return os;
}

TCalendario &TCalendario::operator--()
{

    int vecdias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //si la fecha es la default solo elimiar el mensaje y no decrementarla
    if (dia == 1 && mes == 1 && anyo == 1900)
    {
        if (mensaje != NULL)
        {
            delete[] mensaje;
            mensaje = NULL;
        }
    }
    else
    {
        dia--;
        if (dia == 0)
        {
            mes--;
            if (mes == 0)
            {
                anyo--;
                mes = 12;
            }
            if (mes == 2)
            {
                if (!esBisiesto(anyo))
                {
                    dia = 28;
                }
                else
                {
                    dia = 29;
                }
            }
            else
            {
                dia = vecdias[mes - 1];
            }
        }
    }
    return *this;
}

TCalendario TCalendario::operator--(int x)
{
    TCalendario fechaCopiada(*this);
    --(*this);
    return fechaCopiada;
}

TCalendario TCalendario::operator-(int dias) const
{
    TCalendario fecha(*this);
    for (int i = 1; i <= dias; i++)
    {
        fecha--;
    }
    return fecha;
}

bool TCalendario::ModMensaje(char *msg)
{

    //Eliminamos el mensaje
    if (mensaje != NULL)
    {
        delete[] mensaje;
        mensaje = NULL;
    }
    //Copiamos el mensaje
    if (msg != NULL)
    {
        mensaje = new char[strlen(msg) + 1];
        strcpy(mensaje, msg);
    }

    if (!mensaje)
    {
        return false;
    }

    return true;
}

bool TCalendario::ModFecha(int d, int m, int a)
{
    if (FechaCorrecta(d, m, a) == true)
    { //Solo modificamos si la fecha es correcta;
        dia = d;
        mes = m;
        anyo = a;
        return true;
    }
    else
    {
        return false;
    }
}

bool TCalendario::EsVacio() const
{
    return (dia == 1 && mes == 1 && anyo == 1900 && mensaje == NULL);
}
