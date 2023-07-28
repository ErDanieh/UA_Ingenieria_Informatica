import clasificador_debil as cd
import numpy as np
import math

#X vector de imagenes ya transformado
#Y vector de etiquetas transformado
#T número de veces que se ejecuta el bucle
#A cantidad de clasificadores debiles que se generan en cada bucle
#D es una array de valores inicializado a 1/cantidadImagenes
def entrenar(X, Y, T, A):
    #Para guardar el conjunto de mejores clasificadores y sus alpha [ht,alpha]
    vecMejoresHt = []
    vecAlphas = []
    
    #Inicializamos el vector de errores que al principio estará compuesto valores double
    D = np.ones(len(X), dtype=float)/len(X)
    
    for t in range(T):
        #Menor suma de errores del clasificador debil y su array de errores
        menor_sumerr= np.inf
        
        best_ht = None
        
        #Comenzamos a probar clasificadores debiles
        for k in range(A):
            
            ht = cd.generar_clasificador_debil(28*28)
            #print("Se ha generado", ht)
            #Comenzamos a entrenar al clasificador
            sumaError = cd.obtener_error(ht, X, Y, D)
            #Sacamos el error de nuestro vector de resultados
            if(sumaError < menor_sumerr):
                best_ht = ht
                menor_sumerr = sumaError
            
        #print("el mejor ha sido", best_ht)       
        #Para calcular la confianza utilizaremos
        alpha = np.float64(0.5 * np.log2((1.0 - menor_sumerr) / (menor_sumerr + 1e-5)))
        vecMejoresHt.append(best_ht)
        vecAlphas.append(alpha)
        
        for i in range(len(X)):
            valor = cd.aplicar_clasificador_debil(best_ht, X[i])
            D[i] = (D[i] * pow(math.e, -alpha*Y[i]*valor))
                    
        z = np.sum(D)
        
        #for i in D:
            #z = z + i
    
        for i in range(len(X)):
            D[i] = D[i] / z
        
        
        
    
    return (vecMejoresHt, vecAlphas)