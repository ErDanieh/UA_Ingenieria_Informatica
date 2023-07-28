#correccion del formato dos -> unix
BUFF=/tmp/corrige.bld.$$
#fichero que almacenara la salida del tad nuestro.
SAL=/tmp/corrige.sal.$$
#fichero que almacenara la salida de error de nuestro tad.
ERR=/tmp/corrige.err.$$
if test $# != 1
then
	echo -e "USO: ./corrige FICHERO_PRUEBA"
	exit 1
fi

if ! test -e $1
then
	echo "ERROR: No existe el fichero $1"
	exit 1
fi

if ! test -e makefile
then
	echo "ERROR: No existe el makefile"
fi

rm -f tad
cp $1 src/tad.cpp
make

if ! test -e tad
then
	echo "ERROR: No compila"
	exit 1
fi

./tad > $SAL 2> $ERR

if ! test -e $1.sal
then
	echo "ERROR: No existe el fichero salida de esta prueba"
else
	# cambiamos el salto de linea a unix.
	tr -d '\r' < $1.sal > $BUFF
	DIFF=$(diff $BUFF $SAL)
	
	if test -z "$DIFF"
	then
		tput setf 3
		tput bold
		echo "OK😃️"
		tput op
		tput sgr0
	else
		tput setf 4
		tput bold
		echo "FALLO🤔️"
		tput op
		tput sgr0
		echo $DIFF
	fi	
fi
