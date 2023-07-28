.PHONY= clean

CC=g++
OPTIONS=-std=gnu++0x  -g #-pg
DEBUG= #-D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= buscador.o indexadorHash.o tokenizador.o stemmer.o indexadorInformacion.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: buscador

buscador:    src/main.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/main.cpp $(OBJ) -o buscador

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ) 