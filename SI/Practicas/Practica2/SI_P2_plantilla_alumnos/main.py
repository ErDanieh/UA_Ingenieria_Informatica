# Importamos las librerias que necesitaremos
import numpy as np
import matplotlib.pyplot as plt
import utils
import adaboost
import clasificador_debil as cd

# Cargamos la base de datos
npzfile = np.load("mnist.npz")
mnist_X = npzfile['x']
mnist_Y = npzfile['y']

# Mostrar una imagen y su etiqueta
#utils.mostrar_imagen(mnist_X[3])
#print(mnist_Y[3])

def generadorConjuntosEntrenamiento(lp,X,Y):
    pruebasZerosX = []
    pruebasZerosY = []
    for x,y in zip(X, Y):
        if len(pruebasZerosX) <= lp/2:
            if y == 1:
                pruebasZerosX.append(x)
                pruebasZerosY.append(y)
        else:
            if len(pruebasZerosX)!= lp and len(pruebasZerosX) > lp/2:
                pruebasZerosX.append(x)
                pruebasZerosY.append(y)
    #print(pruebasZerosY)
    return (pruebasZerosX,pruebasZerosY)

# Adaptar los conjuntos X e Y a AdaBoost
(X, Y) = utils.adaptar_conjuntos(mnist_X, mnist_Y, 0)

(XEntrenar, YEntrenar) = generadorConjuntosEntrenamiento(10000,X, Y)



#X vector de imagenes ya transformado
#Y vector de etiquetas transformado
#T número de veces que se ejecuta el bucle
#A cantidad de clasificadores debiles que se generan en cada bucle
#Cogemos las 1000 primeras imagenes

#X=X[:50000,:]
#Y=Y[:50000]

# Lanzar Adaboost
T = 20
A = 10
#c_f = adaboost.entrenar(XEntrenar, YEntrenar, T, A)
#c_f = adaboost.entrenar(pruebasZerosX, pruebasZerosY, T, A)

def aplicar_clasificador_fuerte(H,X):
    hts,alphas = H
    certeza = 0
    resultados = 0
    
    for ht,alpha in zip(hts,alphas):
        resultados += (cd.aplicar_clasificador_debil(ht,X) * alpha)
    
    return resultados

def sacarPorcentaje(X,Y,c_f):
    predicciones = []
    aciertos = 0.0
    for x in X:
        predicciones.append(aplicar_clasificador_fuerte(c_f,x))
    
    for p,y in zip(predicciones, Y):
        if (p > 0) and (y > 0):
            aciertos += 1
        elif (p < 0) and (y < 0):
            aciertos += 1
    return aciertos/len(Y)*100


def total(mnist_X,mnist_Y,T,A):

    for i in range(10):
        print("Adaptando conjuntos para: ",i)
        (X, Y) = utils.adaptar_conjuntos(mnist_X, mnist_Y, i)
        print("Generando conjuntos para: ", i)
        (XEntrenar, YEntrenar) = generadorConjuntosEntrenamiento(10000,X, Y)
        cf = []
        print("Entrenando a :", i)
        cf=adaboost.entrenar(XEntrenar,YEntrenar,T,A)
        print("Porcentaje aciertos para ", i , ":" , sacarPorcentaje(X, Y, cf))

#print(sacarPorcentaje(X,Y,c_f))
total(mnist_X,mnist_Y,100,1000)




############################################################################
# Analisis y resultados de las pruebas realizadas
#T = [0, 100, 200, 300, 400]      # Numero de clasificadores 
#resultados = [0, 20, 35, 56, 68] # Resultados obtenidos de clasificacion
#utils.plot_arrays(T, resultados, "Porcentajes con valores de T")