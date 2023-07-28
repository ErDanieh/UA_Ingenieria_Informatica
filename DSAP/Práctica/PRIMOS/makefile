#Daniel Asensi Roch
#Makefile
INPUT = primosParl.c
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
	mpirun -np 2 ${OUTPUT}

sec:
	${SEC} ${INPUTSEC} -o ${OUTPUT} ${linked}

runSec:
	./${OUTPUT}
	
allH:
	mpirun -f hostfile -np 8 ${OUTPUT}
