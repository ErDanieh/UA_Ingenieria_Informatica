.PHONY= clean
CC=g++
OPTIONS= -g -std=gnu++0x 
DEBUG= #-D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= tokenizador.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ)) 
all: practica1
practica1: src/main.cpp $(OBJ) 
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/main.cpp $(OBJ) -o practica1
$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<
clean: 
	rm -f $(OBJ)