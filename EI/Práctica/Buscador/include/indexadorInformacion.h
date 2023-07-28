#ifndef _INDEXADORINFORMACION_H_
#define _INDEXADORINFORMACION_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

#include <tr1/unordered_map>
#include <tr1/unordered_set>

using namespace std;
///////////////////////////////////////////////////////////////////////////////
/**
 * @class InfTermDoc
 * @brief Esta clase almacena la informacion de los terminos dentro de un documento
 */
class InfTermDoc
{
    friend class Buscador;
    // Operador salida
    friend ostream &operator<<(ostream &s, const InfTermDoc &p);

public:
    // Constructor copia de informacionTermino
    InfTermDoc(const InfTermDoc &);
    // Constructor de informacionTermino
    InfTermDoc(); // Inicializa ft = 0
    // Destructor de informacionTermino
    ~InfTermDoc(); // Pone ft = 0

    InfTermDoc(const int &frec, const int &pos);

    // Operador igual para asignar los mismos valores de una informacionTermino a otra
    InfTermDoc &operator=(const InfTermDoc &);
    // Getters
    void getFt(int &) const;
    void getPosTerm(list<int> &) const;
    // Setters
    void setFt(const int &);
    void setPosTerm(int &);

private:
    // Frecuencia del termino en el documento
    int ft;

    /**
    Lista de numeros de palabra en los que aparece el termino en el
    documento. Los numeros de palabra comenzaran desde cero (la primera
    palabra del documento). Se numeraran las palabras de parada. Estara
    ordenada de menor a mayor posicion.
    Solo activo cuando almacenarPosTerm == true
    **/
    list<int> posTerm;
};
/////////////////////////////////////////////////////////////////////////////////////////
class InformacionTermino
{
    friend ostream &operator<<(ostream &s, const InformacionTermino &p);

public:
    // Constructor copia de informacionTermino
    InformacionTermino(const InformacionTermino &);
    // Constructor de informacionTermino Inicializa ftc = 0
    InformacionTermino();
    // Destructor de informacionTermino pone ftc = 0 y vaci­a l_docs
    ~InformacionTermino();

    InformacionTermino(const int &ftc, pair<int, InfTermDoc> &);
    // Operador igual para asignar los mismos valores de una informacionTermino a otra
    InformacionTermino &operator=(const InformacionTermino &);

    /** Tabla Hash que se accedera por el id del documento, devolviendo un
     *  objeto de la clase InfTermDoc que contiene toda la informacion de
     *  aparicion del termino en el documento
     *  El int es el id del documento y InfTermDoc es la informacion de los terminos de cada documento
     * */

    // Getters y setters
    void getFtc(int &) const;

    void setFtc(int ftc);

    // Inserta un nuevo documento en la tabla hash segun su id
    void insertarDoc(pair<int, InfTermDoc> &);

    // Devuelve la informacion del documento pasado como parametro
    InfTermDoc getInfTermDoc(int &idDoc);

    // Devuelve la informacion de los termnos en el documento
    void getL_docs(unordered_map<int, InfTermDoc> &d) const;

    void setL_docs(const unordered_map<int, InfTermDoc> l_docs)
    {
        this->l_docs = l_docs;
    };

    void modificarDoc(const int &idDoc, int &posTerm)
    {
        l_docs[idDoc].setPosTerm(posTerm);
    };

    void incrementarFt(const int &idDoc)
    {
        int ft;
        l_docs[idDoc].getFt(ft);
        l_docs[idDoc].setFt(ft + 1);
    };

    void imprimirL_docs()
    {
        for (auto it = l_docs.begin(); it != l_docs.end(); ++it)
        {
            cout << it->second;
        }
    };

    bool existeDocu(const int &idDoc) const
    {
        return l_docs.find(idDoc) != l_docs.end();
    };

    int getFtDoc(const int &idDoc)
    {
        int ft = 0;
        if (existeDocu(idDoc))
        {
            l_docs[idDoc].getFt(ft);
            return ft;
        }
        
    };

    int sizeL_docs()
    {
        return l_docs.size();
    };

private:
    // Frecuencia total del termino en la coleccion
    int ftc;
    unordered_map<int, InfTermDoc> l_docs;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Esta es mi implementacion de las fechas para los archivos,
 * utilizaremos la estructura del clock para obtener los datos
 * de la fecha y hora
 */
class Fecha
{

public:
    Fecha();
    Fecha(struct tm *clock);
    Fecha(const Fecha &);
    bool operator<(const Fecha &f) const;
    bool operator>(const Fecha &f) const;
    Fecha &operator=(const Fecha &f);
    int dia;
    int mes;
    int anyo;
    int hora;
    int min;
    int seg;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @class InfDoc
 * @brief Esta clase almacena la informacion de los documentos
 */
class InfDoc
{
    friend class Buscador;
    friend ostream &operator<<(ostream &s, const InfDoc &p);

public:
    // Constructor copia de informacionDocumento
    InfDoc(const InfDoc &);
    // Constructor de informacionDocumento
    InfDoc();
    // Destructor de informacionDocumento
    ~InfDoc();
    // Operador igual para asignar los mismos valores de una informacionDocumento a otra
    InfDoc &operator=(const InfDoc &);

    // Getters
    void getIdDoc(int &) const;
    void getNumPal(int &) const;
    void getNumPalSinParada(int &) const;
    void getNumPalDiferentes(int &) const;
    void getTamBytes(int &) const;
    Fecha getFechaModificacion() const;

    // Setters
    void setIdDoc(int idDoc);
    void setNumPal(int numPal);
    void setNumPalSinParada(int numPalSinParada);
    void setNumPalDiferentes(int numPalDiferentes);
    void setTamBytes(int tamBytes);
    void setFechaModificacion(Fecha fechaModificacion);

private:
    // Identificador del documento. Empieza por el 1
    int idDoc;

    // Numero total de palabras del documento
    int numPal;

    // Numero total de palabras sin stop-words del documento
    int numPalSinParada;

    /** Numero total de palabras diferentes que no sean stop-words (sin acumular
    la frecuencia de cada una de ellas) */
    int numPalDiferentes;

    // Tamano en bytes del documento
    int tamBytes;

    /** Atributo correspondiente a la fecha y hora de modificacion del
    documento*/
    Fecha fechaModificacion;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InfColeccionDocs
{
    friend class Buscador;
    friend ostream &operator<<(ostream &s, const InfColeccionDocs &p);

public:
    // Constructor copia de informacionColeccionDocs
    InfColeccionDocs(const InfColeccionDocs &);
    // Constructor de informacionColeccionDocs
    InfColeccionDocs();
    // Destructor de informacionColeccionDocs
    ~InfColeccionDocs();
    // Operador igual para asignar los mismos valores de una informacionColeccionDocs a otra
    InfColeccionDocs &operator=(const InfColeccionDocs &);

    // Getters
    int getNumDocs() const;
    int getNumTotalPal() const;
    int getNumTotalPalSinParada() const;
    int getNumTotalPalDiferentes() const;
    int getTamBytes() const;

    // Setters
    void setNumDocs(int numDocs);
    void setNumTotalPal(int numTotalPal);
    void setNumTotalPalSinParada(int numTotalPalSinParada);
    void setNumTotalPalDiferentes(int numTotalPalDiferentes);
    void setTamBytes(int tamBytes);

private:
    // Numero total de documentos en la coleccion
    int numDocs;
    // Numero total de palabras en la coleccion
    int numTotalPal;
    // Numero total de palabras sin stop-words en la coleccion
    int numTotalPalSinParada;
    // Numero total de palabras diferentes en la coleccion que no sean stop-words (sin acumular la frecuencia de cada una de ella
    int numTotalPalDiferentes;
    // Tamano total en bytes de la coleccion
    int tamBytes;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InformacionTerminoPregunta
{
    friend ostream &operator<<(ostream &s, const InformacionTerminoPregunta &p);

public:
    // Constructor copia de informacionTerminoPregunta
    InformacionTerminoPregunta(const InformacionTerminoPregunta &);
    // Constructor de informacionTerminoPregunta
    InformacionTerminoPregunta();
    // Destructor de informacionTerminoPregunta
    ~InformacionTerminoPregunta();
    // Operador igual para asignar los mismos valores de una informacionTerminoPregunta a otra
    InformacionTerminoPregunta &operator=(const InformacionTerminoPregunta &);

    // Getters
    int getFt() const;
    list<int> getPosTerm() const;

    // Setters
    void setFt(int ft);
    void setPosTerm(int posTerm);

private:
    // Frecuencia total del término en la pregunta
    int ft;
    // Lista de números de palabra en los que aparece el término en la pregunta
    list<int> posTerm;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InformacionPregunta
{
    friend ostream &operator<<(ostream &s, const InformacionPregunta &p);

public:
    // Constructor copia de informacionPregunta
    InformacionPregunta(const InformacionPregunta &);
    // Constructor de informacionPregunta
    InformacionPregunta();
    // Destructor de informacionPregunta
    ~InformacionPregunta();
    // Operador igual para asignar los mismos valores de una informacionPregunta a otra
    InformacionPregunta &operator=(const InformacionPregunta &);

    // Getters y Setters
    int getNumTotalPal() const;
    int getNumTotalPalSinParada() const;
    int getNumTotalPalDiferentes() const;

    void setNumTotalPal(int numTotalPal);
    void setNumTotalPalSinParada(int numTotalPalSinParada);
    void setNumTotalPalDiferentes(int numTotalPalDiferentes);

private:
    // Numero total de palabras en la pregunta
    int numTotalPal;
    // Numero total de palabras sin stop-words en la pregunta
    int numTotalPalSinParada;
    // Numero total de palabras diferentes en la pregunta que no sean stop-words (sin acumular la frecuencia de cada una de ellas)
    int numTotalPalDiferentes;
};

#endif