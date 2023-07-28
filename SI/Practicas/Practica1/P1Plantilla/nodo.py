from casilla import *
from mapa import *
import math

class Nodo():

    # Constructor de nodos
    def __init__(self, casilla, g, h, padre):
        self.casilla = casilla
        # Coste incial
        self.g = g
        # Cota optimista
        self.h = h
        # Coste
        self.f = g + h
        # Padre
        self.padre = padre

    # Ordena los elementos

    def __lt__(self, other):
        return self.f < other.f

    def __eq__(self, other):
        return self.casilla == other.casilla

    # Devuelve la casilla
    def getCasilla(self):
        return self.casilla
    # Devuelve la G

    def getG(self):
        return self.g
    # Devuelve la h

    def getH(self):
        return self.h
    # Devuelve la F

    def getF(self):
        return self.f
    # Devuelve su nodo Padre

    def getPadre(self):
        return self.padre
    
    # Devuelve la lista de Nodos circundantes Accesibles
    def NodosAlrededor(self, mapi, destino):
        coords = []
        h = 0
        for corX in range(self.casilla.getCol()-1, self.casilla.getCol()+2):

            for corY in range(self.casilla.getFila()-1, self.casilla.getFila()+2):

                if not (corX == self.casilla.getCol() and corY == self.casilla.getFila()) and mapi.getCelda(corY, corX) == 0:
                    #h = 0
                    #h = manhattanD(Casilla(corY, corX), destino)
                    h = euclidea(Casilla(corY,corX),destino)
                    #h = chebysev(Casilla(corY,corX),destino)
                    #h = cosSim(Casilla(corY,corX),destino)
                    if (self.casilla.getCol() != corX) and (self.casilla.getFila() != corY):
                        coords.append(Nodo(Casilla(corY, corX), self.g + 1.5, h, self))
                    else:
                        coords.append( Nodo(Casilla(corY, corX), self.g + 1, h, self))

        return list(coords)


def manhattanD(cas1, cas2):
    return abs(cas1.getFila() - cas2.getFila()) + abs(cas1.getCol()- cas2.getCol())

def euclidea(cas1, cas2):
    return math.sqrt((cas2.getFila() - cas1.getFila())**2 + (cas2.getCol() - cas1.getCol())**2)

def chebysev(cas1,cas2):
    return max(abs(cas1.getFila() - cas2.getFila()), abs(cas1.getCol() - cas2.getCol()))

def cosSim(cas1,cas2):
    num = ((cas1.getFila()*cas2.getFila()) + (cas1.getCol()* cas2.getCol()))
    den1 = math.sqrt(pow(cas1.getFila(),2) + pow(cas2.getFila(),2))
    den2 = math.sqrt(pow(cas1.getCol(),2) + pow(cas2.getCol(),2))
    return num/(den1*den2)
