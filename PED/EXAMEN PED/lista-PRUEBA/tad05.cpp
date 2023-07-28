#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
   TListaCalendario l1, l2, l3;
   TCalendario c1;
   TCalendario c2(1, 1, 2007, (char*) "Fecha2");

   l1.Insertar(c1);
   l2.Insertar(c2);
   l3 = l1.SumarSubl(1, l1.Longitud(), l2, 1, l2.Longitud());

   cout << l3 << endl;
   cout << l1.SumarSubl(1, l1.Longitud(), l2, 1, l2.Longitud()) << endl;

   return 0;
}
