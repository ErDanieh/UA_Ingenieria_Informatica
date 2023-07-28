OPT  = -O3 -w 

all: aristas
aristas: aristas.c aux.o 
	gcc $(OPT) -o aristas aristas.c aux.o
aux.o: aux.c
	gcc $(OPT) -c aux.c
