#Daniel Asensi Roch
#Makefile
INPUT = anillo.c
OUTPUT = anillo
OPTS = mpicc -w

all:
	${OPTS} ${INPUT} -o ${OUTPUT}


clear: 
	rm ${OUTPUT}


run:
	mpirun -np 4 ${OUTPUT}