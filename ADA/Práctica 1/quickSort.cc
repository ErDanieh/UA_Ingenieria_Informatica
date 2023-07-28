//Daniel Asensi Roch 48776120C
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define numtry 30

void middle_QuickSort(int *v, long left, long right)
{

    long i, j;
    int pivot, aux;
    if (left < right)
    {
        i = left;
        j = right;
        pivot = v[(i + j) / 2];
        do
        {
            while (v[i] < pivot)
                i++;
            while (v[j] > pivot)
                j--;
            if (i <= j)
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j)
            middle_QuickSort(v, left, j);
        if (i < right)
            middle_QuickSort(v, i, right);
    }
}

int main(void)
{

    //  srand(getpid());
    srand(0);
    float tiempo = 0; //Variable para luego sacar la media de las 30

    cout << "# QuickSort CPU times in milliseconds:"
         << endl
         << "# Size \t CPU time (ms.)"
         << endl
         << "# ----------------------------"
         << endl;

    for (int exp = 15; exp <= 22; exp++)
    {
        size_t size = size_t(pow(2, exp));
        int *v = new int[size];
        if (!v)
        {
            cerr << "Error, not enough memory!" << endl;
            exit(EXIT_FAILURE);
        }

        cout << size << "\t\t" << std::flush;

        for (unsigned i = 0; i < numtry; i++)
        {
            for (size_t j = 0; j < size; j++)
                v[j] = rand();

            auto start = clock();
            middle_QuickSort(v, 0, size - 1);
            auto end = clock();

            for (size_t i = 1; i < size; i++)
                if (v[i] < v[i - 1])
                {
                    cerr << "Panic, array not sorted! " << i << endl;
                    exit(EXIT_FAILURE);
                }

            tiempo = tiempo + 1000.0 * (end - start) / CLOCKS_PER_SEC;
        }

        cout << tiempo / numtry << endl;

        tiempo = 0;

        delete[] v;
    }
}
