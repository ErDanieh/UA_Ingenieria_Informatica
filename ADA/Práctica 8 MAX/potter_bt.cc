// ANDER DORADO BOLE, 48827596E

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> // std::sort
#include <chrono>
#include <numeric> // std::iota

using namespace std;

string OPTION_F = "-f";

long nodosVisitados = 0;
long nodosExplorados = 0;
long nodosHojaVisitdos = 0;
long nodosNoFactibles = 0;
long nodosNoPrometedores = 0;

bool manejadorArgumentos(int argc, char *argv[], string &file, bool &f);
bool leerArchivo(string inputFile, int &n, double &T, vector<double> &t, vector<double> &v, vector<double> &m);
void kpotter(vector<double> &v, vector<double> &t, vector<double> &m,
             double T, size_t k, vector<double> &x, double present_t, double present_v, double &best_v);
double kpotter(int n, vector<double> &v, vector<double> &t, vector<double> &m, double T);
double kpotter_d(const vector<double> &v, const vector<double> &t, const vector<double> &m, double T);
double kpotter_c(int n, double T, vector<double> &t, vector<double> &v, vector<double> &m);

/*
    Programa principal
*/
int main(int argc, char *argv[])
{
    bool fOption = false;

    string fileName = "";

    int n = 0;
    double T = 0;

    vector<double> t;
    vector<double> v;
    vector<double> m;

    double mejorSol = 0.0; // Mejor sol backtracking

    if (!manejadorArgumentos(argc, argv, fileName, fOption))
        return 0;

    if (!leerArchivo(fileName, n, T, t, v, m))
        return 0;

    vector<int> decision(n);
    vector<double> nodo(n);

    auto start = clock();
    mejorSol = kpotter(n, v, t, m, T);
    auto end = clock();

    cout << mejorSol << endl;
    cout << nodosVisitados << " "
         << nodosExplorados << " "
         << nodosHojaVisitdos << " "
         << nodosNoFactibles << " "
         << nodosNoPrometedores << endl;

    cout << (1000.0 * (double)(end - start) / CLOCKS_PER_SEC) << endl;

    return 0;
}

/*
    Manejador de argumentos. Devuelve si los argumentos son validos.
*/
bool manejadorArgumentos(int argc, char *argv[], string &fileName, bool &f)
{

    for (int i = 1; i < argc; i++)
    {
        string palabra = argv[i];

        if (palabra == OPTION_F)
        {
            f = true;
            i++;

            if (i >= argc)
            {
                cout << "ERROR: missing filename." << endl;
                return false;
            }
            fileName = argv[i];

            ifstream file;

            file.open(fileName);

            if (!file.is_open())
            {
                cout << "ERROR: can’t open file: " << fileName << "." << endl;
                return false;
            }

            file.close();
        }

        else
        {
            cout << "ERROR: unknown option " << palabra << "." << endl;
            cout << "Usage:" << endl;
            cout << "potter -f file" << endl;
            return false;
        }
    }

    if (argc < 3 || !f || fileName == "")
    {
        cerr << "Error: Argumentos insuficientes." << endl;
        return false;
    }

    return true;
}

/*
    Lee el fichero y alamcena los datos n, T, t, v, m
*/
bool leerArchivo(string inputFile, int &n, double &T, vector<double> &t, vector<double> &v, vector<double> &m)
{

    ifstream file;
    file.open(inputFile);

    if (!file.is_open())
    {
        cout << "ERROR: can’t open file: " << inputFile << "." << endl;
        return false;
    }

    string linea;
    unsigned numLineas = 0;

    while (getline(file, linea))
    {
        stringstream palabra(linea);

        switch (numLineas)
        {
            double valor;

        case 0:
            palabra >> n;
            palabra >> T;
            numLineas++;
            break;

        case 1:
            while (palabra >> valor)
            {
                t.push_back(valor);
            }

            numLineas++;
            break;

        case 2:
            while (palabra >> valor)
            {
                v.push_back(valor);
            }
            numLineas++;
            break;

        case 3:
            while (palabra >> valor)
            {
                m.push_back(valor);
            }
            numLineas++;
            break;

        default:
            numLineas++;
            break;
        }
    }

    file.close();
    return true;
}

/*
* Cambio de orden de exploracion de los objetos.
*/
double kpotter(int n, vector<double> &v, vector<double> &t, vector<double> &m, double T)
{
    vector<size_t> idx(v.size()); // index vector

    iota(begin(idx), end(idx), 0);

    sort(begin(idx), end(idx),
         [&v, &t](size_t i, size_t j)
         {
             return v[i] / t[i] > v[j] / t[j];
         });

    vector<double> s_v(v.size()), s_t(t.size()), s_m(m.size());

    for (size_t i = 0; i < v.size(); i++)
    {
        s_v[i] = v[idx[i]]; // valores ordenados
        s_t[i] = t[idx[i]]; // tiempos ordenados
        s_m[i] = m[idx[i]]; // maximos ordenados
    }

    vector<double> x(v.size());
    double best_val = kpotter_d(s_v, s_t, s_m, T);
    kpotter(s_v, s_t, s_m, T, 0, x, 0.0, 0.0, best_val);

    return best_val;
}

/*
    Metodo kpotter_c. Almacena las decisiones en el vector decisiones
*/
double kpotter_c(int n, double T, vector<double> &t, vector<double> &v, vector<double> &m)
{
    if (T == 0)
        return 0.0;

    double acc_v = 0.0;

    for (unsigned i = n; i < t.size(); i++)
    {

        int disponible = (T/t[i] > m[i]) ? m[i] : T / t[i];

        if (t[i] > T)
        {
            acc_v += T / t[i] * v[i];
            break;
        }

        acc_v += disponible * v[i];
        T -= disponible * t[i];
    }

    return acc_v;
}

/*
* Heuristico discreto
*/
double kpotter_d(const vector<double> &v, const vector<double> &t, const vector<double> &m, double T)
{

    double acc_v = 0.0;

    for (unsigned i = 0; i < t.size(); i++)
    {
        if (t[i] < T)
        {
            int disponible = (T/t[i] > m[i]) ? m[i] : T / t[i];
            acc_v += disponible * v[i];
            T -= disponible * t[i];
        }
    }

    return acc_v;
}

/**
 * Funcion backtracking,
 */
void kpotter(vector<double> &v, vector<double> &t, vector<double> &m,
             double T, size_t k, vector<double> &x, double peso, double valor,
             double &best_v)
{
    if (k == x.size()) // Es una hoja
    {
        nodosHojaVisitdos++;
        best_v = valor;
        return;
    }

    for (double j = m[k]; j >= 0; j--)
    {
        nodosVisitados++;
        x[k] = j;

        double new_peso = peso + x[k] * t[k];
        double new_value = valor + x[k] * v[k];

        if (new_peso <= T)
        {
            if (new_value + kpotter_c(k + 1, T - new_peso, t, v, m) > best_v)
            {
                nodosExplorados++;
                kpotter(v, t, m, T, k + 1, x, new_peso, new_value, best_v);
            }
            else
                nodosNoPrometedores++;
        }

        else
            nodosNoFactibles++;
    }
}
