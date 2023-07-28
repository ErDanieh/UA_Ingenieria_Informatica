#Daniel Asensi Roch 48776120C
OPTS = -Wall -O3 -std=c++0x
potter: potter.cc
	g++ ${OPTS} -o potter potter.cc

tar: potter.cc makefile
	tar cvfz 48776120C.tar.gz potter.cc makefile

clean:
	-rm potter