#Daniel Asensi Roch 48776120C
OPTS = -Wall -g -O3 -std=c++0x
potter: potter_bt.cc
	g++ ${OPTS} -o potter_bt potter_bt.cc

tar: potter_bt.cc makefile
	tar cvfz 48776120C.tar.gz potter_bt.cc makefile

clean:
	-rm potter_bt