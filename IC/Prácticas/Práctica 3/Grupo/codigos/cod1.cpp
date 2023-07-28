#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#define SIZE 1000000
using namespace std;
int main()
{
 // A:
 clock_t begin = clock();
 // declaramos un vector sin inicializar.
 std::vector<int> a;
 // usamos push_back para añadir cada elemento.
 for(int i=0;i<SIZE;i++)
 {
    a.push_back(i);
 }
 double aTime = double(clock() - begin) / CLOCKS_PER_SEC;
 cout<<"Elapsed time: "<<aTime<<"s"<<endl;
 // B:
 begin = clock();
 // declaramos un vector inicializado al tamaño requerido.
 std::vector<int> b(SIZE);
 for(int i=0;i<SIZE;i++)
 {
    a[i] = i;
 }
 double bTime = double(clock() - begin) / CLOCKS_PER_SEC;
 cout<<"Elapsed time: "<<bTime<<"s"<<endl;
 cout<<"Gain: "<<aTime/bTime<<endl;
}