all: estandar

run: estandar
	./vida

no_optimizado: source.cpp
	g++ -Wall -O0 source.cpp -o vida

estandar: source.cpp
	g++ -Wall -O1 source.cpp -o vida

optimizado: source.cpp
	g++ -Wall -O3 source.cpp -o vida

clean:
	rm vida

