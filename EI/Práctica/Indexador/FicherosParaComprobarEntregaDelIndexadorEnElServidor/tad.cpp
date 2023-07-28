#include <iostream> 
#include <string>
#include <list> 
#include "indexadorHash.h"

using namespace std;

int
main(void)
{
IndexadorHash a("./StopWordsEspanyol.txt", ". ,:", true, true, "./indicePrueba", 1, false, true);

IndexadorHash b("./StopWordsIngles.txt", ". ,:", true, false, "./indicePruebaIngles", 2, true, true);
}
