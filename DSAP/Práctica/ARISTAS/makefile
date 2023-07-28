#Daniel Asensi Roch
#Makefile
INPUT = aristas_mpi.c
OUTPUT = aristas_mpi
OPTS = mpicc -w
linked = -lm aux.o


all: aux aristas run pont
aristas:
	${OPTS} ${INPUT} ${linked} -o ${OUTPUT}
aux: aux.c
	mpicc -O3 -c -w aux.c
run:
	mpirun -np 3 ${OUTPUT}

pont:
	mpirun -np 3 ${OUTPUT} pont
