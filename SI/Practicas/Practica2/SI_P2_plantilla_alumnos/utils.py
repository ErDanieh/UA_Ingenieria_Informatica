import matplotlib.pyplot as plt
from random import randrange

def mostrar_imagen(imagen):
    plt.figure()
    plt.imshow(imagen)
    plt.show()

#Recibimos Mnist_x que es un conjunto de 60000 imagenes de esta manera transformaremos este vector
#de matrices de 28x28 en un solo vector de 784 elementos, por lo que nos quedará en x un conjunto
#de vectores de 784 elementos y en Y nos quedará un conjunto de elementos donde si Y[i]==0 +1 sino -1
def adaptar_conjuntos(mnist_X, mnist_Y, buscado):
    X = mnist_X.reshape(60000,28*28)
    Y = []
    #print(X.shape)
    for i in mnist_Y:
        if i == buscado:
            Y.append(1)
        else:
            Y.append(-1)    
    return (X,Y)

def plot_arrays(X, Y, title):
    plt.title(title)
    plt.plot(X, Y)
    plt.show()