#include "buscador.h"
#include "indexadorHash.h"

ResultadoRI::ResultadoRI(const double &sim, const long int &idD, const int &np)
{
    this->vSimilitud = sim;
    this->idDoc = idD;
    this->numPregunta = np;
}
ResultadoRI::ResultadoRI(const ResultadoRI &copiar)
{
    this->vSimilitud = copiar.vSimilitud;
    this->idDoc = copiar.idDoc;
    this->numPregunta = copiar.numPregunta;
}

bool ResultadoRI::operator<(const ResultadoRI &lhs) const
{
    if (numPregunta == lhs.numPregunta)
        return (vSimilitud < lhs.vSimilitud);
    else
        return (numPregunta > lhs.numPregunta);
}

ostream &operator<<(std::ostream &os, const ResultadoRI &resultado)
{
    return os << resultado.vSimilitud << "\t\t" << resultado.idDoc << "\t" << resultado.numPregunta << "\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Buscador

Buscador::Buscador(const string &directorioIndexacion, const int &f) : IndexadorHash(directorioIndexacion)
{
    formSimilitud = f;
    c = 2;
    k1 = 1.2;
    b = 0.75;
}

Buscador::Buscador() : IndexadorHash()
{
    formSimilitud = 0;
    c = 2;
    k1 = 1.2;
    b = 0.75;
}

Buscador::~Buscador()
{
    this->docsOrdenados.clear();
}

Buscador::Buscador(const Buscador &b) : IndexadorHash(b)
{
    this->formSimilitud = b.formSimilitud;
    this->c = b.c;
    this->k1 = b.k1;
    this->b = b.b;
}

Buscador &Buscador::operator=(const Buscador &cop)
{
    if (this != &cop)
    {
        (*this).~Buscador();
        Buscador(cop);
    }
    return *this;
}

void Buscador::CambiarParametrosBM25(const double &kk1, const double &kb)
{
    this->k1 = kk1;
    this->b = kb;
}

void Buscador::DevolverParametrosBM25(double &kk1, double &kb) const
{
    kk1 = this->k1;
    kb = this->b;
}

void Buscador::CambiarParametrosDFR(const double &kc)
{
    this->c = kc;
}

double Buscador::DevolverParametrosDFR() const
{
    return this->c;
}

bool Buscador::CambiarFormulaSimilitud(const int &f)
{
    if (f == 0 || f == 1)
    {
        this->formSimilitud = f;
        return true;
    }
    return false;
}

int Buscador::DevolverFormulaSimilitud() const
{
    return this->formSimilitud;
}

bool Buscador::SeleccionarMetodo(const int &numDocumentos, const int &numPregunta)
{
    // Tenemos que comprobar que el indice de preguntas no esta vacio
    // En el caso de que este vacio no podemos realizar la busqueda y devolvemos false
    if (indicePregunta.empty())
        return false;
    else
    {
        // cout << "Seleccionando metodo de busqueda...\n";
        if (this->formSimilitud == 0)
        {
            // cout << "Metodo de busqueda: DFR\n";
            realizarDFR(numDocumentos, numPregunta);
        }
        else
        {
            // cout << "Metodo de busqueda: BM25\n";
            realizarBM25(numDocumentos, numPregunta);
        }
        return true;
    }
}

bool Buscador::Buscar(const int &numDocumentos)
{
    this->docsOrdenados.clear();
    return SeleccionarMetodo(numDocumentos, 0);
}

bool Buscador::Buscar(const string &dirPreguntas, const int &numDocumentos, const int &numPregInicio, const int &numPregFin)
{
    // Comprobamos que el directorio con las preguntas existe sacando su información
    struct stat dir;
    if (stat(dirPreguntas.c_str(), &dir) == -1 || !S_ISDIR(dir.st_mode))
    {
        return false;
    }
    else
    {
        // Vaciamos la colección de documentos ordenado
        this->docsOrdenados.clear();
        ifstream fichPregunta;
        string rutaFichero;
        for (int i = numPregInicio; i <= numPregFin; i++)
        {
            // Creamos la ruta del fichero que queremos abrir
            rutaFichero = dirPreguntas + to_string(i) + ".txt";
            fichPregunta.open(rutaFichero.c_str());
            if (fichPregunta.is_open())
            {
                // Cogemos la pregunta de la primera linea
                string pregunta;
                getline(fichPregunta, pregunta);
                fichPregunta.close();
                // Indexamos la pregunta
                IndexarPregunta(pregunta);
                // Seleccionamos el metodo que queremos realizar y lo realizamos
                bool realizado = SeleccionarMetodo(numDocumentos, i);
                if (!realizado)
                    return false;
            }
        }
        // Todo se ha realizado correctamente
        return true;
    }
}

void Buscador::realizarDFR(const int &numDocumentos, const int &numPregunta)
{
    double vSimilitud = 0.0;
    int k = infPregunta.getNumTotalPalSinParada();
    double wiq = 0.0; // peso en la query del termino i de la query q
    double wid = 0.0; // peso en el documento del término i de la query q
    int nt = 0;       // numero de documentos en el que aparece el termino i de la query q
    int ft = 0.0;     // número total de veces que el término t aparece en toda la colección
    int ftd = 0.0;    // número de veces que el término t aparece en el documento d
    double ftq = 0.0;
    double lambda = 0.0; // es la razón entre la frecuencia del término en la colección y la cantidad de documentos en la colección
    double first = 0.0;
    double avg = 0.0; // media en palabras (no de parada) de los documentos
    int ld = 0.0;     // numero de palabras sin parada del documento
    priority_queue<pair<double, long>> aux;

    avg = 1.0 * (double)informacionColeccionDocs.getNumTotalPalSinParada() / (double)informacionColeccionDocs.getNumDocs();

    // cout << "Calculando similitud...\n";
    // cout << indiceDocs.size() << " documentos indexados\n";
    for (auto informacionDoc = indiceDocs.begin(); informacionDoc != indiceDocs.end(); ++informacionDoc)
    {
        informacionDoc->second.getNumPalSinParada(ld);
        // cout << "Calculando similitud para el documento " << informacionDoc->first << "\n";
        //  Para cada documento sacamos su similitud
        vSimilitud = 0.0;

        for (auto terminoPregunta = indicePregunta.begin(); terminoPregunta != indicePregunta.end(); ++terminoPregunta)
        {
            ftq = terminoPregunta->second.getFt();
            wiq = 1.0 * (double)ftq / k;

            // Hay que sacar el id del documento, buscarlo en el indice de documentos y sacar ft del termino en el documento
            // unordered_map<int, InfTermDoc> todoDocumentosAparece;
            int idDoc;
            informacionDoc->second.getIdDoc(idDoc);
            ftd = indice[terminoPregunta->first].getFtDoc(idDoc);
            indice[terminoPregunta->first].getFtc(ft);
            nt = indice[terminoPregunta->first].sizeL_docs();

            if (ftd == 0 || ft == 0 || nt == 0)
            {
            }
            else
            {
                double lambda = 1.0 * ft / indiceDocs.size();
                double ftdd = (double)ftd * log2(1.0 + (c * avg) / ld);
                wid = (log2(1.0 + lambda) + ftdd * log2((1.0 + lambda) / (lambda))) * ((ft + 1) / (nt * (ftdd + 1)));
                vSimilitud += wiq * wid;
            }
        }

        if (vSimilitud != 0.0)
        {
            int idDoc;
            informacionDoc->second.getIdDoc(idDoc);
            aux.push(make_pair(vSimilitud, idDoc));
        }
    }

    for (int i = 0; i < numDocumentos && !aux.empty(); i++)
    {
        docsOrdenados.push_back(ResultadoRI(aux.top().first, aux.top().second, numPregunta));

        aux.pop();
    }
}
void Buscador::realizarBM25(const int &numDocumentos, const int &numPregunta)
{
    double vSimilitud = 0.0;
    double idf = 0.0;
    double ft = 0.0;
    double fd = 0.0;
    double avg = 0.0; // media en palabras (no de parada) de los documentos
    priority_queue<pair<double, long>> aux;

    avg = (double)informacionColeccionDocs.getNumTotalPalSinParada() / (double)informacionColeccionDocs.getNumDocs();

    for (auto informacionDoc = indiceDocs.begin(); informacionDoc != indiceDocs.end(); ++informacionDoc)
    {
        // Para cada documento sacamos su similitud
        vSimilitud = 0.0;
        for (auto infTermPregunta = indicePregunta.begin(); infTermPregunta != indicePregunta.end(); ++infTermPregunta)
        {
            // Para cada termino de la pregunta lo buscamos en el indice
            auto informacionTermino = indice.find(infTermPregunta->first);
            // Comprobamos que no se haya acabado el indice
            if (informacionTermino != indice.end())
            {
                // Sacamos la información del termino en el documento
                // unordered_map<int, InfTermDoc> informacionTerminoDocs;
                // informacionTermino->second.getL_docs(informacionTerminoDocs);

                int idDoc;
                informacionDoc->second.getIdDoc(idDoc);

                // auto infoTerminoDoc = informacionTerminoDocs.find(idDoc);

                if (informacionTermino->second.existeDocu(idDoc))
                {
                    int ft;
                    ft = informacionTermino->second.getFtDoc(idDoc);

                    int ftc;
                    informacionTermino->second.getFtc(ftc);

                    if (ft != 0) // Si el termino aparece al menos una vez en el documento aplicamos la formula
                    {
                        int numSinParada;
                        informacionDoc->second.getNumPalSinParada(numSinParada);
                        idf = log2(((double)informacionColeccionDocs.getNumDocs() - (double)informacionTermino->second.sizeL_docs() + 0.5) / ((double)informacionTermino->second.sizeL_docs() + 0.5));
                        fd = (ft * (k1 + 1.0)) / (ft + k1 * (1.0 - b + (b * abs((double)numSinParada / avg))));
                        vSimilitud += idf * fd;
                    }
                }
            }
        }
        if (vSimilitud != 0.0)
        {
            int idDoc;
            informacionDoc->second.getIdDoc(idDoc);
            aux.push(make_pair(vSimilitud, idDoc));
        }
    }

    for (int i = 0; i < numDocumentos && !aux.empty(); i++)
    {
        docsOrdenados.push_back(ResultadoRI(aux.top().first, aux.top().second, numPregunta));
        aux.pop();
    }
}

string Buscador::sacarNombreDocId(const long int &idDoc) const
{
    string rutaFichero;
    bool encontrado = false;
    for (auto informacionDoc = indiceDocs.begin(); informacionDoc != indiceDocs.end() && !encontrado; ++informacionDoc)
    {
        int auxIdDoc;
        informacionDoc->second.getIdDoc(auxIdDoc);
        if (auxIdDoc == idDoc)
        {
            rutaFichero = informacionDoc->first;
            encontrado = true;
        }
    }

    if (encontrado)
    {
        string::size_type pos = rutaFichero.find_last_of("/");
        pos++;
        if (pos == string::npos)
            pos = 0;
        string::size_type pos2 = rutaFichero.find_first_of(".", pos);
        return rutaFichero.substr(pos, pos2 - pos);
    }
    else
        return "";
}

void Buscador::ImprimirResultadoBusqueda(const int &numDocumentos) const
{
    string impresion;
    int aux;
    int x = 0;
    while (x != docsOrdenados.size())
    {
        aux = docsOrdenados[x].NumPregunta();
        for (int i = 0; i < numDocumentos; i++)
        {
            if (docsOrdenados[x].NumPregunta() != aux || x == docsOrdenados.size())
            {
                break;
            }
            else
            {
                aux = docsOrdenados[x].NumPregunta();
                impresion += to_string(aux);
                impresion += " ";
                if (!formSimilitud)
                {
                    impresion += "DFR ";
                }
                else
                {
                    impresion += "BM25 ";
                }
                impresion += sacarNombreDocId(docsOrdenados[x].IdDoc()) + " ";
                impresion += to_string(i) + " ";
                impresion += to_string(docsOrdenados[x].VSimilitud()) + " ";
                if (docsOrdenados[x].NumPregunta() == 0)
                {
                    string preg;
                    if (DevuelvePregunta(preg))
                        impresion += preg + "\n";
                    else
                        impresion += "\n";
                }
                else
                {
                    impresion += "ConjuntoDePreguntas\n";
                }
            }
            x++;
        }
    }
    cout << impresion;
}

bool Buscador::ImprimirResultadoBusqueda(const int &numDocumentos, const string &nombreFichero) const
{
    ofstream ficheroEscribo(nombreFichero.c_str());
    if (ficheroEscribo)
    {
        string impresion;
        int aux;
        int x = 0;
        while (x != docsOrdenados.size())
        {
            aux = docsOrdenados[x].NumPregunta();
            for (int i = 0; i < numDocumentos; i++)
            {
                if (docsOrdenados[x].NumPregunta() != aux || x == docsOrdenados.size())
                {
                    break;
                }
                else
                {
                    aux = docsOrdenados[x].NumPregunta();
                    impresion += to_string(aux);
                    impresion += " ";
                    if (!formSimilitud)
                    {
                        impresion += "DFR ";
                    }
                    else
                    {
                        impresion += "BM25 ";
                    }
                    impresion += sacarNombreDocId(docsOrdenados[x].IdDoc()) + " ";
                    impresion += to_string(i) + " ";
                    impresion += to_string(docsOrdenados[x].VSimilitud()) + " ";
                    if (docsOrdenados[x].NumPregunta() == 0)
                    {
                        string preg;
                        if (DevuelvePregunta(preg))
                            impresion += preg + "\n";
                        else
                            impresion += "\n";
                    }
                    else
                    {
                        impresion += "ConjuntoDePreguntas\n";
                    }
                }
                x++;
            }
        }
        ficheroEscribo << impresion;
        ficheroEscribo.close();
        return true;
    }
    else
    {
        return false;
    }
}

ostream &operator<<(ostream &s, const Buscador &p)
{
    string preg;
    s << "Buscador : " << endl;
    if (p.DevuelvePregunta(preg))
        s << "\tPregunta indexada : " << preg << endl;
    else
        s << "\tNo hay ninguna pregunta indexada" << endl;

    s << "\tDatos del indexador : " << endl
      << (IndexadorHash)p; // Invoca a la sobrecarga de la salida del Indexador

    return s;
}
