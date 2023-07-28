#Daniel Asensi Roch
INPUT = fw.c
OUTPUT = fw
OPTS = mpicc

all:
	${OPTS} ${INPUT} -o ${OUTPUT}


clear: 
	rm ${OUTPUT}

redo: 
	rm ${OUTPUT} && ${OPTS} ${INPUT} -o ${OUTPUT}
	
run:
	mpirun -np 4 ./${OUTPUT}
