from random import randrange
#Pixel
#Umbral
#Dirección +1 o -1
    
# Dimension con la que vamos a trabajar. En nuestro caso 28*28
def generar_clasificador_debil(dimension_datos):
    debil = [0,0,0]
    debil[0] = randrange(dimension_datos) #Posición dentro de la imagen
    debil[1] = randrange(256) #Valor
    #Dirección que debemos de tomar
    if randrange(2) == 1:
        debil[2] = 1
    else:
        debil[2] = -1
    #print(debil)
    return debil 

#Devuelve el valor Booleano después de haber aplicado el clasificador a una imagen
def aplicar_clasificador_debil(clasificador, imagen):
    pixel = clasificador[0]
    umbral = clasificador[1]
    direccion = clasificador[2]
    
    if direccion == 1:
        if imagen[pixel] > umbral:
            return 1
        else:
            return -1
    else:
        if imagen[pixel] <= umbral:
            return 1
        else:
            return -1
    
#Obtener el error de la clasificación de nuestro clasificador
#debe de devolver un float sumar los pesos de las imagenes mal clasificadas
#para ello recorremos los vectores X e Y aplicando el clasificador si acierta bien
#pero si no acierta hay que hacer 1*D[i] sino 0*D[i] luego sumar todos los valores de D
def obtener_error(clasificador, X, Y, D):
    resultError = 0
    for i in range(len(X)):
        if aplicar_clasificador_debil(clasificador, X[i]) != Y[i]:
            resultError += D[i]
    return resultError
    
    
    