class Casilla():
    def __init__(self, f, c):
        self.fila=f
        self.col=c
        
    def getFila (self):
        return self.fila
    
    def getCol (self):
        return self.col
        
    
    #Ordena los elementos
    def __eq__(self, other):
        return self.fila == other.fila and self.col == other.col
    