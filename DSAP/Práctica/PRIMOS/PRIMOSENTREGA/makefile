#Daniel Asensi Roch
#Makefile
INPUT = PRIMOS.c
INPUTSEC = primos.c
OUTPUT = primos
OPTS = mpicc -w 
SEC = gcc
linked = -lm


all:
	${OPTS} ${INPUT} ${linked} -o ${OUTPUT} -O3


clear: 
	rm ${OUTPUT}


run:
	mpirun -np 4 ${OUTPUT}
	
runH:
	mpirun -f hostfile -np 8 ${OUTPUT}
