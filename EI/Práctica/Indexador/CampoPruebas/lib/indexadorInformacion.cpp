#include "indexadorInformacion.h"

// Constructor de la clase Fecha
Fecha::Fecha()
{
    this->dia = 0;
    this->mes = 0;
    this->anyo = 0;
    this->hora = 0;
    this->min = 0;
    this->seg = 0;
}

// Constructor parametrizado
Fecha::Fecha(struct tm *clock)
{
    this->dia = clock->tm_mday;
    this->mes = clock->tm_mon;
    this->anyo = clock->tm_year;
    this->hora = clock->tm_hour;
    this->min = clock->tm_min;
    this->seg = clock->tm_sec;
}

Fecha::Fecha(const Fecha &f)
{
    this->dia = f.dia;
    this->mes = f.mes;
    this->anyo = f.anyo;
    this->hora = f.hora;
    this->min = f.min;
    this->seg = f.seg;
}

// Operador menor que para comparar dos fechas
bool Fecha::operator<(const Fecha &f) const
{
    if (this->anyo < f.anyo)
        return true;
    else if (this->anyo > f.anyo)
        return false;
    else if (this->mes < f.mes)
        return true;
    else if (this->mes > f.mes)
        return false;
    else if (this->dia < f.dia)
        return true;
    else if (this->dia > f.dia)
        return false;
    else if (this->hora < f.hora)
        return true;
    else if (this->hora > f.hora)
        return false;
    else if (this->min < f.min)
        return true;
    else if (this->min > f.min)
        return false;
    else if (this->seg < f.seg)
        return true;
    else
        return false;
}

// Operador mayor que para comparar dos fechas
bool Fecha::operator>(const Fecha &f) const
{
    return !(*this < f);
}

// Operador igual para asignar los mismos valores de una fecha a otra
Fecha &Fecha::operator=(const Fecha &f)
{
    if (this != &f)
    {
        this->dia = f.dia;
        this->mes = f.mes;
        this->anyo = f.anyo;
        this->hora = f.hora;
        this->min = f.min;
        this->seg = f.seg;
    }
    return (*this);
}

////////////////////////////////////////////////////////////////////////////

InformacionTermino::InformacionTermino()
{
    this->ftc = 0;
}

InformacionTermino::InformacionTermino(const InformacionTermino &t)
{
    this->ftc = t.ftc;
    this->l_docs = t.l_docs;
}

InformacionTermino::~InformacionTermino()
{
    this->ftc = 0;
    this->l_docs.clear();
}

InformacionTermino &InformacionTermino::operator=(const InformacionTermino &t)
{
    if (this != &t)
    {
        this->ftc = t.ftc;
        this->l_docs = t.l_docs;
    }
    return (*this);
}

void InformacionTermino::getFtc(int &d) const
{
    d = this->ftc;
}
void InformacionTermino::setFtc(int ftc)
{
    this->ftc = ftc;
}

void InformacionTermino::insertarDoc(int &idDoc, InfTermDoc &infTermDoc)
{
    l_docs.insert({idDoc, infTermDoc});
}

InfTermDoc InformacionTermino::getInfTermDoc(int &idDoc)
{
    return this->l_docs.find(idDoc)->second;
}

void InformacionTermino::getL_docs(unordered_map<int, InfTermDoc> &d) const
{
    d = this->l_docs;
}

ostream &operator<<(ostream &os, const InformacionTermino &t)
{
    os << "Frecuencia total: " << t.ftc << "\tfd: " << t.l_docs.size();
    for (auto it = t.l_docs.begin(); it != t.l_docs.end(); ++it)
        os << "\t"
           << "Id.Doc: " << it->first << "\t" << it->second;
    return os;
}

////////////////////////////////////////////////////////////////////////////
InfTermDoc::InfTermDoc()
{
    this->ft = 0;
}

InfTermDoc::InfTermDoc(const InfTermDoc &t)
{
    this->ft = t.ft;
    this->posTerm = t.posTerm;
}

InfTermDoc::~InfTermDoc()
{
    this->ft = 0;
    this->posTerm.clear();
}

InfTermDoc &InfTermDoc::operator=(const InfTermDoc &t)
{
    if (this != &t)
    {
        this->~InfTermDoc();
        this->ft = t.ft;
        this->posTerm = t.posTerm;
    }
    return (*this);
}

void InfTermDoc::getFt(int &d) const
{
    d = this->ft;
}

void InfTermDoc::getPosTerm(list<int> &p) const
{
    p = this->posTerm;
}

void InfTermDoc::setFt(int ft)
{
    this->ft = ft;
}

void InfTermDoc::setPosTerm(int &posTerm)
{
    this->posTerm.push_back(posTerm);
}

ostream &operator<<(ostream &os, const InfTermDoc &t)
{
    os << "ft: " << t.ft << "\t";
    for (auto it = t.posTerm.begin(); it != t.posTerm.end(); ++it)
    {
        if (it == t.posTerm.begin())
        {
            os << *it;
        }
        else
        {
            os << "\t" << *it;
        }
    }

    return os;
}
////////////////////////////////////////////////////////////////////////////
// Constructor InfDoc
InfDoc::InfDoc() : fechaModificacion(),
                   idDoc(0),
                   numPal(0),
                   numPalSinParada(0),
                   numPalDiferentes(0),
                   tamBytes(0)
{
}

InfDoc::InfDoc(const InfDoc &d)
{
    this->idDoc = d.idDoc;
    this->numPal = d.numPal;
    this->numPalSinParada = d.numPalSinParada;
    this->numPalDiferentes = d.numPalDiferentes;
    this->tamBytes = d.tamBytes;
    this->fechaModificacion = d.fechaModificacion;
}

InfDoc::~InfDoc()
{
    this->idDoc = 0;
    this->numPal = 0;
    this->numPalSinParada = 0;
    this->numPalDiferentes = 0;
    this->tamBytes = 0;
}

InfDoc &InfDoc::operator=(const InfDoc &d)
{
    if (this != &d)
    {
        this->idDoc = d.idDoc;
        this->numPal = d.numPal;
        this->numPalSinParada = d.numPalSinParada;
        this->numPalDiferentes = d.numPalDiferentes;
        this->tamBytes = d.tamBytes;
        this->fechaModificacion = d.fechaModificacion;
    }
    return (*this);
}

void InfDoc::getIdDoc(int &id) const
{
    id = this->idDoc;
    // return this->idDoc;
}

void InfDoc::getNumPal(int &numPal) const
{
    numPal = this->numPal;
}

void InfDoc::getNumPalSinParada(int &d) const
{
    d = this->numPalSinParada;
}

void InfDoc::getNumPalDiferentes(int &d) const
{
    d = this->numPalDiferentes;
}

void InfDoc::getTamBytes(int &t) const
{
    t = this->tamBytes;
}

Fecha InfDoc::getFechaModificacion() const
{
    return this->fechaModificacion;
}

void InfDoc::setIdDoc(int idDoc)
{
    this->idDoc = idDoc;
}

void InfDoc::setNumPal(int numPal)
{
    this->numPal = numPal;
}

void InfDoc::setNumPalSinParada(int numPalSinParada)
{
    this->numPalSinParada = numPalSinParada;
}

void InfDoc::setNumPalDiferentes(int numPalDiferentes)
{
    this->numPalDiferentes = numPalDiferentes;
}

void InfDoc::setTamBytes(int tamBytes)
{
    this->tamBytes = tamBytes;
}

void InfDoc::setFechaModificacion(Fecha fechaModificacion)
{
    this->fechaModificacion = fechaModificacion;
}

ostream &operator<<(ostream &os, const InfDoc &d)
{
    os << "idDoc: " << d.idDoc << "\tnumPal: " << d.numPal
       << "\tnumPalSinParada: " << d.numPalSinParada
       << "\tnumPalDiferentes: " << d.numPalDiferentes
       << "\ttamBytes: " << d.tamBytes;
    return os;
}

////////////////////////////////////////////////////////////////////////////
// Constructor InfColeccionDocs
InfColeccionDocs::InfColeccionDocs()
{
    this->numDocs = 0;
    this->numTotalPal = 0;
    this->numTotalPalSinParada = 0;
    this->numTotalPalDiferentes = 0;
    this->tamBytes = 0;
}

InfColeccionDocs::InfColeccionDocs(const InfColeccionDocs &c)
{
    this->numDocs = c.numDocs;
    this->numTotalPal = c.numTotalPal;
    this->numTotalPalSinParada = c.numTotalPalSinParada;
    this->numTotalPalDiferentes = c.numTotalPalDiferentes;
    this->tamBytes = c.tamBytes;
}

InfColeccionDocs::~InfColeccionDocs()
{
    this->numDocs = 0;
    this->numTotalPal = 0;
    this->numTotalPalSinParada = 0;
    this->numTotalPalDiferentes = 0;
    this->tamBytes = 0;
}

InfColeccionDocs &InfColeccionDocs::operator=(const InfColeccionDocs &c)
{
    if (this != &c)
    {
        this->numDocs = c.numDocs;
        this->numTotalPal = c.numTotalPal;
        this->numTotalPalSinParada = c.numTotalPalSinParada;
        this->numTotalPalDiferentes = c.numTotalPalDiferentes;
        this->tamBytes = c.tamBytes;
    }
    return (*this);
}

int InfColeccionDocs::getNumDocs() const
{
    return this->numDocs;
}

int InfColeccionDocs::getNumTotalPal() const
{
    return this->numTotalPal;
}

int InfColeccionDocs::getNumTotalPalSinParada() const
{
    return this->numTotalPalSinParada;
}

int InfColeccionDocs::getNumTotalPalDiferentes() const
{
    return this->numTotalPalDiferentes;
}

int InfColeccionDocs::getTamBytes() const
{
    return this->tamBytes;
}

void InfColeccionDocs::setNumDocs(int numDocs)
{
    this->numDocs = numDocs;
}

void InfColeccionDocs::setNumTotalPal(int numTotalPal)
{
    this->numTotalPal = numTotalPal;
}

void InfColeccionDocs::setNumTotalPalSinParada(int numTotalPalSinParada)
{
    this->numTotalPalSinParada = numTotalPalSinParada;
}

void InfColeccionDocs::setNumTotalPalDiferentes(int numTotalPalDiferentes)
{
    this->numTotalPalDiferentes = numTotalPalDiferentes;
}

void InfColeccionDocs::setTamBytes(int tamBytes)
{
    this->tamBytes = tamBytes;
}

ostream &operator<<(ostream &os, const InfColeccionDocs &p)
{
    os << "numDocs: " << p.numDocs << "\tnumTotalPal: " << p.numTotalPal << "\tnumTotalPalSinParada: " << p.numTotalPalSinParada << "\tnumTotalPalDiferentes: " << p.numTotalPalDiferentes << "\ttamBytes: " << p.tamBytes;
    return os;
}

////////////////////////////////////////////////////////////////////////////
// Constructor InformacionTerminoPregunta
InformacionTerminoPregunta::InformacionTerminoPregunta()
{
    this->ft = 0;
}

InformacionTerminoPregunta::InformacionTerminoPregunta(const InformacionTerminoPregunta &t)
{
    this->ft = t.ft;
    this->posTerm = t.posTerm;
}

InformacionTerminoPregunta::~InformacionTerminoPregunta()
{
    this->ft = 0;
    this->posTerm.clear();
}

InformacionTerminoPregunta &InformacionTerminoPregunta::operator=(const InformacionTerminoPregunta &t)
{
    if (this != &t)
    {
        this->ft = t.ft;
        this->posTerm = t.posTerm;
    }
    return (*this);
}

int InformacionTerminoPregunta::getFt() const
{
    return this->ft;
}

list<int> InformacionTerminoPregunta::getPosTerm() const
{
    return this->posTerm;
}

void InformacionTerminoPregunta::setFt(int ft)
{
    this->ft = ft;
}

void InformacionTerminoPregunta::setPosTerm(int posTerm)
{
    this->posTerm.push_back(posTerm);
}

ostream &operator<<(ostream &os, const InformacionTerminoPregunta &t)
{
    os << "ft: " << t.ft;
    for (auto it = t.posTerm.begin(); it != t.posTerm.end(); ++it)
        os << "\t" << *it;
    return os;
}

////////////////////////////////////////////////////////////////////////////

// Constructor de informacionPregunta
InformacionPregunta::InformacionPregunta()
{
    this->numTotalPal = 0;
    this->numTotalPalSinParada = 0;
    this->numTotalPalDiferentes = 0;
}

// Constructor copia
InformacionPregunta::InformacionPregunta(const InformacionPregunta &p)
{
    this->numTotalPal = p.numTotalPal;
    this->numTotalPalSinParada = p.numTotalPalSinParada;
    this->numTotalPalDiferentes = p.numTotalPalDiferentes;
}

// Destructor de informacionPregunta
InformacionPregunta::~InformacionPregunta()
{
    this->numTotalPal = 0;
    this->numTotalPalDiferentes = 0;
    this->numTotalPalSinParada = 0;
}

// Operador igual para asignar los mismos valores de una informacionPregunta a otra
InformacionPregunta &InformacionPregunta::operator=(const InformacionPregunta &p)
{
    if (this != &p)
    {
        this->numTotalPal = p.numTotalPal;
        this->numTotalPalSinParada = p.numTotalPalSinParada;
        this->numTotalPalDiferentes = p.numTotalPalDiferentes;
    }
    return (*this);
}

int InformacionPregunta::getNumTotalPal() const
{
    return this->numTotalPal;
}

int InformacionPregunta::getNumTotalPalSinParada() const
{
    return this->numTotalPalSinParada;
}

int InformacionPregunta::getNumTotalPalDiferentes() const
{
    return this->numTotalPalDiferentes;
}

void InformacionPregunta::setNumTotalPal(int numTotalPal)
{
    this->numTotalPal = numTotalPal;
}

void InformacionPregunta::setNumTotalPalSinParada(int numTotalPalSinParada)
{
    this->numTotalPalSinParada = numTotalPalSinParada;
}

void InformacionPregunta::setNumTotalPalDiferentes(int numTotalPalDiferentes)
{
    this->numTotalPalDiferentes = numTotalPalDiferentes;
}

// Operador salida
ostream &operator<<(ostream &os, const InformacionPregunta &p)
{
    os << "numTotalPal: " << p.numTotalPal << "\tnumTotalPalSinParada: " << p.numTotalPalSinParada << "\tnumTotalPalDiferentes: " << p.numTotalPalDiferentes;
    return os;
}
////////////////////////////////////////////////////////////////////////////
