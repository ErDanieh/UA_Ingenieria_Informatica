.PHONY= clean

CC=g++
OPTIONS= -g -std=-std=c++11
DEBUG= #-D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= indexadorHash.o tokenizador.o stemmer.o indexadorInformacion.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: indexador

indexador:    src/main.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/main.cpp $(OBJ) -o indexador

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ) 