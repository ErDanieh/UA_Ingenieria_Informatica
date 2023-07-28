#ifndef _INDEXADORHASH_H_
#define _INDEXADORHASH_H_

// Mis librerias
#include "indexadorInformacion.h"
#include "stemmer.h"
#include "tokenizador.h"

// Librerias de c++
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <tr1/unordered_map>
#include <tr1/unordered_set>

using namespace std;

class IndexadorHash
{
    friend ostream &operator<<(ostream &s, const IndexadorHash &p);

public:
    IndexadorHash(const string &fichStopWords, const string &delimitadores,
                  const bool &detectComp, const bool &minuscSinAcentos, const string &dirIndice,
                  const int &tStemmer, const bool &almEnDisco, const bool &almPosTerm);

    IndexadorHash(const string &directorioIndexacion);

    /**
     * @brief Construtor copia
     *
     */
    IndexadorHash(const IndexadorHash &);

    /**
     * @brief Destroy the Indexador Hash object
     *
     */
    ~IndexadorHash();

    /**
     * @brief Operador igual
     */
    IndexadorHash &operator=(const IndexadorHash &);

    bool Indexar(const string &ficheroDocumentos);

    bool IndexarDirectorio(const string &dirAIndexar);

    bool GuardarIndexacion() const;

    bool RecuperarIndexacion(const string &directorioIndexacion);

    void ImprimirIndexacion() const;

    bool IndexarPregunta(const string &preg);

    /**
     * @brief Busca una pregunta indexada que contenga al menos un termino
     * que no sea palabra de parada
     *
     * @param preg pregunta que se ha encontrado
     * @return true si se encuentra una pregunta indexada
     * @return false si no se encuentra una pregunta indexada
     */
    bool DevuelvePregunta(string &preg) const;

    /**
     * @brief Se aplica stemming y las mayusculas a word y se busca en la pregunta indexada y lo devuelve en inf
     * 
     * @param word termino a buscar
     * @param inf informacion que se devuelve puede devolverse vacio
     * @return true si se encuentra el termino
     * @return false si no se encuentra el termino
     */
    bool DevuelvePregunta(const string &word, InformacionTerminoPregunta &inf) const;

    /**
     * @brief Devuelve si hay alguna pregunta indexada
     * 
     * @param inf donde se devuelve la informacion de la pregunta
     * @return true si hay alguna pregunta indexada
     * @return false si no hay ninguna pregunta indexada
     */
    bool DevuelvePregunta(InformacionPregunta &inf) const;

    void ImprimirIndexacionPregunta() const;

    void ImprimirPregunta();

    bool Devuelve(const string &word, InformacionTermino &inf) const;

    bool Devuelve(const string &word, const string &nomDoc, InfTermDoc &InfDoc) const;

    bool Existe(const string &word) const;

    bool Borra(const string &word);

    bool BorraDoc(const string &nomDoc);

    void VaciarIndiceDocs();

    void VaciarIndicePreg();

    bool Actualiza(const string &word, const InformacionTermino &inf);

    bool Inserta(const string &word, const InformacionTermino &inf);

    int NumPalIndexadas() const;

    string DevolverFichPalParada() const;

    void ListarPalParada() const;

    int NumPalParada() const;

    string DevolverDelimitadores() const;

    bool DevolverCasosEspeciales();

    bool DevolverPasarAminuscSinAcentos();

    bool DevolverAlmacenarPosTerm() const;

    string DevolverDirIndice() const;

    int DevolverTipoStemming() const;

    bool DevolverAlmEnDisco() const;

    void ListarInfColeccDocs() const;

    void ListarTerminos() const;

    bool ListarTerminos(const string &nomDoc) const;

    void ListarDocs() const;

    bool ListarDocs(const string &nomDoc) const;

    //Para cada uno de nuestros Indexadores tendremos nuestro objeto stemmer
    stemmerPorter stemmerIndexador;

private:
    /**
     * @brief Este constructor se pone en la parte privada porque no se permitirá
    crear un indexador sin inicializarlo convenientemente.
     */
    IndexadorHash();

    // Índice de términos indexados accesible por el término
    tr1::unordered_map<string, InformacionTermino> indice;

    // Índice de documentos indexados accesible por el nombre del documento
    tr1::unordered_map<string, InfDoc> indiceDocs;

    // Información recogida de la colección de documentos indexada
    InfColeccionDocs informacionColeccionDocs;

    // Pregunta indexada actualmente. Si no hay ninguna indexada, contendría el valor ""
    string pregunta;

    // Índice de términos indexados en una pregunta. Se almacenará en memoria principal
    tr1::unordered_map<string, InformacionTerminoPregunta> indicePregunta;

    // Información recogida de la pregunta indexada. Se almacenará en memoria principal
    InformacionPregunta infPregunta;

    //Tabla hash con todas las stopWords
    tr1::unordered_set<string> stopWords;

    // Nombre del fichero que contiene las palabras de parada
    string ficheroStopWords;

    Tokenizador tok;

    /** “directorioIndice” será el directorio del disco duro donde se almacenará el índice.
     * En caso que contenga la cadena vacía se creará enel directorio donde se ejecute el indexador**/
    string directorioIndice;

    int tipoStemmer;

    bool almacenarEnDisco;

    bool almacenarPosTerm;
};
#endif