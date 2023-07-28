#Daniel Asensi Roch 48776120C
OPTS = -Wall -O3 -std=c++0x

pow2: pow2.cc
	g++ ${OPTS} -o pow2 pow2.cc 

pow2.steps: pow2
	./pow2 > pow2.steps

graphs: pow2.steps pow2.gnuplot
	gnuplot pow2.gnuplot

all: pow2 pow2.steps graphs

tar: pow2.cc pow2.gnuplot makefile
	tar cvfz 48776120C.tar.gz pow2.cc pow2.gnuplot makefile

clean: 
	-rm pow2 pow2.steps fit.log *.png 
 
