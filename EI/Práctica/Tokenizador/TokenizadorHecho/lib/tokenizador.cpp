#include "tokenizador.h"

const string Tokenizador::delimiters_Siempre = " \n";

/**
 * TODO:Si encuentro otro . o , cambia el pos al siguiente
 * TODO:Poner \n y espacio de delimitadores
 * TODO: Corregir pruebas fallan
 * TODO: Evitar salto linea consola
 * TODO: Dibujar bien el grafo para presentacion
 * TODO: Mirar mmap
 **/

Tokenizador::Tokenizador()
{
    this->delimiters = ",;:.-/+*\\ '\"{}[]()<>�!�?&#=\t\n\r@";
    this->casosEspeciales = true;
    this->pasarAminuscSinAcentos = false;
}

Tokenizador::Tokenizador(const string &delimitadoresPalabra, const bool &kcasosEspeciales, const bool &minuscSinAcentos)
{
    this->casosEspeciales = kcasosEspeciales;
    this->pasarAminuscSinAcentos = minuscSinAcentos;
    this->delimiters = delimitadoresPalabra;
    EliminarRepetidos(this->delimiters);
}

Tokenizador::Tokenizador(const Tokenizador &token)
{
    this->delimiters = token.delimiters;
    this->casosEspeciales = token.casosEspeciales;
    this->pasarAminuscSinAcentos = token.pasarAminuscSinAcentos;
}

Tokenizador::~Tokenizador()
{
    this->delimiters.clear();
}

Tokenizador &Tokenizador::operator=(const Tokenizador &t)
{
    if (this != &t)
    {
        this->delimiters = t.delimiters;
        this->casosEspeciales = t.casosEspeciales;
        this->pasarAminuscSinAcentos = t.pasarAminuscSinAcentos;
    }
    return (*this);
}

void Tokenizador::EliminarRepetidos(string &delimitadoresPalabra)
{
    string delimitadores = "";
    for (int i = 0; i < delimitadoresPalabra.length(); i++)
    {
        if (delimitadores.find(delimitadoresPalabra[i]) == string::npos)
            delimitadores += delimitadoresPalabra[i];
    }
    delimitadoresPalabra = delimitadores;
}

string Tokenizador::normalizaAcentosMinusculas(const string &palabra) const
{

    string palabraAux = palabra;
    char ISO[260]= "                                 !\"#$%&'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[ ]^_`abcdefghijklmnopqrstuvwxyz{|}~ ? ,                                                            �aaaaaa ceeeeiiii  ooooo  uuuuy  aaaaaa ceeeeiiii  ooooo  uuuuy y";
    ISO[241]= ISO[209]= '�';
    for (int i = 0; i < palabraAux.size(); i++)
        palabraAux[i] = ISO[(unsigned char)palabra[i]];
    
    return palabraAux;
}

void Tokenizador::Tokenizar(const string &str, list<string> &tokens) const
{
    if (!tokens.empty())
        tokens.clear();

    if (this->casosEspeciales)
    {
        // cout << str << endl;
        UsandoCasosEspeciales(tokens, str);
    }
    else
    {

        string token;
        string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        string::size_type pos = str.find_first_of(delimiters, lastPos);
        while (string::npos != pos || string::npos != lastPos)
        {
            if (this->pasarAminuscSinAcentos)
                token = normalizaAcentosMinusculas(str.substr(lastPos, pos - lastPos));
            else
                token = str.substr(lastPos, pos - lastPos);

            tokens.push_back(token);
            lastPos = str.find_first_not_of(delimiters, pos);
            pos = str.find_first_of(delimiters, lastPos);
        }
    }
}

bool Tokenizador::Tokenizar(const string &i, const string &f) const
{
    ifstream file;
    ofstream fileOut;
    string cadena;
    list<string> tokens;
    file.open(i.c_str());
    fileOut.open(f.c_str());
    list<string>::iterator itS;

    if (!file)
    {
        cerr << "ERROR: No existe el archivo: " << i << "\n";
        return false;
    }
    else
    {
        while (!file.eof())
        {
            cadena = "";
            getline(file, cadena);
            if (cadena.length() != 0)
            {
                Tokenizar(cadena, tokens);
                for (itS = tokens.begin(); itS != tokens.end(); itS++)
                {
                    fileOut << (*itS) << "\n";
                }
            }
        }
    }
    file.close();
    fileOut.close();

    if (!tokens.empty())
        tokens.clear();

    return true;
}

#if 0
bool Tokenizador::Tokenizar(const string &i) const
{
    return Tokenizar(i, i + ".tk");
}
#endif

bool Tokenizador::TokenizarListaFicheros(const string &i) const
{
    bool resultado = true;
    string fichero;
    fstream f(i);

    getline(f, fichero);
    while (!f.eof())
    {
        if (!Tokenizar(fichero))
            resultado = false;

        getline(f, fichero);
    }
    return resultado;
}

bool Tokenizador::TokenizarDirectorio(const string &i) const
{
    struct stat dir;
    // Compruebo la existencia del directorio
    int err = stat(i.c_str(), &dir);
    if (err == -1 || !S_ISDIR(dir.st_mode))
        return false;
    else
    {
        // Hago una lista en un fichero con find>fich
        string cmd = "find " + i + " -type f -follow |sort > .lista_fich";
        system(cmd.c_str());
        return TokenizarListaFicheros(".lista_fich");
    }
}

void Tokenizador::DelimitadoresPalabra(const string &nuevoDelimiters)
{
    // Solo si los casos especiales est�n activados se a�adir�n los delimitadores que siempre se activan
    // el salto de linea y el espacio
    EliminarRepetidos(this->delimiters = nuevoDelimiters);
}

void Tokenizador::AnyadirDelimitadoresPalabra(const string &nuevoDelimiters)
{
    if (!this->casosEspeciales)
    {
        EliminarRepetidos(this->delimiters += nuevoDelimiters);
    }
    else
    {
        string insertados = delimiters_Siempre + nuevoDelimiters;
        EliminarRepetidos(insertados);
        this->delimiters += insertados;
    }
}

string Tokenizador::DelimitadoresPalabra() const
{
    return this->delimiters;
}

void Tokenizador::CasosEspeciales(const bool &nuevoCasosEspeciales)
{
    if (!nuevoCasosEspeciales)

        this->casosEspeciales = nuevoCasosEspeciales;
}

bool Tokenizador::CasosEspeciales()
{
    return this->casosEspeciales;
}

void Tokenizador::PasarAminuscSinAcentos(const bool &nuevoPasarAminuscSinAcentos)
{
    this->pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

bool Tokenizador::PasarAminuscSinAcentos()
{
    return this->pasarAminuscSinAcentos;
}

ostream &operator<<(ostream &os, const Tokenizador &tokenizador)
{
    os << "DELIMITADORES: " << tokenizador.DelimitadoresPalabra() << " TRATA CASOS ESPECIALES: " << tokenizador.casosEspeciales
       << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tokenizador.pasarAminuscSinAcentos;
    return os;
}

bool Tokenizador::EsDelimitador(const char caracter, int &casoAnterior) const
{
    if (caracter == '\0' || caracter == ' ' || this->delimiters.find(caracter) != string::npos)
    {
        return true;
    }
    return false;
}

bool Tokenizador::delimitadorDeReales(const char c) const
{

    // Miramos si esta en los caracteres definidos en los delimitadores de los reales
    if (delimitadoresReal.find(c) != string::npos)
        return true;
    else if ((unsigned char)c == 164) // Miramos si el caracter es el simbolo del euro en iso-8859-1
        return true;
    else
        return false;
}

void Tokenizador::analizaURLHTTPFTP(char &c, int &estado, const string &frase, string::size_type &pos, string::size_type &npos, bool &salida, int &casoAnterior) const
{
    casoAnterior = estado;
    if ((pos + 5 < frase.length() && (frase[pos] == 'h' || frase[pos] == 'H') && frase[pos + 1] == 't' && frase[pos + 2] == 't' && frase[pos + 3] == 'p' &&
         (frase[pos + 4] == ':' || (pos + 6 < frase.length() && frase[pos + 4] == 's' && frase[pos + 5] == ':'))) ||
        (pos + 4 < frase.length() && (frase[pos] == 'f' || frase[pos] == 'F') && frase[pos + 1] == 't' && frase[pos + 2] == 'p' && frase[pos + 3] == ':'))
    {
        estado = TOK_URL;
        npos = frase.find_first_of(':', pos);
    }
    // Si se acaba el fichero directamete salimos
    else if (c == '\0')
        salida = true;
    // Nos comemos los delimitadores para que no entren se corte la URL
    else if (c != '.' && c != ',' && EsDelimitador(c, casoAnterior))
        ++pos;
    // En el caso de que no sea una URL pasamos a los reales
    else
        estado = TOK_Real;
}

void Tokenizador::analizaURLyMarcaTokeniza(string::size_type &npos, const string &frase, int &estado, int &casoAnterior) const
{
    casoAnterior = estado;
    bool salbucle = true;
    while (salbucle)
    {
        // Vamos saltandonos los delimitadores de la URL para poder meterlos todos en una sola palabra
        npos = frase.find_first_of(this->delimiters, npos + 1);
        // Salimos del bucle cuando encontremos un delimitador de URL o nos quedemos sin palabra
        if (npos > frase.length() || delimitadoresURL.find(frase[npos]) == string::npos || frase[npos] == '\0')
            salbucle = false;
    }
    // Pasamos a la tokenización normal ya que nos hemos comido los delimitadores de la URL y las letras
    estado = TOKENIZARnormal;
}

void Tokenizador::analizaReal(char &c, int &estado, const string &frase, string::size_type &pos, string::size_type &npos,
                              bool &salida, bool &delimitadorRealEspecial, bool &anadirCero, int &casoAnterior) const
{
    casoAnterior = estado;
    switch (estado)
    {
    case TOK_Real:
        npos = pos;
        c = frase[npos];
#if 0
        cout<<frase<<endl;
        cout << frase[pos]<<endl;
        cout << frase[pos-1]<<endl;
        cout << c << endl;
        cout<<"--------"<<endl;
#endif
        // Miramos si al n?mero real hay que a?adirle un 0 porque no lo tiene en el texto
        if ((c == '.' || c == ','))
            estado = TOK_AnadeCero;
        else if (c >= '0' && c <= '9')
            estado = TOK_Real2;
        else
            estado = TOK_Email;
        break;

    // Al ser un numero decimal asi -> .9 debemos anadirle un 0 en la tokenizacion ->0.9
    case TOK_AnadeCero:
        // Comprabamos si debemos anadir un 0 al numero tokenizado
        if (c >= '0' && c <= '9')
        {
            anadirCero = true;
            estado = TOK_Real2;
        }
        else
            estado = TOK_Email;
        break;

    // Analizamos las comas y puntos ya que el numero es decimal
    case TOK_Real2:
        if (c == '.' || c == ',')
            estado = TOK_Real3;
        else if (EsDelimitador(c, casoAnterior))
            estado = TOKENIZARreal;
        else if (delimitadorDeReales(c))
        {
            delimitadorRealEspecial = true;
            estado = TOK_Real4;
        }
        else if (c < '0' || c > '9') // Si encontramos una letra pasamos a los emails
            estado = TOK_Email;
        break;

    case TOK_Real3:
        if (c >= '0' && c <= '9')
            estado = TOK_Real2; // Volvemos a analizar los numeros
        else if (EsDelimitador(c, casoAnterior))
        {
            estado = TOKENIZARreal;
            --npos;
        }
        else
            estado = TOK_Email;
        break;
    case TOK_Real4:
        if (EsDelimitador(c, casoAnterior))
        {
            estado = TOKENIZARreal;
            --npos;
        }
        else
            estado = TOK_Email;
    }
}

void Tokenizador::analizaEmail(char &c, int &estado, const string &frase, string::size_type &pos,
                               string::size_type &npos, bool &salida, int &numArrobas, int &casoAnterior) const
{
    casoAnterior = estado;
    // Lee una string hasta el primer espacio o fin de cadena
    switch (estado)
    {
    /**
     * Analizamos los emails, si encontramos que la primera palabra es un delimitador saltamos
     * a mirar si es un acrónimo, en el caso contrario buscamos la arroba
     */
    case TOK_Email:
        npos = pos;
        c = frase[npos];
        if (EsDelimitador(c, casoAnterior))
            estado = TOK_Acronimo;
        else
            estado = TOK_EmailArroba;
        break;
    /**
     * Si encontramos la arroba seguimos tokenizando como correo pero sumamos una al contador
     * de arrobas porque si nos encontramos otra pasaremos a acronimo
     * Además nos comeremos los delimitadores de emails
     * Si encontramos un delimitador no soportado por los emails deberemos pasar a acronimos
     */
    case TOK_EmailArroba:
        if (c == '@') // Buscamos el arrboba para mandar todo el trozo a tokenizar
        {
            estado = TOK_EmailSaleOTokeniza;
            ++numArrobas;
        }
        else if (delimitadoresEmail.find(c) != string::npos)
        {
            // Nos comemos los delimitadores de los emails
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOK_Acronimo;
        break;
    /**
     * Si nos encontramos más arrobas de las debidas o el número de arrobas es mayor de 1
     * entonces pasamos a los acronimos
     * Sino nos comemos los delimitadores de los emails
     * Y si encontramos un delimitador no soportado por los emails deberemos pasar a tokenizar todo.
     */
    case TOK_EmailSaleOTokeniza:
        if (c == '@' || numArrobas > 1)
            estado = TOK_Acronimo;
        else if (delimitadoresEmail.find(c) != string::npos)
        {
            // Nos comememos los delimitadores de los emails
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOKENIZARnormal;
        break;
    }
}

void Tokenizador::analizaAcronimo(char &c, int &estado, const string &frase, string::size_type &pos, string::size_type &npos,
                                  bool &salida, int &numPuntoIzquierda, int &numPuntosDerecha, int &casoAnterior) const
{
    casoAnterior = estado;
    switch (estado)
    {
    /**
     * Si encontramos un punto a la izquierda lo cogemos, Si encontramos un delimitador
     * pasamos a palabra compuesta, sino seguimos leyendo el acronimo
     */
    case TOK_Acronimo:
        npos = pos;
        c = frase[npos];
        if (c == '.')
        {
            ++numPuntoIzquierda;
            estado = TOK_AcronimoDelimExit;
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOK_Guion;
        else
            estado = TOK_AcronimoPuntosDer;
        break;
    /**
     * Si es un delimitador o otro punto nos salimos a los guiones
     * si es una letra seguimos en el acronimo
     */
    case TOK_AcronimoDelimExit:
        if (EsDelimitador(c, casoAnterior) || c == '.')
            estado = TOK_Guion;
        else
            estado = TOK_AcronimoPuntosDer;
        break;
    /**
     * Si es un punto a la derecha lo cogemos y seguimos, si es un delimitador nos
     * pasamos a los guiones
     */
    case TOK_AcronimoPuntosDer:
        if (c == '.')
        {
            ++numPuntosDerecha;
            estado = TOK_AcronimoFin;
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOK_Guion;
        break;
    /**
     * Si encontramos un punto a la derecha lo cogemos, Si encontramos un delimitador o letra
     * tokenizamos todo, si no es un delimitador seguimos analizando
     */
    case TOK_AcronimoPuntosDer2:
        if (c == '.')
        {
            ++numPuntosDerecha;
            estado = TOK_AcronimoPuntosDer3;
        }
        else if (!EsDelimitador(c, casoAnterior))
        {
            --numPuntosDerecha;
            estado = TOK_AcronimoPuntosDer4;
        }
        else
            estado = TOKENIZARacronimo;
        break;
    /**
     * Cogemos el punto a la derecha y seguimos analizando
     * si es un delimitador paramos y tokenizamos, sino es
     * delimitador pasamos a guiones
     */
    case TOK_AcronimoPuntosDer3:
        if (c == '.')
        {
            ++numPuntosDerecha;
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOKENIZARacronimo;
        else
            estado = TOK_Guion;
        break;
    /**
     * Si encontramos un punto a la derecha lo cogemos y seguimos analizando
     * si es un delimitador o los puntos a la derecha son mayores que 2 paramos y tokenizamos
     */
    case TOK_AcronimoPuntosDer4:
        if (c == '.')
        {
            ++numPuntosDerecha;
            estado = TOK_AcronimoPuntosDer2;
        }
        else if (EsDelimitador(c, casoAnterior) || numPuntosDerecha >= 2)
            estado = TOKENIZARacronimo;
        break;
    /**
     * Si encontramos otro punto dejamos de analizar y pasamos a guiones
     * sino es un punto restamos los puntos para no anadirlos al otkm
     */
    case TOK_AcronimoFin:
        if (c == '.' || EsDelimitador(c, casoAnterior) || numPuntosDerecha >= 2)
            estado = TOK_Guion;
        else
        {
            --numPuntosDerecha;
            estado = TOK_AcronimoPuntosDer4;
        }
        break;
    }
}

void Tokenizador::analizaCompuestas(char &c, int &estado, const string &frase, string::size_type &pos, string::size_type &npos, bool &salida,
                                    int &numGuionesDerecha, int &casoAnterior) const
{
    casoAnterior = estado;
    switch (estado)
    {
    /**Si encontramos un delimitador saltamos al estado de Tokenizar Normal
     * si encontramos cualquier otra cosa pasamos a analizar la palabra compuesta
     */
    case TOK_Guion:
        npos = pos;
        c = frase[npos];
        if (EsDelimitador(c, casoAnterior))
            estado = TOK_Normal;
        else
            estado = TOK_GuionPrimero;
        break;
    /**Si lo primero que encontramos es un guion pasamos al siguiente estado de los guiones
     * si encontramos un delimitador pasamos al estado de Tokenizar Normal
     */
    case TOK_GuionPrimero:
        if (c == '-')
            estado = TOK_GuionFinSiGuion;
        else if (EsDelimitador(c, casoAnterior))
            estado = TOK_Normal;
        break;
    /**Si volvemos a encontrar un guion o encontramos un delimitdor pasamos a
     * Tokenizar normal , por el contrario si encontramos cualquier otra cosa
     * seguimos analizando la palabra compuesta
     */
    case TOK_GuionFinSiGuion:
        if (c == '-' || EsDelimitador(c, casoAnterior))
            estado = TOK_Normal;
        else
            estado = TOK_Guion3;
        break;
        /**Si encontramos un guion sumamos 1 a nuestro contador y seguimos analizando
         * la palabra compuesta, si es un delimitador pasamos al estado de Tokenizar con guiones
         * como una palabra compuesta ya que tiene al menos un guion
         */
    case TOK_Guion3:
        if (c == '-')
        {
            ++numGuionesDerecha;
            estado = TOK_GuionFinOElimExtras;
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOKENIZARguion;
        break;
    /**Si encontramos un guion sumamos 1 a nuestro contador y seguimos analizando
     * si por el contrario encontramos un delimitador pasamos ya a tokenizar guion
     * en cualquier otro caso pasamos al estado 3
     */
    case TOK_GuionFinOElimExtras:
        if (c == '-')
        {
            ++numGuionesDerecha;
            estado = TOK_Guion5;
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOKENIZARguion;
        else
        {
            --numGuionesDerecha;
            estado = TOK_Guion3;
        }
        break;
        /**Si encontramos un guion sumamos 1 a nuestro contador y seguimos analizando
         * si por el contrario encontramos un delimitador pasamos ya a tokenizar guion
         * en cualquier otro caso pasamos a tokenizar normal
         */
    case TOK_Guion5:
        if (c == '-')
        {
            ++numGuionesDerecha;
            // estado = TOK_Guion4
        }
        else if (EsDelimitador(c, casoAnterior))
            estado = TOKENIZARguion;
        else
        {
            estado = TOK_Normal;
        }
    }
}

void Tokenizador::estadoNormal(char &c, int &estado, const string &frase, string::size_type &pos, string::size_type &npos, bool &salida,
                               int &numPuntoIzquierda, int &numPuntosDerecha, int &numGuionesDerecha, int &numArrobas, int &casoAnterior) const
{
    casoAnterior = estado;
    string delim = this->delimiters + " ";

    if (!EsDelimitador(frase[pos], casoAnterior))
    {
        // cout<<frase[pos]<<endl;
        // cout << delim << endl;
        npos = frase.find_first_of(delim, pos);
        // cout << npos << endl;
        estado = TOKENIZARnormal;
    }
    else
    {
        numPuntoIzquierda = 0;
        estado = TOK_URL_HTTP_FTTP;
        npos = pos;
        ++pos;
    }
}

void Tokenizador::UsandoCasosEspeciales(list<string> &tokens, const string &frase) const
{
    // Inicializamos el estado a las URL
    int casoEstamos = TOK_URL_HTTP_FTTP;
    int casoAnterior = -1;
    string delimitadores = delimiters + " ";
    // Caracter que vamos a analizar
    char caracter;
    string::size_type pos = 0;
    string::size_type npos = 0;
    // Token generado despues de la analizaci?n con la resta de las posiciones
    string token;
    // Parametro de salida del bucle cuando se acaba la frase
    bool salir = false;
    // Adiccion de informacion en los numeros reales decimales
    bool anadirCero = false;
    bool delimitadorRealEspecial = false;
    // Cantidad de puntos que nos saltamos o anadimos en el token
    int numPuntosIzquierda = 0;
    int numPuntosDerecha = 0;
    int numGuionesDerecha = 0;
    // Número de arrobas de los emails.
    int numArrobas = 0;

    // cout << frase << endl;

    if (frase.length() != 0)
    {
        while (!salir)
        {
            // Asignamos el barra 0 cuando nos pasamos de la longitud de la cadena para salirnos
            if (npos >= frase.length())
            {
                caracter = '\0';
            }
            else
            {
                caracter = frase[npos]; // Asignamos el caracter que vamos a analizar
                if (caracter == ' ')
                {
                    numArrobas = 0;
                }
            }

#if 0
            cout << "caracter: " << caracter << endl;
            cout << "Estado: " << casoEstamos << endl;
            cout << endl;
#endif
            // Automata de analisis de estados de la cadena
            switch (casoEstamos)
            {
            // Analisis y marcaje de URLs
            case TOK_URL_HTTP_FTTP:
                analizaURLHTTPFTP(caracter, casoEstamos, frase, pos, npos, salir, casoAnterior);
                break;
            case TOK_URL:
                analizaURLyMarcaTokeniza(npos, frase, casoEstamos, casoAnterior);
                break;

            // Analisis de n?meros reales
            case TOK_Real:
            case TOK_AnadeCero:
            case TOK_Real2:
            case TOK_Real3:
            case TOK_Real4:
                analizaReal(caracter, casoEstamos, frase, pos, npos, salir, delimitadorRealEspecial, anadirCero, casoAnterior);
                break;

            // Analisis de emails
            case TOK_Email:
            case TOK_EmailArroba:
            case TOK_EmailSaleOTokeniza:
                analizaEmail(caracter, casoEstamos, frase, pos, npos, salir, numArrobas, casoAnterior);
                break;

            // Analisis de acronimos
            case TOK_Acronimo:
            case TOK_AcronimoDelimExit:
            case TOK_AcronimoPuntosDer:
            case TOK_AcronimoPuntosDer2:
            case TOK_AcronimoPuntosDer3:
            case TOK_AcronimoPuntosDer4:
            case TOK_AcronimoFin:
                analizaAcronimo(caracter, casoEstamos, frase, pos, npos, salir, numPuntosIzquierda, numPuntosDerecha, casoAnterior);
                break;

            // Analisis de palabras compuestas
            case TOK_Guion:
            case TOK_GuionPrimero:
            case TOK_GuionFinSiGuion:
            case TOK_Guion3:
            case TOK_GuionFinOElimExtras:
            case TOK_Guion5:
                analizaCompuestas(caracter, casoEstamos, frase, pos, npos, salir, numGuionesDerecha, casoAnterior);
                break;

            // Si el caracter por el que vamos no es un delimi
            case TOK_Normal:
                estadoNormal(caracter, casoEstamos, frase, pos, npos, salir, numPuntosIzquierda, numGuionesDerecha, numGuionesDerecha, numArrobas, casoAnterior);
                break;
            }
            // Casos de tokenizacion y adicion de informacion a tokens
            switch (casoEstamos)
            {
            case TOKENIZARnormal:
#if 0
                cout<< "TOKENIZARnormal" << endl;
                cout << frase.substr(pos, npos - pos) << endl;
                cout << "-----" << endl;
#endif
                token = frase.substr(pos, npos - pos);
                break;
            case TOKENIZARreal:
#if 0
                cout<< "TOKENIZARreal" << endl;
                cout << frase.substr(pos, npos - pos) << endl;
                cout << "-----" << endl;
#endif
                if (!anadirCero)
                    token = frase.substr(pos, npos - pos);
                else
                    token = "0" + frase.substr(pos, npos - pos);

                if (delimitadorRealEspecial)
                    --npos;
                break;
            case TOKENIZARacronimo:
#if 0
                cout<< "TOKENIZARacronimo" << endl;
                cout << frase.substr(pos, npos - pos) << endl;
                cout << "-----" << endl;
#endif
                token = frase.substr(pos + numPuntosIzquierda, (npos - numPuntosDerecha) - (pos + numPuntosIzquierda));
                break;
            case TOKENIZARguion:
#if 0
                cout << "TOKENIZARguion" << endl;
                cout << frase.substr(pos, (npos)-pos) << endl;
                cout << "-----" << endl;
                cout << numGuionesDerecha << endl;

#endif
                if (numGuionesDerecha == 0 || this->delimiters.find("-") != string::npos)
                {
                    // cout << "Entra en el if" << endl;
                    token = frase.substr(pos, (npos)-pos);
                    if (numGuionesDerecha != 0)
                        token = frase.substr(pos, (npos - numGuionesDerecha) - pos);
                }
                else
                    token = frase.substr(pos, (npos + numGuionesDerecha) - pos);

                if (token.find(" ") != string::npos)
                    token = token.substr(0, token.find(" "));

                break;
            }

            // cout << token << endl;

            // Metemos el token en la lista, pasanado a minusculas si es necesario
            if (casoEstamos >= 0 && casoEstamos <= 3)
            {
                // Antes de meterlo lo pasamos a minusculas
                if (this->pasarAminuscSinAcentos)
                    tokens.push_back(normalizaAcentosMinusculas(token));
                else
                    tokens.push_back(token);

                // Reseteamos los valores
                pos = npos + 1;
                anadirCero = false;
                delimitadorRealEspecial = false;
                numPuntosIzquierda = 0;
                numPuntosDerecha = 0;
                numGuionesDerecha = 0;
                // numArrobas = 0;
                casoEstamos = TOK_URL_HTTP_FTTP;

                if (npos >= frase.length() || frase[npos] == '\0')
                    salir = true;
            }
            if (npos != string::npos)
                ++npos; // Pasamos a la siguiente letra del string
        }
    }
}
