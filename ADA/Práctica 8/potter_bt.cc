#include <iostream>
#include <fstream>
#include <cstring>
#include <numeric>
#include <math.h>
#include <vector>
#include <ctime>
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
    vector<int> m;
    vector<int> v;
    vector<double> t;
    double T;
    int n;
};

string fichero;
bool ficheroLeido;
//SI trabajo con variables globales se acelera la ejecución del programa :O
TDatos datosOrdenados;


long long todos = 0, noSonHoja = 0, podados = 0, factibles = 0, visitados = 0, noFactibles = 0;

bool procesaArgumentos(int argc, char *argv[], TDatos &datosProblem);
bool lecturaFichero(TDatos &datosProblem);
double potterDatosMejorValor(TDatos &datosProblem);
void PotterHaciasLasHojas(int k, vector<int> &veces, double t_h, double v_h, long &mejorVal);
double potterGreedy(const TDatos &dp);
double min(double x, double y);

int main(int argc, char *argv[])
{
    unsigned t0, t1;
    t0 = clock();
    TDatos datosProblem;

    if (procesaArgumentos(argc, argv, datosProblem))
    {
        //Si los datos se leen con exito empezamos a hacer algoritmo
        if (ficheroLeido)
        {
            cout << potterDatosMejorValor(datosProblem) << endl;
            //generados factibles visitados noFactibles podados
            cout << todos << " " << factibles << " " << visitados << " " << noFactibles << " " << podados << endl;
            t1 = clock();
            double time = 1000 * (double(t1 - t0) / CLOCKS_PER_SEC);
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
    datosOrdenados.v = vector<int>(datosProblem.n);
    datosOrdenados.t = vector<double>(datosProblem.n);
    datosOrdenados.m = vector<int>(datosProblem.n);
    //Ordenamos los datos y adjudicamos si indice
    for (unsigned long int i = 0; i < indiceX.size(); i++)
    {
        datosOrdenados.v[i] = datosProblem.v[indiceX[i]];
        datosOrdenados.t[i] = datosProblem.t[indiceX[i]];
        datosOrdenados.m[i] = datosProblem.m[indiceX[i]];
    }

    mejorVal = potterGreedy(datosOrdenados);
    PotterHaciasLasHojas(0, decisiones, 0, 0, mejorVal);

    return mejorVal;
}

double potterGreedy(const TDatos &dp)
{
    auto criterio = [dp](size_t x, size_t y) -> bool
    { return dp.v[x] / dp.t[x] > dp.v[y] / dp.t[y]; };
    vector<size_t> idx(dp.n);
    double T = dp.T;
    vector<int> x(dp.n, 0); // vector de veces.
    double sol;
    int veces;

    // vector de indices.
    for (int i = 0; i < idx.size(); i++)
    {
        idx[i] = i;
    }
    sort(idx.begin(), idx.end(), criterio); // vector que contiene el orden en el que tengo que comprobar los elementos.

    sol = 0;
    int i = 0, indice;
    while (i < idx.size() && T > 0)
    {
        indice = idx[i];
        veces = min(trunc(T / dp.t[indice]) /*calculaVeces(T, ordenados[i].t)*/, dp.m[indice]);
        T = T - (dp.t[indice] * veces);
        sol += (dp.v[indice] * veces);
        i++;
    }
    return sol;
}

void PotterHaciasLasHojas(int k, vector<int> &veces, double t_h, double v_h, long &mejorVal)
{
    //Cada vez que entramos a esta función de manera recursiva generamos un nodo por eso incrementamos el total
    todos++;
    if (k == datosOrdenados.n)
    {
        //Cada vez que visitamos un nodo es que actualizamos el mejor valor
        visitados++;
        mejorVal = v_h;
        return;
    }

    //Recorremos los nodos
    for (int j = 0; j <= datosOrdenados.m[k]; j++)
    {
        int k2 = k + 1;
        veces[k] = j;
        double new_t = t_h + veces[k] * datosOrdenados.t[k];
        double new_v = v_h + veces[k] * datosOrdenados.v[k];
        double recortado = 0;

        if (new_t < datosOrdenados.T)
        {
            //Si el tamaño es menor o igual es que es un nodo factible a mejor solución
            factibles++;
            double susti = datosOrdenados.T - new_t;

            //Procedemos a recorrer el nodo y comprobar si debemos de podarlo o no
            while (susti > 0 && k2 < datosOrdenados.n)
            {
                if (datosOrdenados.t[k2] * datosOrdenados.m[k2] <= susti)
                {
                    recortado = recortado + datosOrdenados.v[k2] * datosOrdenados.m[k2];
                    susti -= datosOrdenados.t[k2] * datosOrdenados.m[k2];
                    //Voy sumando profundidades para ver si tengo que recortar o no
                    k2++;
                }
                else
                {
                    recortado = recortado + datosOrdenados.v[k2] * susti / datosOrdenados.t[k2];
                    susti = 0;
                }
            }
            //Si resulta que es mejor que el mejorValor añadimos el nodo y actualizamos la mejor solución mediante la llamada recursiva
            if ((new_v + recortado) > mejorVal)
            {
                PotterHaciasLasHojas(k + 1, veces, new_t, new_v, mejorVal);
            }
            else
            {
                //SI no se poda el nodo ya que no nos hace falta
                podados++;
            }
        }
        else
        {
            //En el caso de que no se factible el nodo en el que estamos no se hace nada de esto y directamente se pasa de el
            noFactibles++;
        }
    }
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
        datosProblem.v = vector<int>(datosProblem.n);
        datosProblem.m = vector<int>(datosProblem.n);
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
    //cout<<podados<<factibles<<generados;

    return abreFichero;
}

double min(double x, double y){
	double m;
	if(x <= y){
		m = x;
	}
	else{
		m = y;
	}
	return m;
}