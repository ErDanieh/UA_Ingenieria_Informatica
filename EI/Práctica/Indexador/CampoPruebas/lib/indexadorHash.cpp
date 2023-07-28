#include "indexadorHash.h"
#include "tokenizador.h"

ostream &operator<<(ostream &s, const IndexadorHash &p)
{
    s << "Fichero con el listado de palabras de parada: " << p.ficheroStopWords << "\n";
    s << "Tokenizador: " << p.tok << "\n";
    s << "Directorio donde se almacenara el indice generado: " << p.directorioIndice << "\n";
    s << "Stemmer utilizado: " << p.tipoStemmer << "\n";
    s << "Informacion de la coleccion indexada: " << p.informacionColeccionDocs << "\n";
    s << "Se almacenara parte del indice en disco duro: " << p.almacenarEnDisco << "\n";
    s << "Se almacenaran las posiciones de los terminos: " << p.almacenarPosTerm << "\n";
    return s;
}

// Constructor de la clase IndexadorHash que inicializa los atributos de la clase
IndexadorHash::IndexadorHash(const string &fichStopWords, const string &delimitadores,
                             const bool &detectComp, const bool &minuscSinAcentos, const string &dirIndice,
                             const int &tStemmer, const bool &almEnDisco, const bool &almPosTerm)
{
    // Asignamos el fichero que contiene las stopWords
    this->ficheroStopWords = fichStopWords;
    // Intentamos abrir el ficheor
    ifstream fichero(fichStopWords, ifstream::in);
    if (fichero.good())
    {
        // Si se ha podido abrir, leemos las stopWords
        string palabra;
        fichero >> palabra;
        while (!fichero.eof())
        {
            this->stopWords.insert(palabra);
            fichero >> palabra;
        }
        fichero.close();
    }
    else
    {
        cerr << "No se ha encontrado el fichero con StopWords"
             << "\n";
    }

    // Inicializamos los valores que va a tener nuestro tokenizador
    this->tok.DelimitadoresPalabra(delimitadores);
    this->tok.PasarAminuscSinAcentos(minuscSinAcentos);
    this->tok.CasosEspeciales(detectComp);

    // Asignamos el valor del stemmer
    this->tipoStemmer = tStemmer; // 0 sin stemmer, 1 Porter espanol, 2 Porter ingles

    this->almacenarEnDisco = almEnDisco;
    this->almacenarPosTerm = almPosTerm;

    // Si se nos pasa el directorio vacio le asignamos el directorio en el que nos encontramos
    if (dirIndice != "")
    {
        this->directorioIndice = dirIndice;
    }
    else
    {
        this->directorioIndice = get_current_dir_name();
    }
}

IndexadorHash::IndexadorHash(const string &directorioIndexacion)
{
    RecuperarIndexacion(directorioIndexacion);
}

// Constrcutor de copia
IndexadorHash::IndexadorHash(const IndexadorHash &ind)
{
    this->ficheroStopWords = ind.ficheroStopWords;
    this->stopWords = ind.stopWords;
    this->tok = ind.tok;
    this->tipoStemmer = ind.tipoStemmer;
    this->directorioIndice = ind.directorioIndice;
    this->informacionColeccionDocs = ind.informacionColeccionDocs;
    this->almacenarEnDisco = ind.almacenarEnDisco;
    this->almacenarPosTerm = ind.almacenarPosTerm;
    this->indice = ind.indice;
    this->indiceDocs = ind.indiceDocs;

    this->indicePregunta = ind.indicePregunta;
    this->infPregunta = ind.infPregunta;
    this->pregunta = ind.pregunta;
}

// Destructor de indexadorHash
IndexadorHash::~IndexadorHash()
{
    // Primero tenemos que vaciar todos los indices
    indice.clear();
    indiceDocs.clear();
    indicePregunta.clear();

    this->pregunta.clear();
    this->ficheroStopWords.clear();
    this->directorioIndice.clear();
    this->tipoStemmer = 0;
    // Ponemos el almacenarEnDisco a false y el almacenarPosTerm a false
    this->almacenarEnDisco = false;
    this->almacenarPosTerm = false;
}

IndexadorHash &IndexadorHash::operator=(const IndexadorHash &ind)
{
    if (this != &ind)
    {
        this->ficheroStopWords = ind.ficheroStopWords;
        this->stopWords = ind.stopWords;
        this->tok = ind.tok;
        this->tipoStemmer = ind.tipoStemmer;
        this->directorioIndice = ind.directorioIndice;
        this->informacionColeccionDocs = ind.informacionColeccionDocs;
        this->almacenarEnDisco = ind.almacenarEnDisco;
        this->almacenarPosTerm = ind.almacenarPosTerm;
        this->indice = ind.indice;
        this->indiceDocs = ind.indiceDocs;

        this->indicePregunta = ind.indicePregunta;
        this->infPregunta = ind.infPregunta;
        this->pregunta = ind.pregunta;
    }
    return *this;
}

bool IndexadorHash::Indexar(const string &ficheroDocumentos)
{
    // Abrimos el fichero ficheroDocumentos
    ifstream nombresDocumentos(ficheroDocumentos, ifstream::in);
    // Informacion del documento que necesito para indexar
    string documentoAnalizo, lineaAnalizo;
    bool procederIndexacion = false;
    struct stat infoDocumento;
    int idDocumentoAuxiliar;
    list<string> tokensLineaAnalizo;
    int posTermino = 0;
    int idDocumento;
    int numPal;
    int numSinParada;
    int numDiferentes;
    int frecuenciaTermino;
    int ftc;
    unordered_map<int, InfTermDoc> aux;
    int cantVueltas = 0;
    tok.TokenizarListaFicheros(ficheroDocumentos);

    // Si se ha podido abrir bien el fichero y podido leer
    if (nombresDocumentos.is_open())
    {
        ifstream documentoAnalizoFich;
        documentoAnalizo = "";
        // Cojo el nonbre de un documento
        while (nombresDocumentos >> documentoAnalizo)
        {
            // cout << "Analizando documento : " << documentoAnalizo << "\n";
            auto itIndiceDocumentos = indiceDocs.find(documentoAnalizo);
            // Reinicio los valores que necesito
            idDocumentoAuxiliar = 0;
            procederIndexacion = false;
            posTermino = 0;

            // Saco la informacion del documento
            stat(documentoAnalizo.c_str(), &infoDocumento);
            // Obtengo la fecha de modificacion del documento y la parseo a mi propia estructura
            Fecha fechaModificacionDoc(gmtime(&(infoDocumento.st_mtime)));

            // Comprobamos que el fichero no esta en el indice
            if (itIndiceDocumentos == indiceDocs.end())
            {
                // cout << "El documento no esta en el indice" << endl;
                //  Como no hemos encontrado el fichero entonces lo indexamos
                procederIndexacion = true;
            }
            else
            {
                cerr << "El documento " << documentoAnalizo << " ya esta en el indice"
                     << "\n";
                // Lo ha encontrado entonces deberemos comprobar si la fecha de modificacion es igual o menor que la que tenemos
                if (itIndiceDocumentos->second.getFechaModificacion() < fechaModificacionDoc)
                {
                    cout << "El documento " << documentoAnalizo << " se va a reindexar"
                         << "\n";
                    // Nos guardamos el id del documento que tenemos en el indice para poder asignarlo nuevamente
                    itIndiceDocumentos->second.getIdDoc(idDocumentoAuxiliar);
                    procederIndexacion = true;
                }
                // Borramos el documento del indice para poder volver a indexarlo
                if (!BorraDoc(documentoAnalizo))
                {
                    // cout << "No se ha podido borrar el documento del indice" << endl;
                    cerr << "No se ha podido borrar el documento " << documentoAnalizo << "\n";
                    return false;
                }
            }

            // Procedemos a la indexacion si lo necesitamos
            if (procederIndexacion)
            {
                // cout << documentoAnalizo << endl;
                //  Abrimos el documento que estamos analizando para leerlo
                documentoAnalizoFich.open(documentoAnalizo + ".tk", ifstream::in);

                // Si no se ha podido abrir el documento
                if (!documentoAnalizoFich.is_open())
                {
                    // Sacamos el error por pantalla si no se ha podido abrir el documento
                    this->~IndexadorHash();
                    cerr << "No se ha podido abrir el documento " << documentoAnalizo << "\n";
                    return false;
                }
                else // Si si que se puede abrir
                {
                    // cout << "he abierto el documento" << endl;

                    InfDoc informacioDocumentoAnalizo;
                    // cout << "Voy a insertar la informacion" << endl;

                    // Empezamos a meterle la informacion
                    if (idDocumentoAuxiliar != 0)
                    {
                        informacioDocumentoAnalizo.setIdDoc(idDocumentoAuxiliar);
                    }
                    else
                    {
                        informacionColeccionDocs.setNumDocs(informacionColeccionDocs.getNumDocs() + 1);
                        informacioDocumentoAnalizo.setIdDoc(informacionColeccionDocs.getNumDocs());
                    }
                    informacioDocumentoAnalizo.setTamBytes(infoDocumento.st_size);
                    informacioDocumentoAnalizo.setFechaModificacion(fechaModificacionDoc);

                    // cout << "he asignado la informacion" << endl;

                    // Leemos la linea del documento
                    while (documentoAnalizoFich >> lineaAnalizo)
                    {

                        // cout << lineaAnalizo << endl;
                        //  Sacamos los tokens de la linea
                        // tok.Tokenizar(lineaAnalizo, tokensLineaAnalizo);

                        // Asignamos la cantidad de palabras que tiene el documento
                        // informacioDocumentoAnalizo.getNumPal(numPal);
                        numPal++;
                        informacioDocumentoAnalizo.setNumPal(numPal);

                        // Para cada uno de los token que tenemos le pasamos el stemmer y sacamos su informacion

                        // Le pasamos el stemmer al token
                        stemmerIndexador.stemmer(lineaAnalizo, tipoStemmer);
                        // Buscamos en nuestras stopWords para ver si tenemos que quitarla o no

                        if (stopWords.find((lineaAnalizo)) == stopWords.end())
                        {
                            // Incrementamos el numero de palabras sin parada
                            informacioDocumentoAnalizo.getNumPalSinParada(numSinParada);
                            informacioDocumentoAnalizo.setNumPalSinParada(numSinParada + 1);

                            // Comprobamos si el termino ya esta en el indice
                            auto PalabrasIndice = indice.find(lineaAnalizo);

                            // Si el termino ya existe lo que vamos a hacer es cargar su informacion y modificarla
                            if (PalabrasIndice == indice.end())
                            {
                                // cout << " No existe en el indice" << endl;
                                // Esta la informacion que tenemos del termino en general
                                InformacionTermino informacionTermino;
                                // Esta es la informacion del termino en el documento
                                InfTermDoc informacionTerminoEnDocumento;

                                //   Incrementamos las palabras diferentes que tenemos en el documento
                                informacioDocumentoAnalizo.getNumPalDiferentes(numDiferentes);
                                informacioDocumentoAnalizo.setNumPalDiferentes(numDiferentes + 1);
                                // Incrementamos nuestra coleccion de palabras diferentes
                                informacionColeccionDocs.setNumTotalPalDiferentes(informacionColeccionDocs.getNumTotalPalDiferentes() + 1);

                                // Le asignamos la informacion inicial al termino
                                informacionTerminoEnDocumento.setFt(1);
                                informacionTerminoEnDocumento.setPosTerm(posTermino);
                                // Inicializamos la informacion global del termino
                                informacionTermino.setFtc(1);
                                informacioDocumentoAnalizo.getIdDoc(idDocumento);
                                informacionTermino.insertarDoc(idDocumento, informacionTerminoEnDocumento);

                                // Insertamos el termino en el indice
                                indice.insert({lineaAnalizo, informacionTermino});
                            }
                            else // Si el termino no existe lo que vamos a hacer es insertarlo
                            {
                                // cout << " Ya existe en el indice" << endl;
                                //   Cargamos la informacion del termino

                                PalabrasIndice->second.getL_docs(aux);
                                informacioDocumentoAnalizo.getIdDoc(idDocumento);
                                auto informacionTerminoCargado = aux.find(idDocumento);

                                // El termino existe ya en el documento por lo tanto actualizamos frencuencia y posicion
                                if (informacionTerminoCargado != aux.end())
                                {
                                    // cout << "Ya existe en el documento" << endl;
                                    // cout << "Añado el termino " << (*itTokens) << " al documento " << informacioDocumentoAnalizo.getIdDoc() << " con " << informacionTerminoCargado->second << " " << endl;

                                    informacionTerminoCargado->second.getFt(frecuenciaTermino);
                                    frecuenciaTermino++;

                                    PalabrasIndice->second.modificarDoc(idDocumento, frecuenciaTermino, posTermino);
                                }
                                else // El termino no ha aparecido el documento hasta ahora por lo tanto lo anadimos
                                {
                                    // cout << "No existe en el documento" << endl;
                                    informacioDocumentoAnalizo.getNumPalDiferentes(numDiferentes);
                                    informacioDocumentoAnalizo.setNumPalDiferentes(numDiferentes + 1);

                                    InfTermDoc informacionTerminoDocumento;
                                    informacionTerminoDocumento.setFt(1);
                                    informacionTerminoDocumento.setPosTerm(posTermino);
                                    // cout << "Añado el termino " << (*itTokens) << " al documento " << informacioDocumentoAnalizo.getIdDoc() << " con " << informacionTerminoDocumento << " " << endl;
                                    PalabrasIndice->second.insertarDoc(idDocumento, informacionTerminoDocumento);
                                }
                                PalabrasIndice->second.getFtc(ftc);
                                PalabrasIndice->second.setFtc(ftc + 1);
                            }
                        }

                        ++posTermino;

                        lineaAnalizo = "";
                        cantVueltas++;
                    }
                    // cout << "he analizado bien" << endl;
                    //  Ahora que tenemos todos los nuevos terminos y los documentos debemos actualizar nuestra coleccion
                    informacioDocumentoAnalizo.getNumPal(numPal);
                    informacionColeccionDocs.setNumTotalPal(informacionColeccionDocs.getNumTotalPal() + numPal);

                    informacioDocumentoAnalizo.getNumPalSinParada(numSinParada);
                    informacionColeccionDocs.setNumTotalPalSinParada(informacionColeccionDocs.getNumTotalPalSinParada() + numSinParada);

                    informacioDocumentoAnalizo.getTamBytes(numSinParada);
                    informacionColeccionDocs.setTamBytes(informacionColeccionDocs.getTamBytes() + numSinParada);
                    // cout << "he seteado el total de palabras" << endl;

                    // Insertamos el documento en la coleccion
                    // cout << documentoAnalizo << endl;
                    // cout << informacioDocumentoAnalizo << endl;
                    this->indiceDocs.insert({documentoAnalizo, informacioDocumentoAnalizo});
                    documentoAnalizoFich.close();
                }
            }
        }

        // Cerramos el documento con los nombres
        nombresDocumentos.close();
    }
    else
    {
        cerr << "ERROR: no se ha podido abrir el archivo que contiene los nombres de los documentos: " << ficheroDocumentos << "\n";
    }

    // Si todo ha salido segun lo previsto :)
    // cout << cantVueltas << " vueltas" << endl;
    return true;
}

bool IndexadorHash::IndexarDirectorio(const string &dirAIndexar)
{
    struct stat dir;
    int err = stat(dirAIndexar.c_str(), &dir);

    if (err == -1 || !S_ISDIR(dir.st_mode))
    {
        return false;
    }
    else
    {
        // Le decimos al directorio que no coja los archivos con extension .tk por si acaso
        string cmd = "find " + dirAIndexar + " -follow -type f -not -name \"*.tk\" | sort > lista_fich_indexar";
        system(cmd.c_str());
        return Indexar("lista_fich_indexar");
    }
}

bool IndexadorHash::GuardarIndexacion() const
{
    // Obtenemos la informacion del directorio
    struct stat infoDirectorio;
    stat(this->directorioIndice.c_str(), &infoDirectorio);
    Fecha fechaFile;
    int idDocumento;
    int dato;
    unordered_map<int, InfTermDoc> aux;
    list<int> aux2;
    // En el caso de que no exista el directorio tendremos que crearlo
    if (!S_ISDIR(infoDirectorio.st_mode))
    {
        system(string("mkdir " + this->directorioIndice).c_str());
    }

    ofstream ficheroCreado(this->directorioIndice + "/" + "indice", ofstream::out);

    if (!ficheroCreado.good())
    {
        cerr << "ERROR: no se ha podido crear el archivo de indice: " << this->directorioIndice << "/"
             << "indice" << endl;
        return false;
    }
    else
    {
        ficheroCreado << this->almacenarPosTerm << "\n";
        ficheroCreado << this->almacenarEnDisco << "\n";
        ficheroCreado << this->ficheroStopWords << "\n";
        // Escribimos todas las stopWords en el fichero
        for (auto it = this->stopWords.begin(); it != this->stopWords.end(); ++it)
        {
            ficheroCreado << *it << " ";
        }
        ficheroCreado << "\n";

        // Escribimos toda la informacion de la pregunta
        ficheroCreado << this->infPregunta.getNumTotalPal() << "\n";
        ficheroCreado << this->infPregunta.getNumTotalPalDiferentes() << "\n";
        ficheroCreado << this->infPregunta.getNumTotalPalSinParada() << "\n";
        ficheroCreado << this->pregunta << "\n";
        ficheroCreado << indicePregunta.size() << "\n";
        // Escribimos la informacion de todos los terminos de la pregunta
        for (auto it = indicePregunta.begin(); it != indicePregunta.end(); ++it)
        {
            ficheroCreado << it->first << "\n";
            ficheroCreado << it->second.getFt() << "\n";
            list<int> posiciones = it->second.getPosTerm();
            for (auto itTerm = posiciones.begin(); itTerm != posiciones.end(); ++itTerm)
            {
                ficheroCreado << (*itTerm) << " ";
            }
            // El intro nos indica que pasamos al siguiente termino
            ficheroCreado << "\n";
        }

        // Informacion de la coleccion de documentos
        ficheroCreado << this->informacionColeccionDocs.getNumDocs() << "\n";
        ficheroCreado << this->informacionColeccionDocs.getNumTotalPal() << "\n";
        ficheroCreado << this->informacionColeccionDocs.getNumTotalPalDiferentes() << "\n";
        ficheroCreado << this->informacionColeccionDocs.getNumTotalPalSinParada() << "\n";
        ficheroCreado << this->informacionColeccionDocs.getTamBytes() << "\n";

        // Metemos el tamanyo del indice
        ficheroCreado << this->indice.size() << "\n";
        // Escribimos todos los terminos del indice
        for (auto it = indice.begin(); it != indice.end(); ++it)
        {
            it->second.getL_docs(aux);
            ficheroCreado << it->first << "\n";
            it->second.getFtc(dato);
            ficheroCreado << dato << "\n";
            ficheroCreado << aux.size() << "\n";

            for (auto itTerm = aux.begin(); itTerm != aux.end(); ++itTerm)
            {
                ficheroCreado << itTerm->first << "\n";
                itTerm->second.getFt(dato);
                ficheroCreado << dato << "\n";
                itTerm->second.getPosTerm(aux2);

                for (auto itTermPos = aux2.begin(); itTermPos != aux2.end(); ++itTermPos)
                {
                    ficheroCreado << (*itTermPos) << " ";
                }
                ficheroCreado << "\n";
            }
            // El intro nos indica que pasamos al siguiente termino
            ficheroCreado << "\n";
        }

        // Escribimos todo nuestro indice de documentos
        ficheroCreado << this->indiceDocs.size() << "\n";
        for (auto it = indiceDocs.begin(); it != indiceDocs.end(); ++it)
        {
            ficheroCreado << it->first << "\n";
            it->second.getIdDoc(idDocumento);
            ficheroCreado << idDocumento << "\n";
            it->second.getNumPal(dato);
            ficheroCreado << dato << "\n";
            it->second.getNumPalDiferentes(dato);
            ficheroCreado << dato << "\n";
            it->second.getNumPalSinParada(dato);
            ficheroCreado << dato << "\n";
            it->second.getTamBytes(dato);
            ficheroCreado << dato << "\n";

            fechaFile = it->second.getFechaModificacion();
            ficheroCreado << fechaFile.anyo << "\n";
            ficheroCreado << fechaFile.mes << "\n";
            ficheroCreado << fechaFile.dia << "\n";
            ficheroCreado << fechaFile.hora << "\n";
            ficheroCreado << fechaFile.min << "\n";
            ficheroCreado << fechaFile.seg << "\n";
        }
        ficheroCreado << this->tok.CasosEspeciales() << "\n";
        ficheroCreado << this->tok.PasarAminuscSinAcentos() << "\n";
        ficheroCreado << this->tok.DelimitadoresPalabra() << "\n";

        ficheroCreado.close();
        return true;
    }
}

bool IndexadorHash::RecuperarIndexacion(const string &directorioIndexacion)
{
    indice.clear();
    indiceDocs.clear();
    indicePregunta.clear();
    pregunta = "";
    ficheroStopWords = "";
    directorioIndice = "";
    tipoStemmer = 0;
    almacenarEnDisco = false;
    almacenarPosTerm = false;
    InfTermDoc infTermDoc;
    string idDoc;
    int pos = 0;

    ifstream fichero(directorioIndexacion + "/indice", ifstream::in);
    directorioIndice = directorioIndexacion;
    Tokenizador tokAux(" ", false, false);
    list<string> palabras;

    if (fichero.is_open())
    {
        string dato = "";

        getline(fichero, dato);
        almacenarPosTerm = atoi(dato.c_str());

        getline(fichero, dato);
        almacenarEnDisco = atoi(dato.c_str());

        getline(fichero, ficheroStopWords);

        // Cogemos todas las stopWords separadas por espacios y nos las guardamos
        getline(fichero, dato);
        list<string> listaStopWords;
        tokAux.Tokenizar(dato, listaStopWords);
        for (auto it = listaStopWords.begin(); it != listaStopWords.end(); ++it)
        {
            stopWords.insert(*it);
        }

        getline(fichero, dato);
        infPregunta.setNumTotalPal(atoi(dato.c_str()));

        getline(fichero, dato);
        infPregunta.setNumTotalPalDiferentes(atoi(dato.c_str()));

        getline(fichero, dato);
        infPregunta.setNumTotalPalSinParada(atoi(dato.c_str()));

        getline(fichero, pregunta);

        getline(fichero, dato);
        for (unsigned i = atoi(dato.c_str()); i > 0; i--)
        {
            string termino;
            InformacionTerminoPregunta infTermPreg;
            getline(fichero, termino);

            getline(fichero, dato);
            infTermPreg.setFt(atoi(dato.c_str()));
            getline(fichero, dato);

            // Metemos todas las posiciones de la palabra
            tokAux.Tokenizar(dato, palabras);
            for (auto it = palabras.begin(); it != palabras.end(); ++it)
            {
                infTermPreg.setPosTerm(atoi((*it).c_str()));
            }
            indicePregunta.insert({termino, infTermPreg});
        }

        getline(fichero, dato);
        informacionColeccionDocs.setNumDocs(atoi(dato.c_str()));
        getline(fichero, dato);
        informacionColeccionDocs.setNumTotalPal(atoi(dato.c_str()));
        getline(fichero, dato);
        informacionColeccionDocs.setNumTotalPalDiferentes(atoi(dato.c_str()));
        getline(fichero, dato);
        informacionColeccionDocs.setNumTotalPalSinParada(atoi(dato.c_str()));
        getline(fichero, dato);
        informacionColeccionDocs.setTamBytes(atoi(dato.c_str()));

        getline(fichero, dato);
        for (int i = atoi(dato.c_str()); i != 0; i--)
        {
            string termino;
            getline(fichero, termino);

            InformacionTermino infoTermino;
            getline(fichero, dato);
            infoTermino.setFtc(atoi(dato.c_str()));

            getline(fichero, dato);
            for (int j = atoi(dato.c_str()); j != 0; j--)
            {
                getline(fichero, idDoc);

                getline(fichero, dato);
                infTermDoc.setFt(atoi(dato.c_str()));
                getline(fichero, dato);
                tokAux.Tokenizar(dato, palabras);
                for (auto it = palabras.begin(); it != palabras.end(); ++it)
                {
                    pos = atoi((*it).c_str());
                    infTermDoc.setPosTerm(pos);
                }
                int id = atoi(idDoc.c_str());
                infoTermino.insertarDoc(id, infTermDoc);
            }
            indice.insert({termino, infoTermino});
        }

        getline(fichero, dato);
        for (int i = atoi(dato.c_str()); i != 0; i--)
        {
            InfDoc infoDoc;
            string nomDoc;
            getline(fichero, nomDoc);

            getline(fichero, dato);
            infoDoc.setIdDoc(atoi(dato.c_str()));
            getline(fichero, dato);
            infoDoc.setNumPal(atoi(dato.c_str()));
            getline(fichero, dato);
            infoDoc.setNumPalDiferentes(atoi(dato.c_str()));
            getline(fichero, dato);
            infoDoc.setNumPalSinParada(atoi(dato.c_str()));
            getline(fichero, dato);
            infoDoc.setTamBytes(atoi(dato.c_str()));

            getline(fichero, dato);
            palabras.clear();
            tokAux.Tokenizar(dato, palabras);
            auto itTokens = palabras.begin();
            ++itTokens;
            Fecha aux;
            aux.anyo = atoi((*itTokens).c_str());
            ++itTokens;
            aux.mes = atoi((*itTokens).c_str());
            ++itTokens;
            aux.dia = atoi((*itTokens).c_str());
            ++itTokens;
            aux.hora = atoi((*itTokens).c_str());
            ++itTokens;
            aux.min = atoi((*itTokens).c_str());
            ++itTokens;
            aux.seg = atoi((*itTokens).c_str());
            ++itTokens;
            infoDoc.setFechaModificacion(aux);
            indiceDocs.insert({nomDoc, infoDoc});
        }
        getline(fichero, dato);
        tok.CasosEspeciales(atoi(dato.c_str()));
        getline(fichero, dato);
        tok.PasarAminuscSinAcentos(atoi(dato.c_str()));
        getline(fichero, dato);
        tok.DelimitadoresPalabra(dato);
        fichero.close();
    }
    else
    {
        cout << "Error al abrir el fichero" << endl;
        return false;
    }
    return true;
}

void IndexadorHash::ImprimirIndexacion() const
{
    cout << "Terminos indexados: "
         << "\n";
    for (auto it = indiceDocs.begin(); it != indiceDocs.end(); ++it) // A continuación aparecerá un listado del contenido del campo privado “indiceDocs” donde para cada documento indexado se imprimirá: cout << nomDoc << ‘\t’ << InfDoc << endl;
        cout << it->first << '\t' << it->second << "\n";
    cout << "Documentos indexados: "
         << "\n";
    for (auto it = indice.begin(); it != indice.end(); ++it) // A continuación aparecerá un listado del contenido del campo privado “índice” donde para cada término indexado se imprimirá: cout << termino << ‘\t’ << InformacionTermino << endl;
        cout << it->first << '\t' << it->second << "\n";
}

bool IndexadorHash::IndexarPregunta(const string &preg)
{
    int posTerm = 0;
    indicePregunta.clear();
    infPregunta.setNumTotalPal(0);
    infPregunta.setNumTotalPalDiferentes(0);
    infPregunta.setNumTotalPalSinParada(0);

    pregunta = preg;
    list<string> tokensPregunta;

    tok.Tokenizar(pregunta, tokensPregunta);

    infPregunta.setNumTotalPal(tokensPregunta.size());

    if (infPregunta.getNumTotalPal() == 0)
    {
        cerr << "No se ha podido indexar la pregunta"
             << "\n";
        return false;
    }

    for (auto it = tokensPregunta.begin(); it != tokensPregunta.end(); ++it)
    {
        stemmerIndexador.stemmer((*it), tipoStemmer);
        auto itStopWords = stopWords.find((*it));

        if (itStopWords == stopWords.end())
        {
            string palabra = (*it);
            auto itIndicePregunta = indicePregunta.find((*it));

            if (itIndicePregunta != indicePregunta.end())
            {
                itIndicePregunta->second.setFt(itIndicePregunta->second.getFt() + 1);
                itIndicePregunta->second.setPosTerm(posTerm);
            }
            else
            {
                InformacionTerminoPregunta nuevoTermino;
                nuevoTermino.setFt(1);
                nuevoTermino.setPosTerm(posTerm);
                indicePregunta.insert({palabra, nuevoTermino});
                infPregunta.setNumTotalPalDiferentes(infPregunta.getNumTotalPalDiferentes() + 1);
            }
            infPregunta.setNumTotalPalSinParada(infPregunta.getNumTotalPalSinParada() + 1);
        }
        ++posTerm;
    }

    if (infPregunta.getNumTotalPal() == 0)
    {
        cerr << "No se ha podido indexar la pregunta"
             << "\n";
        return false;
    }
    return true;
}

bool IndexadorHash::DevuelvePregunta(string &preg) const
{
    if (!this->pregunta.empty())
    {
        preg = this->pregunta;
        return true;
    }
    else
        return false;
}

bool IndexadorHash::DevuelvePregunta(const string &word, InformacionTerminoPregunta &inf) const
{
    // Buscamos el termino en el indice de pregunta mediante un iterador
    auto it = indicePregunta.find(word);

    if (it != indicePregunta.end())
    {
        // Si lo encontramos se devuelve la informacion dentro del inf
        inf = it->second;
        return true;
    }
    else
        return false;
}

bool IndexadorHash::DevuelvePregunta(InformacionPregunta &inf) const
{
    if (!this->pregunta.empty())
    {
        inf = this->infPregunta;
        return true;
    }
    else
        return false;
}

void IndexadorHash::ImprimirIndexacionPregunta() const
{
    cout << "Pregunta indexada: " << pregunta << "\n";
    cout << "Terminos indexados en la pregunta: "; // << "\n";
    for (auto it = indicePregunta.begin(); it != indicePregunta.end(); ++it)
        cout << it->first << '\t' << it->second << "\n";
    cout << "Informacion de la pregunta: " << infPregunta << "\n";
}

void IndexadorHash::ImprimirPregunta()
{
    cout << "Pregunta indexada : " << this->pregunta << "\n";
    cout << "Informacion de la pregunta : " << this->infPregunta << "\n";
}

bool IndexadorHash::Devuelve(const string &word, InformacionTermino &inf) const
{
    auto temp = indice.find(word);
    if (temp != indice.end())
    {
        inf = temp->second;
        return true;
    }
    inf = InformacionTermino();
    return false;
}

bool IndexadorHash::Devuelve(const string &word, const string &nomDoc, InfTermDoc &InfDoc) const
{
    unordered_map<int, InfTermDoc> aux;
    auto itDocumentos = indiceDocs.find(nomDoc);

    if (itDocumentos != indiceDocs.end())
    {
        auto itIndice = indice.find(word);

        if (itIndice != indice.end())
        {

            int idDoc;
            itDocumentos->second.getIdDoc(idDoc);
            itIndice->second.getL_docs(aux);
            auto itLdocs = aux.find(idDoc);

            if (itLdocs != aux.end())
            {
                InfDoc = itLdocs->second;
                return true;
            }
        }
    }
    return false;
}

bool IndexadorHash::Existe(const string &word) const
{
    return (indice.find(word) != indice.end());
}

bool IndexadorHash::Borra(const string &word)
{
    return (indice.erase(word) != 0);
}

bool IndexadorHash::BorraDoc(const string &nomDoc)
{

    // Buscamos en el indice de documentos el nombre del documento
    auto it = indiceDocs.find(nomDoc);
    int dato;
    int dato2;
    unordered_map<int, InfTermDoc> aux;
    unordered_map<int, InfTermDoc> aux3;
    if (it != indiceDocs.end())
    {
        for (auto itIndice = indice.begin(); itIndice != indice.end(); ++itIndice)
        {
            itIndice->second.getL_docs(aux);
            int idDoc;
            it->second.getIdDoc(idDoc);
            auto itLdocs = aux.find(idDoc);

            if (itLdocs != aux.end())
            {
                itLdocs->second.getFt(dato);
                itIndice->second.getFtc(dato2);
                itIndice->second.setFtc(dato2 - dato);
                aux.erase(itLdocs);
                itIndice->second.setL_docs(aux);

                itIndice->second.getL_docs(aux3);
                if (aux3.empty())
                {
                    indice.erase(itIndice);
                    informacionColeccionDocs.setNumTotalPalDiferentes(informacionColeccionDocs.getNumTotalPalDiferentes() - 1);
                }
            }
        }

        informacionColeccionDocs.setNumDocs(informacionColeccionDocs.getNumDocs() - 1);

        it->second.getNumPal(dato);
        informacionColeccionDocs.setNumTotalPal(informacionColeccionDocs.getNumTotalPal() - dato);

        it->second.getNumPalSinParada(dato);
        informacionColeccionDocs.setNumTotalPalSinParada(informacionColeccionDocs.getNumTotalPalSinParada() - dato);

        it->second.getTamBytes(dato);
        informacionColeccionDocs.setTamBytes(informacionColeccionDocs.getTamBytes() - dato);
        indiceDocs.erase(it);
        return true;
    }
    return false;
}

void IndexadorHash::VaciarIndiceDocs()
{
    indiceDocs.clear();
}

void IndexadorHash::VaciarIndicePreg()
{
    indicePregunta.clear();
}

bool IndexadorHash::Actualiza(const string &word, const InformacionTermino &inf)
{
    if (Existe(word))
    {
        indice[word] = inf;
        return true;
    }
    else
    {
        cerr << "ERROR: En actualiza no existe la palabra " << word << endl;
        return false;
    }
}

bool IndexadorHash::Inserta(const string &word, const InformacionTermino &inf)
{
    auto aux = indice.find(word);
    if (aux == indice.end())
    {
        indice.insert({word, inf});
        return true;
    }
    return false;
}

int IndexadorHash::NumPalIndexadas() const
{
    return this->indice.size();
}

string IndexadorHash::DevolverFichPalParada() const
{
    return this->ficheroStopWords;
}

void IndexadorHash::ListarPalParada() const
{
    for (auto it = stopWords.begin(); it != stopWords.end(); ++it)
        cout << (*it) << "\n";
}

int IndexadorHash::NumPalParada() const
{
    return this->stopWords.size();
}

string IndexadorHash::DevolverDelimitadores() const
{
    return this->tok.DelimitadoresPalabra();
}

bool IndexadorHash::DevolverCasosEspeciales()
{
    return tok.CasosEspeciales();
}

bool IndexadorHash::DevolverPasarAminuscSinAcentos()
{
    return tok.PasarAminuscSinAcentos();
}

bool IndexadorHash::DevolverAlmacenarPosTerm() const
{
    return this->almacenarPosTerm;
}

string IndexadorHash::DevolverDirIndice() const
{
    return this->directorioIndice;
}

int IndexadorHash::DevolverTipoStemming() const
{
    return this->tipoStemmer;
}

bool IndexadorHash::DevolverAlmEnDisco() const
{
    return this->almacenarEnDisco;
}

void IndexadorHash::ListarInfColeccDocs() const
{
    cout << informacionColeccionDocs << "\n";
}

void IndexadorHash::ListarTerminos() const
{
    for (auto it = indice.begin(); it != indice.end(); ++it)
        cout << it->first << '\t' << it->second << "\n";
}

bool IndexadorHash::ListarTerminos(const string &nomDoc) const
{
    unordered_map<int, InfTermDoc> aux;
    auto itIndiceDocs = indiceDocs.find(nomDoc);

    if (itIndiceDocs != indiceDocs.end()) // Comprueba que exista el documento
    {
        for (auto itIndice = indice.begin(); itIndice != indice.end(); ++itIndice) // Recorre lista de terminos indexados
        {
            itIndice->second.getL_docs(aux);
            int idDoc;
            itIndiceDocs->second.getIdDoc(idDoc);
            auto itLdocs = aux.find(idDoc);
            if (itLdocs != aux.end())
                cout << itLdocs->first << '\t' << itIndice->second << "\n";
        }
        return true;
    }
    return false;
}

void IndexadorHash::ListarDocs() const
{
    for (auto it = indiceDocs.begin(); it != indiceDocs.end(); ++it)
        cout << it->first << '\t' << it->second << endl;
}

bool IndexadorHash::ListarDocs(const string &nomDoc) const
{
    auto itIndiceDocs = indiceDocs.find(nomDoc);

    if (itIndiceDocs != indiceDocs.end())
    {
        cout << itIndiceDocs->first << '\t' << itIndiceDocs->second << "\n";
        return true;
    }
    return false;
}