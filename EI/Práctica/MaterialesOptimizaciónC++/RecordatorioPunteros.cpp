#include <stdio.h>

void NotocaVariable(int n)
{
    n = n + 1;
}

void tocaVariable(int* n)
{
    //Rescatamos el número que hay en la posición de memoria
    int y = *n;
    y = y + 1;
    //Ahora modificamos el valor que hay en la celda n
    *n = y;
}

int main()
{
    int x = 10;
    printf("%d \n", x);

    //Para guardar la dirección de memoria de una variable
    int *dirX = &x;
    printf("%u \n", dirX);

    //Podemos hacerlo con cualquier tipo de variable
    float y = 0.5;
    float *dirY = &y;
    printf("%u \n", dirY);

    //Recuerda que cuando llamamos una función si no lleva el & no modifica la variable
    NotocaVariable(x);
    printf("%d \n", x);

    //Ahora llamamos a la función que si que toca la variable para ver que la modifica
    tocaVariable(&x);
    printf("%d \n", x);

    /**Trabajar con punteros consume mucha menos memoria que si trabajamos con copias de objetos
     * ya que no realizaremos la copia y solo trabajaremos con un objeto que modificaremos 
     * a lo largo que avance la ejecución de nuestro programa.
     * **/


}