#include <iostream>
#include <fstream>
#include <cstring>
#include <numeric>
#include <math.h>
#include <vector>
#include <ctime>
#include <queue>
//Esta librería contiene el algoritmo Sort we need it
#include <algorithm>
using namespace std;

/**
 * @brief Estrucutura para los datos del problemas
 * con los tiempos y la cantidad de elementos
 * 
 */
struct TDatos
{
    vector<long> m;   //Maximas copias realizables
    vector<long> v;   //Precio
    vector<double> t; //tiempo de realización (peso)
    double T; //tiempo maximo
    long n; //Cantidad objetos
};

//Variables Globales definidas para el correcto funcionamiento del codigo
string fichero;
bool ficheroLeido;
//SI trabajo con variables globales se acelera la ejecución del programa
TDatos datosOrdenados;
long hojas = 0;
long descartados = 0;
long explorados = 0;
long visitados = 0;
long actualizadosCompletos = 0;
long actualizadosNoCompletos = 0;
long noPrometedores = 0;
long noFactibles = 0;

//Prototipos de las funciones para la correcta lectura del codigo
bool lecturaFichero(TDatos &datosProblem);
bool procesaArgumentos(int argc, char *argv[], TDatos &datosProblem);
double potterDatosMejorValor(TDatos &datosProblem);
double potterSolucionTotal();
double vorazMochilaDiscreta(const TDatos &datos, long iteracion, double tiempo);
double vorazMochilaContinua(const TDatos &datos, long iteracion, double tiempo);

int main(int argc, char *argv[])
{
    unsigned t0, t1;
    t0 = clock();
    //Utilizamos esta variable ya que al
    TDatos datosProblem;

    if (procesaArgumentos(argc, argv, datosProblem))
    {
        //Si los datos se leen con exito empezamos a hacer algoritmo
        if (ficheroLeido)
        {
            double mejorValor = potterDatosMejorValor(datosProblem);
            t1 = clock();
            double time =1000 * (double(t1 - t0) / CLOCKS_PER_SEC);
            cout << mejorValor << endl;

            cout << visitados << " " << explorados << " " << hojas << " " << noFactibles << " " << noPrometedores << " " << descartados << " " << actualizadosCompletos << " " << actualizadosNoCompletos << endl;

            cout << time;
        }
    }
    else
    {
        cout << "Error at the arguments please use: -f file" << endl;
    }

    return 0;
}

double potterDatosMejorValor(TDatos &datosProblem)
{
    long mejorVal = 0;
    vector<size_t> indiceX(datosProblem.n);

    vector<int> decisiones(datosProblem.n);
    //Lambda de ordenación igual que el Boraz
    auto ordenacion = [datosProblem](size_t x, size_t y) -> bool
    { return datosProblem.v[x] / datosProblem.t[x] > datosProblem.v[y] / datosProblem.t[y]; };

    //Iota asigna valores de manera ordenada desde el principio hasta el final del vector que le pases de manera sucesiva
    iota(indiceX.begin(), indiceX.end(), 0);
    sort(indiceX.begin(), indiceX.end(), ordenacion);

    datosOrdenados.n = datosProblem.n;
    datosOrdenados.T = datosProblem.T;
    //Inicializamos los vectores
    datosOrdenados.v = vector<long>(datosProblem.n);
    datosOrdenados.t = vector<double>(datosProblem.n);
    datosOrdenados.m = vector<long>(datosProblem.n);
    //Con los datos  adjudicamos seguún su indice
    for (unsigned long int i = 0; i < indiceX.size(); i++)
    {
        datosOrdenados.v[i] = datosProblem.v[indiceX[i]];
        datosOrdenados.t[i] = datosProblem.t[indiceX[i]];
        datosOrdenados.m[i] = datosProblem.m[indiceX[i]];
    }

    //Aqui metemos la nueva función con los datos Ordenados ya por nuestra función lambda
    mejorVal = potterSolucionTotal();

    return mejorVal;
}

/**
 * @brief Funcion a la que le pasamos la estructura con los datos ordenados
 * siguiendo la funcion datosProblem.v[x] / datosProblem.t[x] > datosProblem.v[y] / datosProblem.t[y];
 * aquí realizaremos la solución optimista y pesimista[Boraz]
 * 
 * @return double 
 */
double potterSolucionTotal()
{
    typedef vector<long> soluciones;
    //Estructura de datos para guardas los nodos
    typedef tuple<double, double, double, soluciones, unsigned> Nodo;
    //Cola de Nodos
    priority_queue<Nodo> colaNodos;

    double mejorValor = vorazMochilaDiscreta(datosOrdenados, 0, datosOrdenados.T);

    double nodoInicial = vorazMochilaContinua(datosOrdenados, 0, datosOrdenados.T);

    //Metemos el nodoinicial en la cola de prioridad de nodo
    colaNodos.emplace(nodoInicial, 0, 0, soluciones(datosOrdenados.n), 0);
    while (colaNodos.empty() == false)
    {
        //Cabeza de la cola
        auto [optimista, valor, tiempo, x, k] = colaNodos.top();
        //Vamos sacando nodos de la cola

        colaNodos.pop();
        //Comprobamos si hemos llegado a una hoja
        if (k == datosOrdenados.n)
        {
            hojas++;
            //Si encontramos un valor mejor lo actualizamos
            if (mejorValor < valor)
                mejorValor = valor;
            continue; //Pasamos al siguiente nodo
        }

        //Descartamos el nodo si la cota optimista es menor que el mejor valor actual
        if (optimista < mejorValor)
        {
            descartados++;
            continue; //Pasamos al siguiente nodo
        }

        if (k == datosOrdenados.n - 1)
            hojas++;
        else
            explorados++;

        //Pasamos ahora analizar las maximas
        for (unsigned long int j = 0; j <= datosOrdenados.m[k]; j++)
        {
            visitados++;
            x[k] = j;
            //Adjudicamos los nuevos tiempos y nuevos valores que luego comparearemos
            double nuevoTiempo = tiempo + x[k] * datosOrdenados.t[k];
            double nuevoValor = valor + x[k] * datosOrdenados.v[k];

            if (nuevoTiempo <= datosOrdenados.T) //El nodo es factible
            {
                //Ahora probamos a mejorar el ultimo valor que teniamos
                //Mediante el uso de la mochila Discreta
                double valorViejo = mejorValor;
                mejorValor = max(mejorValor, nuevoValor + vorazMochilaDiscreta(datosOrdenados, k + 1, datosOrdenados.T - nuevoTiempo));
                //Si el nuevo valor es diferente debemos incrementar los actualizados completos y no completos cuando sea k  = al número objetos -1
                if (valorViejo != mejorValor)
                {
                    if (k == datosOrdenados.n - 1)
                        actualizadosCompletos++;
                    else
                        actualizadosNoCompletos++;
                }
                //Conseguimso el nuevo valor Optimista que luego compararemos
                optimista = nuevoValor + vorazMochilaContinua(datosOrdenados, k + 1, datosOrdenados.T - nuevoTiempo);
                //Si este es mejor que el mejorValor meteremos el nodo en la cola
                //SI VEMOS QUE EL NODO PUEDE CONTENER LA MEJOR SOLUCION LO METEMOS EN LA COLA!!
                if (optimista > mejorValor)
                    colaNodos.emplace(optimista, nuevoValor, nuevoTiempo, x, k + 1); 
                else
                    noPrometedores++;//En caso contrario la rama explorada no es prometedora y se descarta
            }
            else
            {
                noFactibles++;
            }
        }
    }
    return mejorValor;
}

double vorazMochilaContinua(const TDatos &datos, long iteracion, double tiempo)
{
    double solucion = 0;
    double tiempoQueda = tiempo;
    unsigned long i;

    for (i = iteracion; i < datos.n; i++)
    {
        if (tiempoQueda > 0)
        {
            //Si todavía podemos ir cogiendo nodos continuamos
            if (datos.t[i] * datos.m[i] <= tiempoQueda)
            {
                solucion += datos.v[i] * datos.m[i];
                tiempoQueda -= datos.t[i] * datos.m[i];
            }
            else //No nos queda tiemp para meter más objetos
            {
                solucion += datos.v[i] * tiempoQueda / datos.t[i];
                tiempoQueda = 0;
            }
        }
    }
    return solucion;
}

/**
 * @brief La forma en que podemos seleccionar n objetos
 *  con peso pi y valor vi para cargarlos en una mochila
 *  con un peso máximo P de tal forma que obtengamos el valor
 *  máximo V
 * 
 * @param datos 
 * @param iteracion 
 * @param tiempo 
 * @return double 
 */
double vorazMochilaDiscreta(const TDatos &datos, long iteracion, double tiempo)
{
    double solucion = 0;
    double tiempoQueda = tiempo;
    unsigned long i;
    long caben = 0;

    for (i = iteracion; i < datos.n; i++)
    {
        if (tiempoQueda > 0)
        {
            if (datos.m[i] <= trunc(tiempoQueda / datos.t[i]))
                caben = datosOrdenados.m[i];
            else
                caben = trunc(tiempoQueda / datosOrdenados.t[i]);
            solucion += datosOrdenados.v[i] * caben;
            tiempoQueda -= datosOrdenados.t[i] * caben;
        }
    }
    return solucion;
}

/**
 * @brief Procesará los argumentos para controlar si se ha pasado el file
 * 
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return true bien 
 * @return false mal
 */
bool procesaArgumentos(int argc, char *argv[], TDatos &datosProblem)
{
    bool oks = true;

    if (argc == 1) //recortadoo tenemos un argumento por lo que esta mal
    {
        oks = false;
        cout << "ERROR: missing filename." << endl;
    }
    else //Cuando tengamos más de un argumento∫
    {
        for (int i = 1; i < argc && oks; i++)
        {
            string s = argv[i];

            if (s == "-f")
            {
                if (i + 1 < argc)
                {
                    fichero = argv[i + 1]; //Sacamos el nombre del fichero
                    i++;                   //Para saltarnos nombre del fichero
                    ficheroLeido = lecturaFichero(datosProblem);
                }
                else
                {
                    //Si despues de la -f no se encuentra un fichero leible lanzamos el error
                    oks = false;
                    cout << "ERROR: missing filename." << endl;
                    cout << "Usage: -f file" << endl;
                }
            }
        }
    }
    return oks;
}

/**
 * @brief Leera el fichero para poder realizar las operaciones
 * 
 * @param datosProblem datos de problema
 * @return true 
 * @return false 
 */
bool lecturaFichero(TDatos &datosProblem)
{
    bool abreFichero = false;
    ifstream fich;

    fich.open(fichero.c_str());

    if (fich.is_open())
    {
        abreFichero = true;
        //Leemos la cantidad de elementos
        fich >> datosProblem.n >> datosProblem.T;

        //Incializamos los vectores para añadirlos a la estructura de datos
        datosProblem.v = vector<long>(datosProblem.n);
        datosProblem.m = vector<long>(datosProblem.n);
        datosProblem.t = vector<double>(datosProblem.n);
        //Leemos el primer vector
        for (int i = 0; i < datosProblem.n; i++)
        {
            fich >> datosProblem.t[i];
            //cout << datosProblem.t[i] << " ";
        }
        //cout << endl;
        //Leemos el segundo vector
        for (int i = 0; i < datosProblem.n; i++)
        {
            fich >> datosProblem.v[i];
            //cout << datosProblem.v[i] << " ";
        }
        //cout << endl;
        //Leemos el tercer vector
        for (int i = 0; i < datosProblem.n; i++)
        {
            fich >> datosProblem.m[i];
            //cout << datosProblem.m[i] << " ";
        }
        //cout << endl;
    }
    else
    {
        //Por si no podemos abrir el fichero
        cout << "ERROR: can’t open file: " << fichero << endl;
    }

    fich.close(); //Hay que cerrar el fichero

    return abreFichero;
}