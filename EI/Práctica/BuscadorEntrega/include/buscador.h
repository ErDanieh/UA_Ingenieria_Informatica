#ifndef _BUSCADOR_H_
#define _BUSCADOR_H_

#include "indexadorHash.h"
#include "math.h"
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm> 

using namespace std;

class ResultadoRI
{
    friend ostream &operator<<(ostream &, const ResultadoRI &);

public:
    bool operator<(const ResultadoRI &lhs) const;
    ResultadoRI(const double &kvSimilitud, const long int &kidDoc, const int &np);
    ResultadoRI(const ResultadoRI &);
    double VSimilitud() const { return vSimilitud; }
    long int IdDoc() const { return idDoc; }
    int NumPregunta() const { return numPregunta; }
    void setVSimilitud(const double &sim) { this->vSimilitud = sim; }
    void setIdDoc(const long int &idD) { this->idDoc = idD; }
    void setNumPregunta(const int &np) { this->numPregunta; }

private:
    double vSimilitud;
    long int idDoc;
    int numPregunta;
};

// Clase buscador hereda de IndexadorHash
class Buscador : public IndexadorHash
{
    friend class IndexadorHash;
    friend ostream &operator<<(ostream &, const Buscador &);

public:
    Buscador(const string &directorioIndexacion, const int &f);

    Buscador(const Buscador &);

    ~Buscador();

    Buscador &operator=(const Buscador &);

    int DevolverFormulaSimilitud() const;

    bool CambiarFormulaSimilitud(const int &f);

    void CambiarParametrosDFR(const double &kc);

    double DevolverParametrosDFR() const;

    void CambiarParametrosBM25(const double &kk1, const double &kb);

    void DevolverParametrosBM25(double &kk1, double &kb) const;

    bool SeleccionarMetodo(const int &numDocumentos, const int &numPregunta);

    bool Buscar(const int &numDocumentos = 99999);

    bool Buscar(const string &dirPreguntas, const int &numDocumentos, const int &numPregInicio, const int &numPregFin);
    
    void ImprimirResultadoBusqueda(const int &numDocumentos = 99999) const;
    bool ImprimirResultadoBusqueda(const int &numDocumentos, const string &nombreFichero) const;
    void realizarDFR(const int &numDocumentos, const int &numPregunta);
    void realizarBM25(const int &numDocumentos, const int &numPregunta);

private:
    Buscador();
    vector<ResultadoRI> docsOrdenados;
    int formSimilitud;
    double c;
    double k1;
    double b;

    string sacarNombreDocId(const long int &idDoc) const;
};
#endif