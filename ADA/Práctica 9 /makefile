#Daniel Asensi Roch 48776120C
OPTS = -Wall -g -O3 -std=c++17
potter: potter_bb.cc
	g++ ${OPTS} -o potter_bb potter_bb.cc

tar: potter_bb.cc makefile
	tar cvfz 48776120C.tar.gz potter_bb.cc makefile memoria.pdf

clean:
	-rm potter_bb