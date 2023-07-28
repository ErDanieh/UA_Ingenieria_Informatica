#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include <vector>
//Esta librería contiene el algoritmo QuickSort we need it
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
    vector<float> t;
    double T;
    int n;
};

/**
 * @brief Variables globales para los datos, el fichero
 * y conocer si el fichero ha sido leido
 */
string fichero;
bool ficheroLeido;
vector<int> solve;

bool lecturaFichero(TDatos &datosProblem);
bool procesaArgumentos(int argc, char *argv[], TDatos &datosProblem);
void algoritmoBoraz(TDatos &datosProblem);
void solucionesImpresora(TDatos datos);

int main(int argc, char *argv[])
{
    TDatos datosProblem;

    if (procesaArgumentos(argc, argv, datosProblem))
    {
        //Si los datos se leen con exito empezamos a hacer algoritmo
        if (ficheroLeido)
        {
            //Modificamos la variable global
            algoritmoBoraz(datosProblem);
        }
    }
    else
    {
        cout << "Error at the arguments please use: -f file" << endl;
    }

    return 0;
}

/**
 * @brief Imprimirá el vector de las soluciones
 *      
 * @param datos datos del problema 
 */
void solucionesImpresora(TDatos datos)
{
    double tiempoTotal = 0;
    long solucionValores = 0;

    //Bucle para conseguir la solución total de los valores y el tiempo
    for (unsigned long int i = 0; i < solve.size(); i++)
    {
        //multiplicamos la solución por el coste
        solucionValores = solucionValores + datos.v[i] * solve[i];
        //multiplicamos el coste por el tiempo
        tiempoTotal = tiempoTotal + datos.t[i] * solve[i];
    }
    cout << solucionValores << endl;
    //Imprimimos las soluciones de los objetos
    for (unsigned long int i = 0; i < solve.size(); i++)
    {
        cout << solve[i] << " ";
    }
    cout << endl;
    cout << tiempoTotal << endl;
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
        datosProblem.t = vector<float>(datosProblem.n);
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

    if (argc == 1) //Solo tenemos un argumento por lo que esta mal
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
 * @brief Realizará el algoritmo boraz con los datos leidos del fichero
 * 
 * @param datosProblem Datos del fichero
 */
void algoritmoBoraz(TDatos &datosProblem)
{

    /**
     * @brief Explicación para futuro:
     *  A una función lambda no le podemos pasar una variable global 
     *  ya que esta variable no es de tipo estático
     */
    auto ordenacion = [datosProblem](size_t x, size_t y) -> bool { return datosProblem.v[x] / datosProblem.t[x] > datosProblem.v[y] / datosProblem.t[y]; };
    vector<size_t> indiceX(datosProblem.n);
    double Tiempos = datosProblem.T;
    vector<int> veces(datosProblem.n, 0);

    for (long unsigned int i = 0; i < indiceX.size(); i++)
    {
        indiceX[i] = i;
    }

    //Ordenamos el vector
    sort(indiceX.begin(), indiceX.end(), ordenacion);

    //Inicializamos los indices y la variable por la que vamos
    long unsigned int i = 0, indice;

    while (i < indiceX.size() && Tiempos > 0)
    {
        indice = indiceX[i];

        //Tenemos que realizar el truncamiento de la división para obtener el optimo
        if ((trunc(Tiempos / datosProblem.t[indice]) <= datosProblem.m[indice])) veces[indice] = (trunc(Tiempos / datosProblem.t[indice]));
        else veces[indice] = datosProblem.m[indice];

        Tiempos = Tiempos - (datosProblem.t[indice] * veces[indice]);
        i++;
    }

    solve = veces;
    //Imprimimos las soluciones obtenidas
    solucionesImpresora(datosProblem);
}
