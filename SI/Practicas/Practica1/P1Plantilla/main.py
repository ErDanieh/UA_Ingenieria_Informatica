import sys
import pygame
import tkinter
import math
from math import *
from casilla import *
from mapa import *
from nodo import *
from pygame.locals import *
import tkinter.filedialog


MARGEN = 5
MARGEN_INFERIOR = 60
TAM = 30
NEGRO = (0, 0, 0)
BLANCO = (255, 255, 255)
VERDE = (0, 255, 0)
ROJO = (255, 0, 0)
AZUL = (0, 0, 255)
AMARILLO = (255, 255, 0)

# ---------------------------------------------------------------------

# Funciones
# ---------------------------------------------------------------------

# Devuelve si una casilla del mapa se puede seleccionar como destino


def bueno(mapi, pos):
    res = False

    if mapi.getCelda(pos.getFila(), pos.getCol()) == 0:
        res = True

    return res

# Devuelve si una posicion de la ventana corresponde al mapa


def esMapa(mapi, posicion):
    res = False

    if posicion[0] > MARGEN and posicion[0] < mapi.getAncho()*(TAM+MARGEN)+MARGEN and \
            posicion[1] > MARGEN and posicion[1] < mapi.getAlto()*(TAM+MARGEN)+MARGEN:
        res = True

    return res

# PDevuelve si se ha pulsado el boton. Posicion del boton: 20, mapa.getAlto()*(TAM+MARGEN)+MARGEN+10]


def pulsaBoton(mapi, posicion):
    res = False

    if posicion[0] > 20 and posicion[0] < 70 and \
       posicion[1] > mapi.getAlto()*(TAM+MARGEN)+MARGEN+10 and posicion[1] < MARGEN_INFERIOR+mapi.getAlto()*(TAM+MARGEN)+MARGEN:
        res = True

    return res


# Construye la matriz para guardar el camino
def inic(mapi):
    cam = []
    for i in range(mapi.alto):
        cam.append([])
        for j in range(mapi.ancho):
            cam[i].append('.')

    return cam

######################################


def moduloVector(cas1, cas2):
    x1 = cas1.getCol()
    x2 = cas2.getCol()
    y1 = cas1.getFila()
    y2 = cas2.getFila()
    return sqrt((x1-x2)**2 + (y1-y2)**2)


#Saca la posición de un objeto en una lista
def position(m, lista):
    h = -1
    for i in range(len(lista)):
        if lista[i]== m:
               h = i
    return h
# Algoritmo A*
def aEstrella(mapi, origen, destino, camino):
    coste = -1
    nodoOrigen = Nodo(origen, 0, 0, None)
    itec  = 0

    #print("Empiezo en:", origen.getFila(), origen.getCol())

    listaInterior = []
    listaFrontera = nodoOrigen.NodosAlrededor(mapi, destino)
    #print("Los nodos alrededor son: ")
    
    #for i in nodoOrigen.NodosAlrededor(mapi,destino):
        #print(i.getCasilla().getFila(), ",", i.getCasilla().getCol(),"g:",i.g,"h:",i.h,"f:",i.f)

    if nodoOrigen.getCasilla() == destino:
        return 0

    while len(listaFrontera) != 0:
        itec = itec + 1
        # Sacamos el nodo con menor coste
        n = min(listaFrontera)
        
        y = n.getCasilla().getFila()
        x = n.getCasilla().getCol()
        camino[y][x] = 'c'

        #print("Exploro:", n.getCasilla().getFila(), ",", n.getCasilla().getCol(),"g:",n.g,"h:",n.h,"f:",n.f)

        if n.getCasilla() == destino:
            # Reconstrucción de camino
            #print("Destino encontrado en" , destino.getFila(),", ", destino.getCol())
            aux = n.getPadre()
            coste = n.getG()

            # Cambia los valores de las celdas para imprimir el camino
            while aux:
                y = aux.getCasilla().getFila()
                x = aux.getCasilla().getCol()
                #print(x, y)
                camino[y][x] = n.getG()
                aux = aux.padre

            break

        else:
            #print("Elimino de la Frontera: ", n.getCasilla().getFila(), ",", n.getCasilla().getCol())
            listaFrontera.remove(n)
            #print("Añado en interior: ", n.getCasilla().getFila(), ",", n.getCasilla().getCol())
            listaInterior.append(n)

            for m in n.NodosAlrededor(mapi,destino):
                if m not in listaInterior:
                    if m not in listaFrontera:
                        # Almacenar la f, g y h del nodo en (m.f, m.g, m.h)
                        h = euclidea(m.getCasilla(),destino)
                        #h = manhattanD(m.getCasilla(), destino)
                        #h = chebysev(m.getCasilla(), destino)
                        #h = cosSim(m.getCasilla(), destino)
                        #h = 0;
                        aux =  Nodo(m.getCasilla(), m.g, h, n)
                        #print("Meto en frontera:",aux.getCasilla().getFila(), ",", aux.getCasilla().getCol(),"g:",aux.g,"h:",aux.h,"f:",aux.f)
                        listaFrontera.append(aux)
                    elif m.g < listaFrontera[position(m,listaFrontera)].g:
                        listaFrontera[position(m,listaFrontera)].padre = n
                        listaFrontera[position(m,listaFrontera)].g = m.g
                        #print("Actualizo:",m.getCasilla().getFila(), ",", m.getCasilla().getCol(),"g:",m.g,"h:",m.h,"f:",m.f);
                        #print("Padre Nuevo:",n.getCasilla().getFila(),",",n.getCasilla().getCol(),n.g);

                        
                              
                    y = m.getCasilla().getFila()
                    x = m.getCasilla().getCol()
                    camino[y][x] = 'c'
        


    print(itec)
    return coste



#Mirar en la frontera si
#tengo un valor más pequeño que m.g si lo 
#tengo hay que cambiarlo por el que tengo ahora


######################################


# funcion principal
def main():
    root = tkinter.Tk()  # para eliminar la ventana de Tkinter
    root.withdraw()  # se cierra
    file = tkinter.filedialog.askopenfilename()  # abre el explorador de archivos

    pygame.init()
    destino = Casilla(-1, -1)

    reloj = pygame.time.Clock()

    if not file:  # si no se elige un fichero coge el mapa por defecto
        file = 'mapa.txt'

    mapi = Mapa(file)
    origen = mapi.getOrigen()
    camino = inic(mapi)

    anchoVentana = mapi.getAncho()*(TAM+MARGEN)+MARGEN
    altoVentana = MARGEN_INFERIOR+mapi.getAlto()*(TAM+MARGEN)+MARGEN
    dimension = [anchoVentana, altoVentana]
    screen = pygame.display.set_mode(dimension)
    pygame.display.set_caption("Practica 1")

    boton = pygame.image.load("boton.png").convert()
    boton = pygame.transform.scale(boton, [50, 30])

    personaje = pygame.image.load("pig.png").convert()
    personaje = pygame.transform.scale(personaje, [TAM, TAM])

    coste = -1
    running = True
    primeraVez = True

    while running:
        # procesamiento de eventos
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                # Pulsa el boton del raton para indicar donde va
            if event.type == pygame.MOUSEBUTTONDOWN:
                # obtener posicion y calcular coordenadas matriciales
                pos = pygame.mouse.get_pos()
                colDestino = pos[0]//(TAM+MARGEN)
                filDestino = pos[1]//(TAM+MARGEN)
                casi = Casilla(filDestino, colDestino)
                if pulsaBoton(mapi, pos):  # reinicializar
                    origen = mapi.getOrigen()
                    destino = Casilla(-1, -1)
                    camino = inic(mapi)
                    coste = -1
                    primeraVez = True
                elif esMapa(mapi, pos):
                    if bueno(mapi, casi):
                        if not primeraVez:  # la primera vez el origen esta en el mapa
                            origen = destino
                        else:
                            # se marca como libre la celda origen
                            mapi.setCelda(int(origen.getFila()),
                                          int(origen.getCol()), 0)
                        destino = casi
                        # Matriz que debemos actualizar
                        camino = inic(mapi)
                        # llamar al A*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        coste = aEstrella(mapi, origen, destino, camino)
                        if coste == -1:
                            tkinter.messagebox.showwarning(
                                title='Error', message='No existe un camino entre origen y destino')
                        else:
                            primeraVez = False  # hay un camino y el destino sera el origen para el proximo movimiento
                    else:  # se ha hecho click en una celda roja
                        tkinter.messagebox.showwarning(
                            title='Error', message='Esa casilla no es valida')

        # codigo de dibujo
        # limpiar pantalla
        screen.fill(NEGRO)
        # pinta mapa
        for fil in range(mapi.getAlto()):
            for col in range(mapi.getAncho()):
                # para que no quede negro el origen inicial
                if mapi.getCelda(fil, col) == 2 and not primeraVez:
                    pygame.draw.rect(screen, BLANCO, [
                                     (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                if mapi.getCelda(fil, col) == 0:
                    if camino[fil][col] == '.':
                        pygame.draw.rect(screen, BLANCO, [
                                         (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                    elif camino[fil][col] == 'c':
                        pygame.draw.rect(screen, AZUL, [
                                         (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                    else:
                        pygame.draw.rect(screen, AMARILLO, [
                                         (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)

                elif mapi.getCelda(fil, col) == 1:
                    pygame.draw.rect(
                        screen, ROJO, [(TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)

        # pinta origen
        screen.blit(personaje, [(TAM+MARGEN)*origen.getCol() +
                    MARGEN, (TAM+MARGEN)*origen.getFila()+MARGEN])
        # pinta destino
        pygame.draw.rect(screen, VERDE, [
                         (TAM+MARGEN)*destino.getCol()+MARGEN, (TAM+MARGEN)*destino.getFila()+MARGEN, TAM, TAM], 0)
        # pinta boton
        screen.blit(boton, [20, mapi.getAlto()*(TAM+MARGEN)+MARGEN+10])
        # pinta coste
        if coste != -1:
            fuente = pygame.font.Font(None, 30)
            texto = fuente.render("Coste "+str(coste), True, AMARILLO)
            screen.blit(texto, [anchoVentana-120,
                        mapi.getAlto()*(TAM+MARGEN)+MARGEN+15])

        # actualizar pantalla
        pygame.display.flip()
        reloj.tick(40)

    pygame.quit()


# ---------------------------------------------------------------------
if __name__ == "__main__":
    main()


