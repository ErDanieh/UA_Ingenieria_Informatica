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

IndexadorHash::IndexadorHash() : tok()
{
    this->ficheroStopWords= "";
    this->tipoStemmer= 0;
    this->stopWords.clear();

    this->directorioIndice= "./"; // Directorio raiz
    this->almacenarEnDisco= false;
    this->almacenarPosTerm= false;
    
    //this->indiceDisco.clear();
    //this->indiceDocsDisco.clear();
    this->indice.clear();
    this->indiceDocs.clear();
    this->indicePregunta.clear();
    this->infPregunta.~InformacionPregunta();
    this->informacionColeccionDocs.~InfColeccionDocs();
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
    // Tokenizamos la lista de ficheros
    bool nice = tok.TokenizarListaFicheros(ficheroDocumentos);
    ifstream ficheroNombres(ficheroDocumentos, ifstream::in);
    ifstream ficheroAnalizo;
    string nombreDocu = "";
    int idDocumento = 0;
    bool indexar = false;
    int posTermino = 0;
    struct stat infoDocumento;
    Fecha fechaMod;
    int cantDocs = 0;
    string linea;
    int palDiferentes = 0;
    int idAnalizo = 0;
    int sinParada = 0;
    int numTotal = 0;
    int ftc;

    int numTotalColec = 0;
    int numTotalSinParada = 0;
    int numTotalBytes = 0;

    if (ficheroNombres.is_open() && nice)
    {
        while (ficheroNombres >> nombreDocu)
        {
            InfDoc infoDoc;
            auto indiceDocumentos = indiceDocs.find(nombreDocu);
            // Reiniciamos los valores
            idDocumento = -1;
            posTermino = 0;
            indexar = false;
            sinParada = 0;
            palDiferentes = 0;
            numTotal = 0;

            // Sacamos las stats del documento
            stat(nombreDocu.c_str(), &infoDocumento);
            Fecha fechaDocu(gmtime(&(infoDocumento.st_mtime)));

            // Si el documento ya ha sido indexado anteriormente
            if (indiceDocumentos != indiceDocs.end())
            {
                cerr << "ERROR: El documento " << nombreDocu << " ya ha sido indexado anteriormente"
                     << "\n";

                if (indiceDocumentos->second.getFechaModificacion() < fechaDocu)
                {
                    // Rescatamos el id del documento
                    indiceDocumentos->second.getIdDoc(idDocumento);
                    indexar = true;
                }
                // Borramos el documento de nuestro indice así como todas sus palabras
                if (!BorraDoc(nombreDocu))
                {
                    cerr << "ERROR: No se ha podido borrar el documento " << nombreDocu << "\n";
                    return false;
                }
            }
            else
            {
                indexar = true;
            }

            if (indexar)
            {
                ficheroAnalizo.open(nombreDocu + ".tk", ifstream::in);
                if (ficheroAnalizo.is_open())
                {
                    if (idDocumento != -1)
                    {
                        infoDoc.setIdDoc(idDocumento);
                    }
                    else
                    {
                        // Le asignamos un id al documento creando un nuevo id
                        informacionColeccionDocs.setNumDocs(informacionColeccionDocs.getNumDocs() + 1);

                        infoDoc.setIdDoc(informacionColeccionDocs.getNumDocs());
                    }
                    int id = informacionColeccionDocs.getNumDocs();
                    // Asignamos las stats de nuestro documento
                    infoDoc.setTamBytes(infoDocumento.st_size);
                    numTotalBytes += infoDocumento.st_size;
                    infoDoc.setFechaModificacion(fechaDocu);
                    while (ficheroAnalizo >> linea)
                    {
                        ++numTotal;
                        ++numTotalColec;

                        if (tipoStemmer != 0)
                            stemmerIndexador.stemmer(linea, tipoStemmer);

                        // No es una stopWord pasamos a indexarlar
                        if (stopWords.find(linea) == stopWords.end())
                        {
                            ++sinParada;
                            ++numTotalSinParada;
                            // Si la palabra no esta en el indice la añadimos
                            if (indice.find(linea) == indice.end())
                            {
                                InfTermDoc infoTermDoc(1, posTermino);
                                pair<int, InfTermDoc> pareja(id, infoTermDoc);
                                InformacionTermino infoTermino(1, pareja);

                                // Incrementamos el total de palabras del documento
                                // infoDoc.getNumPalDiferentes(palDiferentes);
                                ++palDiferentes;
                                // infoDoc.setNumPalDiferentes(palDiferentes + 1);

                                // Incrementamos el total de palabras de la coleccion
                                informacionColeccionDocs.setNumTotalPalDiferentes(informacionColeccionDocs.getNumTotalPalDiferentes() + 1);

                                // Añadimos el termino al indice
                                indice.insert(pair<string, InformacionTermino>(linea, infoTermino));
                            }
                            else // Si el termino ya existe cargamos la informacion para modificarla
                            {
                                auto docu = indice.find(linea);
                                // Existe el documento dentro de su L_Docs
                                if (docu->second.existeDocu(id))
                                {
                                    // cout << "Edito"<< endl;

                                    // docu->second.getFtc(ftc);
                                    // docu->second.setFtc(ftc + 1);
                                    docu->second.incrementarFt(id);
                                    docu->second.modificarDoc(id, posTermino);
                                }
                                else // Si existe pero no en el documento actual
                                {
                                    // cout << "Añado" << endl;
                                    int num;
                                    ++palDiferentes;

                                    InfTermDoc infoTermDoc(1, posTermino);
                                    pair<int, InfTermDoc> pareja(id, infoTermDoc);

                                    docu->second.insertarDoc(pareja);
                                }
                                int ftc;
                                docu->second.getFtc(ftc);
                                docu->second.setFtc(ftc + 1);
                            }
                        }
                        ++posTermino;
                        linea = "";
                    }
                }

                infoDoc.setNumPalSinParada(sinParada);
                infoDoc.setNumPal(numTotal);
                infoDoc.setNumPalDiferentes(palDiferentes);
                // informacionColeccionDocs.setNumDocs(informacionColeccionDocs.getNumDocs() + 1);
                indiceDocs.insert(pair<string, InfDoc>(nombreDocu, infoDoc));
                // cout << "Documento " << nombreDocu << " indexado correctamente" << endl;
                ficheroAnalizo.close();
            }
        }
        informacionColeccionDocs.setNumTotalPal(informacionColeccionDocs.getNumTotalPal() + numTotalColec);
        informacionColeccionDocs.setNumTotalPalSinParada(informacionColeccionDocs.getNumTotalPalSinParada() + numTotalSinParada);
        informacionColeccionDocs.setTamBytes(informacionColeccionDocs.getTamBytes() + numTotalBytes);
    }
    else
    {
        cerr << "ERROR: No se ha podido abrir el directorio " << ficheroDocumentos << "\n";
        cerr << "ERROR: No se ha podido Tokenizar " << endl;
        return false;
    }
    ficheroNombres.close();

    if (this->almacenarEnDisco)
    {
        return GuardarIndexacion();
    }

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
        // cout << "Almacenando " << this->almacenarPosTerm << endl;
        ficheroCreado << this->almacenarPosTerm << "\n";
        // cout << "Almacenando " << this->almacenarEnDisco << endl;
        ficheroCreado << this->almacenarEnDisco << "\n";
        // cout << "Almacenando " << this->ficheroStopWords << endl;
        ficheroCreado << this->ficheroStopWords << "\n";

        // Escribimos todas las stopWords en el fichero
        for (auto it = this->stopWords.begin(); it != this->stopWords.end(); ++it)
        {
            // cout << "StopWord: " << *it << endl;
            ficheroCreado << *it << " ";
        }
        ficheroCreado << "\n";

        // Escribimos toda la informacion de la pregunta
        ficheroCreado << this->infPregunta.getNumTotalPal() << "\n";

        ficheroCreado << this->infPregunta.getNumTotalPalDiferentes() << "\n";
        ficheroCreado << this->infPregunta.getNumTotalPalSinParada() << "\n";
        ficheroCreado << this->pregunta << "\n";
        ficheroCreado << indicePregunta.size() << "\n";
        // cout<< "Indice pregunta: " << indicePregunta.size() << endl;
        //  Escribimos la informacion de todos los terminos de la pregunta
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
        // cout <<"Tambytes escribo:" <<this->informacionColeccionDocs.getTamBytes() << endl;

        // Metemos el tamanyo del indice
        ficheroCreado << this->indice.size() << "\n";
        // Escribimos todos los terminos del indice
        for (auto it = indice.begin(); it != indice.end(); ++it)
        {
            it->second.getL_docs(aux);
            // cout << it->first << endl;
            ficheroCreado << it->first << "\n";
            it->second.getFtc(dato);
            // cout << dato << endl;
            // cout << aux.size() << endl;
            ficheroCreado << dato << "\n";
            ficheroCreado << aux.size() << "\n";

            for (auto itTerm = aux.begin(); itTerm != aux.end(); ++itTerm)
            {
                // cout<< itTerm->first << endl;
                ficheroCreado << itTerm->first << "\n";
                itTerm->second.getFt(dato);
                ficheroCreado << dato << "\n";
                itTerm->second.getPosTerm(aux2);

                for (auto itTermPos = aux2.begin(); itTermPos != aux2.end(); ++itTermPos)
                {
                    // cout << (*itTermPos) << " ";
                    ficheroCreado << (*itTermPos) << " ";
                }
                // cout << endl;
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
    // cout << "RECUPERANDO INDEXACION" << endl;
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
        // out << "Almacenando " << this->almacenarPosTerm << endl;

        getline(fichero, dato);
        almacenarEnDisco = atoi(dato.c_str());
        // cout << "Almacenando " << this->almacenarEnDisco << endl;

        getline(fichero, ficheroStopWords);
        // cout << "Almacenando " << this->ficheroStopWords << endl;

        // Cogemos todas las stopWords separadas por espacios y nos las guardamos
        getline(fichero, dato);
        list<string> listaStopWords;
        tokAux.Tokenizar(dato, listaStopWords);
        for (auto it = listaStopWords.begin(); it != listaStopWords.end(); ++it)
        {
            // cout << "StopWord: " << *it << endl;
            stopWords.insert(*it);
        }

        getline(fichero, dato);
        infPregunta.setNumTotalPal(atoi(dato.c_str()));
        // cout << dato << endl;

        getline(fichero, dato);
        infPregunta.setNumTotalPalDiferentes(atoi(dato.c_str()));

        getline(fichero, dato);
        infPregunta.setNumTotalPalSinParada(atoi(dato.c_str()));

        getline(fichero, this->pregunta);
        getline(fichero, dato);
        // cout << "Indice pregunta leo: " << dato << endl;
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
        // cout << "Tambytes guardo: ";
        // cout << dato << endl;

        getline(fichero, dato);
        // cout << "tamaño indice:" << dato << endl;
        int tam = atoi(dato.c_str());
        int i = 0;
        while (i != tam)
        {
            // cout << i << endl;
            string termino;
            getline(fichero, termino);
            // cout<<"Termino: " << termino << endl;

            InformacionTermino infoTermino;
            getline(fichero, dato);
            // cout<< "FTC: " << dato << endl;
            infoTermino.setFtc(atoi(dato.c_str()));

            int lDocsSize;
            getline(fichero, dato);
            lDocsSize = atoi(dato.c_str());
            // cout << "lDocsSize: " << lDocsSize << endl;

            for (int j = 0; j <= lDocsSize - 1; j++)
            {
                InfTermDoc infoTerminoDoc;
                // Cogemos el id del documento
                getline(fichero, dato);
                int idDoc = atoi(dato.c_str());
                // Seteamo el ft del documento
                getline(fichero, dato);
                int ft = atoi(dato.c_str());
                infoTerminoDoc.setFt(ft);

                getline(fichero, dato);
                // cout << "Posiciones: " << dato << endl;
                tokAux.Tokenizar(dato, palabras);
                for (auto it = palabras.begin(); it != palabras.end(); ++it)
                {
                    int pos = atoi((*it).c_str());
                    infoTerminoDoc.setPosTerm(pos);
                }
                pair<int, InfTermDoc> p = make_pair(idDoc, infoTerminoDoc);
                infoTermino.insertarDoc(p);
            }
            // cout << infoTermino << endl;
            indice.insert({termino, infoTermino});
            // cout << "otra palabra"<< endl;
            i++;
            getline(fichero, dato);
        }

        int cantDocs;
        getline(fichero, dato);
        // cout << "Cantidad de documentos: " << dato;

        cantDocs = atoi(dato.c_str());
        int j = 0;

        while (j != cantDocs)
        {
            InfDoc infoDoc;
            string nombreDoc;
            getline(fichero, nombreDoc);

            int idDoc;
            getline(fichero, dato);
            idDoc = atoi(dato.c_str());
            infoDoc.setIdDoc(idDoc);

            int palabras;
            getline(fichero, dato);
            palabras = atoi(dato.c_str());
            infoDoc.setNumPal(palabras);

            getline(fichero, dato);
            palabras = atoi(dato.c_str());
            infoDoc.setNumPalDiferentes(palabras);

            getline(fichero, dato);
            palabras = atoi(dato.c_str());
            infoDoc.setNumPalSinParada(palabras);

            int tambytes;
            getline(fichero, dato);
            tambytes = atoi(dato.c_str());
            infoDoc.setTamBytes(tambytes);

            int datoFecha;
            Fecha fecha;
            getline(fichero, dato);
            datoFecha = atoi(dato.c_str());
            fecha.anyo = datoFecha;

            getline(fichero, dato);
            datoFecha = atoi(dato.c_str());
            fecha.mes = datoFecha;

            getline(fichero, dato);
            datoFecha = atoi(dato.c_str());
            fecha.dia = datoFecha;

            getline(fichero, dato);
            datoFecha = atoi(dato.c_str());
            fecha.hora = datoFecha;

            getline(fichero, dato);
            datoFecha = atoi(dato.c_str());
            fecha.min = datoFecha;

            getline(fichero, dato);
            datoFecha = atoi(dato.c_str());
            fecha.seg = datoFecha;

            j++;
            indiceDocs.insert({nombreDoc, infoDoc});
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
        cerr << "ERROR: al abrir el fichero" << endl;
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

    if (this->almacenarEnDisco)
    {
        return GuardarIndexacion();
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
    string palabra = word;
    if (tok.PasarAminuscSinAcentos())
    {
        palabra = tok.normalizaAcentosMinusculas(word);
    }
    // Buscamos el termino en el indice de pregunta mediante un iterador
    auto it = indicePregunta.find(palabra);

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

        if (this->almacenarEnDisco)
        {
            GuardarIndexacion();
        }

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
        if (this->almacenarEnDisco)
        {
            GuardarIndexacion();
        }
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

        if (this->almacenarEnDisco)
        {
            GuardarIndexacion();
        }
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