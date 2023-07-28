#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

/**
 * @author Daniel Asensi Roch 48776120C
 * Potter.cc
 */

//Estrucutura que almacena los datos del problema
struct TDatos
{
    //Tiempo    Precio  Maximas
    vector<long> t, v, m;
    long T, n;
};

//Estructura que almacena los datos de la solución
struct TSolucion
{
    vector<long> x;
    long valorAcumulado;
    long tiempoAcumulado;
};

/**
 * Argumentos:
 *          --ignore-naive : no se mostra la ingenua
            -f: el siguiente argumento será el fichero a leer
            -t: muesta memoización y Iterativa
 **/
bool lecturaFichero(string fichero, TDatos &dp);
bool procesaArgumentos(int argc, char *argv[], bool &t, string &fichero, bool &ignoreActive);
long recursivoAlmacen(int n, long T);
long recursivoNaive(int n, long T);
long iterativaAlmacen();
long iterativaAlmacenMejor();
void impresoraAlmacen(const vector<vector<long>> unAlmacen);
void SolveMyShit();
/**
 * @brief Variable global para los datos del problema y el almacen
 * 
 */
TDatos datosProblem;                    //Los datos que tendrán todos los algoritmos
vector<vector<long>> almacen;           //Almacen generado por recursivoAlmacen
vector<vector<long>> solu;              //Solucion generada iterativos
vector<vector<long>> almacenItera;      //Solucion generada iterativos
vector<vector<long>> mejorAlmacenItera; //Solucion generada iterativos
vector<long> solucionTotal;

const long minusInf = numeric_limits<long>::min(); // -infinito
bool okFich;                                       //Fichero
/**
 * @brief El main que realizará la estructura del programa y activará
 * las funciones dependiendo de los parametros de entrada
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    string fichero;
    bool ignoreActive, imprimeMatriz;

    if (procesaArgumentos(argc, argv, imprimeMatriz, fichero, ignoreActive))
    {
        if (okFich)
        {
            if (!ignoreActive)
            {
                cout << recursivoNaive(datosProblem.n - 1, datosProblem.T) << " ";
            }

            //Inicializamos el almacenes y Soluciones
            almacen = vector<vector<long>>(datosProblem.n, vector<long>(datosProblem.T + 1, -1));
            solu = vector<vector<long>>(datosProblem.n, vector<long>(datosProblem.T + 1, -1));
            almacenItera = vector<vector<long>>(datosProblem.n, vector<long>(datosProblem.T + 1, -1));
            mejorAlmacenItera = vector<vector<long>>(datosProblem.n, vector<long>(datosProblem.T + 1, -1));

            cout << recursivoAlmacen(datosProblem.n - 1, datosProblem.T);
            cout << " "; //Aqui va solución iterativa 1;
            cout << iterativaAlmacen();
            mejorAlmacenItera = almacenItera;
            cout << " "; //Aqui va solución iterativa 2;
            cout << iterativaAlmacenMejor();
            cout << endl;

            SolveMyShit();

            if (imprimeMatriz) //Si activamos el argumento -t
            {
                cout << "Memoization matrix: " << endl;
                impresoraAlmacen(almacen);
                ////////////////////////////////////////
                cout << "Iterative matrix: " << endl;
                impresoraAlmacen(almacenItera); //Aqui tengo que poner la matriz Iterativa
            }
        }
    }
    return 0;
}

/**
 * @brief Leera el fichero y meterá los datos en las estructuras
 * 
 * @param fichero para abrir y leer
 * @return true 
 * @return false 
 */
bool lecturaFichero(string fichero)
{
    bool abreFichero = false;
    ifstream fich;
    long aux;
    fich.open(fichero.c_str());

    if (fich.is_open())
    {
        abreFichero = true;
        //Leemos la cantidad de elementos
        fich >> datosProblem.n >> datosProblem.T;
        //Leemos el primer vector
        for (int i = 1; i <= datosProblem.n; i++)
        {
            fich >> aux;
            datosProblem.t.push_back(aux);
        }
        //Leemos el segundo vector
        for (int i = 1; i <= datosProblem.n; i++)
        {
            fich >> aux;
            datosProblem.v.push_back(aux);
        }
        //Leemos el tercer vector
        for (int i = 1; i <= datosProblem.n; i++)
        {
            fich >> aux;
            datosProblem.m.push_back(aux);
        }
    }
    else
    {
        cout << "ERROR: can’t open file: " << fichero << endl;
    }

    return abreFichero;
}

/**
 * @brief Procesador de argumentos 
 * 
 * @param argc Cantidad de argumentos
 * @param argv vector de argumentos 
 * @param arguoks argumentos bien?
 * @param fichero fichero a leer
 * @param ignoreActive se muestra la ingenua?
 * @return true están bien los argmentos
 * @return false están mal los argumentos
 */
bool procesaArgumentos(int argc, char *argv[], bool &t, string &fichero, bool &ignoreActive)
{
    bool oks = true;

    if (argc == 1) //Solo tenemos un argumento por lo que esta mal
    {
        oks = false;
        cout << "ERROR: missing filename." << endl;
        cout << "Usage: " << endl;
        cout << "potter [-t] [--ignore-naive] -f file";
    }
    else //Cuando tengamos más de un argumento∫
    {
        for (int i = 1; i < argc && oks; i++)
        {
            string s = argv[i];

            if (s == "--ignore-naive")
                ignoreActive = true;
            else
            {
                if (s == "-t")
                    t = true; //Mostraremos las tablas
                else
                {
                    if (s == "-f")
                    {
                        if (i + 1 < argc)
                        {
                            fichero = argv[i + 1]; //Sacamos el nombre del fichero
                            i++;                   //Para saltarnos nombre del fichero
                            okFich = lecturaFichero(fichero);
                        }
                        else
                        {
                            //Si despues de la -f no se encuentra un fichero leible lanzamos el error
                            oks = false;
                            cout << "ERROR: missing filename." << endl;
                            cout << "Usage: potter [-t] [--ignore-naive] -f file" << endl;
                        }
                    }
                    else if (s != "--ignore-naive" || s != "-t" || s != "-f")
                    {
                        cout << "ERROR: unkown option " << s << endl;
                        cout << "Usage: potter [-t] [--ignore-naive] -f file" << endl;
                        oks = false; //Para que solo muestre un mensaje de error
                    }
                }
            }
        }
    }

    return oks;
}

/**
 * @brief Dará la mejor solución utilizando backTracking
 * 
 * @param datosProblem 
 * @param n 
 * @param T 
 * @return long 
 */
long recursivoNaive(int n, long T)
{
    long actual, bestOne;
    if (n == -1 || T == 0)
        bestOne = 0;
    else
    {
        bestOne = minusInf;                                                         //Inicializamos el mejor a -infinito
        for (long i = 0; i <= datosProblem.m[n] && i * datosProblem.t[n] <= T; i++) //Recorremos los objetos del potter
        {
            //Volvemos a llamar a la función para el soguiente objeto
            actual = recursivoNaive(n - 1, T - i * datosProblem.t[n]) + datosProblem.v[n] * i;
            //Adjudicamos el mejor valor
            if (actual > bestOne)
                bestOne = actual;
        }
    }
    //Devolvemos el mejor valor que luego iremos comparando con los siguientes
    return bestOne;
}

/**
 * @brief Realizará el recursivo con almacen
 *        genereando un almacen de soluciones que al recorrer escogerá
 *        la mejor opción.
 * @param n cantidad elementos
 * @param T 
 * @return long la mejor opción
 */
long recursivoAlmacen(int n, long T)
{
    long respuesta, bestOne;
    int mejorIteracion;

    //Caso base
    if (n == -1)
    {
        return 0;
    }
    else
    {
        if (almacen[n][T] == -1)
        {
            bestOne = minusInf;
            //Recorremos la varible global donde tenemos
            //los datos del problema
            for (int i = 0; i <= datosProblem.m[n]; i++)
            {
                if (i * datosProblem.t[n] <= T)
                {
                    //Realizamos otra llamada para el siguiente caso
                    respuesta = recursivoAlmacen(n - 1, T - i * datosProblem.t[n]) + datosProblem.v[n] * i;
                    //Devolvemos el mejor
                    if (respuesta > bestOne)
                    {
                        mejorIteracion = i;
                        bestOne = respuesta;
                    }
                }
            }
            almacen[n][T] = bestOne; //Metemos la respuesta en el almacen
            //Construimos la solución
            solu[n][T] = mejorIteracion;
        }
        //Una vez llegamos al caso base devolvemos el almacén
        return almacen[n][T];
    }
}
/**
 * @brief Obtendrá las soluciones dependiendo de los datos pasados 
 * en el almacen recursivo y imprimirá los resultados por pantalla
 * 
 */
void SolveMyShit()
{
    int T;
    long answer = 0;
    vector<long> s(datosProblem.n);

    T = datosProblem.T;
    for (int i = datosProblem.n - 1; i >= 0; i--)
    {
        s[i] = solu[i][T];
        T = T - s[i] * datosProblem.t[i];
    }

    for (long unsigned int i = 0; i < s.size(); i++)
    {
        cout << s[i] << " ";
        answer += s[i] * datosProblem.t[i];
    }
    cout << endl;
    cout << answer << endl;
}
/**
 * @brief Realiza el almacen de manera iterativa
 * 
 * @return long devuelve el mejor valor del almacen
 */
long iterativaAlmacen()
{
    long mejorResultado;
    int i, t, n;

    //Rellenamos la primera columna
    for (i = 0; i < datosProblem.n; i++)
        almacenItera[i][0] = 0;

    //La primera fila
    for (t = 1; t <= datosProblem.T; t++)
    {
        if ((t / datosProblem.t[0]) < (datosProblem.m[0]))
            i = t / datosProblem.t[0];
        else
            i = datosProblem.m[0];

        almacenItera[0][t] = i * datosProblem.v[0];
    }

    for (n = 1; n < datosProblem.n; n++)
    {
        for (t = 1; t <= datosProblem.T; t++)
        {
            mejorResultado = minusInf;
            for (i = 0; i <= datosProblem.m[n]; i++)
            {
                if (datosProblem.t[n] * i <= t)
                {
                    if (mejorResultado > almacenItera[n - 1][t - datosProblem.t[n] * i] + datosProblem.v[n] * i)
                        mejorResultado = mejorResultado;
                    else
                        mejorResultado = almacenItera[n - 1][t - datosProblem.t[n] * i] + datosProblem.v[n] * i;
                }
            }
            almacenItera[n][t] = mejorResultado;
        }
    }
    return almacenItera[datosProblem.n - 1][datosProblem.T];
}

/**
 * @brief Realizará el iterativo del mejor Almacen utilizando el almacen anterios
 * 
 * @return long devuelve el mejor valor
 */
long iterativaAlmacenMejor()
{
    long mejorResultado;
    int i, t, n;

    //Rellenamos la primera columna
    for (i = 0; i < datosProblem.n; i++)
        mejorAlmacenItera[i][0] = 0;

    //La primera fila
    for (t = 1; t <= datosProblem.T; t++)
    {
        if ((t / datosProblem.t[0]) < (datosProblem.m[0]))
            i = t / datosProblem.t[0];
        else
            i = datosProblem.m[0];

        mejorAlmacenItera[0][t] = i * datosProblem.v[0];
    }

    for (n = 1; n < datosProblem.n; n++)
    {
        for (t = 1; t <= datosProblem.T; t++)
        {
            mejorResultado = minusInf;
            for (i = 0; i <= datosProblem.m[n]; i++)
            {
                if (datosProblem.t[n] * i <= t)
                {
                    if (mejorResultado > (mejorAlmacenItera[n % 2][t - datosProblem.t[n] * i]) + datosProblem.v[n] * i)
                        mejorResultado = mejorResultado;
                    else
                        mejorResultado = (mejorAlmacenItera[n % 2][t - datosProblem.t[n] * i]) + datosProblem.v[n] * i;
                }
            }
            mejorAlmacenItera[n % 2][t] = mejorResultado;
        }
    }
    return mejorAlmacenItera[datosProblem.n - 1][datosProblem.T];
}
/**
 * @brief Imprimira un almacen pasado como parámetro
 * 
 * @param unAlmacen almacen de vector de enteros
 */
void impresoraAlmacen(const vector<vector<long>> unAlmacen)
{
    for (long unsigned int i = 0; i < unAlmacen.size(); i++)
    {
        for (long unsigned int j = 0; j < unAlmacen[i].size(); j++)
        {
            if (unAlmacen[i][j] != -1)
            {
                cout << unAlmacen[i][j];
            }
            else
            {
                cout << "-";
            }
            if (j == unAlmacen[i].size() - 1)
                true;
            else
                cout << " ";
        }
        cout << endl;
    }
}