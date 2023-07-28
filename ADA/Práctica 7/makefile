#Daniel Asensi Roch 48776120C
OPTS = -Wall -O3 -std=c++0x
potter: potter_greddy.cc
	g++ ${OPTS} -o potter_greddy potter_greddy.cc

tar: potter_greddy.cc makefile
	tar cvfz 48776120C.tar.gz potter_greddy.cc makefile

clean:
	-rm potter_greddy