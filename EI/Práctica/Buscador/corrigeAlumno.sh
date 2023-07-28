#!/bin/bash
# Corrector practicas Explotacion de la Informacion
# Modificacion de Antonio Ferrandez sobre la version de:
# (c) Sergio Lujan Mora, 2001

#################################################
# SE EJECUTA DESDE EL DIRECTORIO QUE CONTIENE src lib include
#   DICHO DIRECTORIO NO CONTENDRA NINGUN ARCHIVO $EJE (VER CONTENIDO DE DICHA VARIABLE)
# EL SUBDIRECTORIO src:
#   * CONTENDRA LOS FICHEROS DE PRUEBA: tad*.cpp 
#   * SUS SALIDAS CORRESPONDIENTES tad*.cpp.sal
#   * NO CONTENDRA NINGUN ARCHIVO $MAIN (VER CONTENIDO DE DICHA VARIABLE)
# 
# corrigeAlumno

#################################################
# PARAMETROS A CAMBIAR
#
# Fichero makefile
MAKE1=makefile

# Fichero que contiene el main en el makefile
MAIN=main.cpp
# Nombre del ejecutable en el makefile
EJE=buscador
#################################################

# Directorio raiz
CASA=.

# Directorio ficheros de prueba
DIROK1=./src

MAKE2=$MAKE1
MAKEDIR=$CASA

# Directorio del alumno
DIRALU=.

# Temporal salida estandar
NOMTMPSAL=lwdhfb.tmp
# Temporal salida de error
NOMTMPERR=jfgskv.tmp
# Temporal auxiliar
NOMTMPAUX=qwekjz.tmp
# Temporal auxiliar para OKs
NOMTMPOK=123oks123.tmp

# Elimina el temporal que cuenta los oks
if test -e $NOMTMPOK;
then
  rm $NOMTMPOK
fi

# Elimina el temporal que cuenta los oks
if test -e corrigeUno.log;
then
  rm corrigeUno.log
fi

# Elimina el temporal que cuenta los oks
if test -e corrigeUnoBD.log;
then
  rm corrigeUnoBD.log
fi

# Elimina el temporal que cuenta los oks
if test -e corrigeUno.res;
then
  rm corrigeUno.res
fi





function testOK()
{
  if test -e $DIRALU/$EJE;
  then
# Existe el ejecutable
    $DIRALU/$EJE > $NOMTMPSAL 2> $NOMTMPERR
    echo "###------------ stderr ($auxPROG) --------------"
    cat $NOMTMPERR
    MENERR=$(cat $NOMTMPERR)
    echo "###------------ correccion --------------------"
# Para no tener en cuenta espacios en blanco: -b
# Para no tener en cuenta lineas de mas: -B
# Para ignorar mayusculas/minusculas: -i
# Ejemplo: DIFF=$(diff -b -B -i $1.sal $NOMTMPSAL)
    DIFF=$(diff -bB $1.sal $NOMTMPSAL)
    if test -z "$DIFF";
    then
      if test -z $MENERR;
      then
        echo -e "OK\n"
        echo "OK" >> $NOMTMPOK
      else
        echo -e "REG\n"
        echo "REG" >> $NOMTMPOK
      fi
    else
      echo "$DIFF"
      echo "ERROR" >> $NOMTMPOK
    fi
  else
# No existe el ejecutable
    echo -e "Error: NO EXISTE EL EJECUTABLE\n"
    echo -e "       Posible problema al compilar\n"
    echo "ERROR" >> $NOMTMPOK
  fi
}


function corrige()
{

# Empieza la correccion
  for FICH in $DIROK1/*.cpp;
  do
  echo -e "\n----------------------------------------------"
  echo -e $FICH
  echo -e "----------------------------------------------\n"
# Copia el fichero de prueba
    cp $FICH $DIROK1/$MAIN
# Borra el ejecutable anterior
    if test -e $DIRALU/$EJE;
    then
      rm $DIRALU/$EJE
    fi
    if test -e $DIRALU/$EJE.o;
    then
      rm $DIRALU/$EJE.o
    fi

    make  -f $MAKE1 -s
    testOK $FICH
  done

# Cuenta el numero de OK, REG y ERROR
  echo -e "\n-------------------------"
# La instruccion sed elimina los espacios en blanco iniciales
  VAR=$(grep OK $NOMTMPOK | wc -w | sed -e '1,$ s/^[ ]*//')
  echo "# CORR. OKs:      $VAR"
  echo -n "$VAR:" >> corrigeUno.res	
  VAR=$(grep REG $NOMTMPOK | wc -w | sed -e '1,$ s/^[ ]*//')
  echo "# CORR. REGs:     $VAR"
  echo -n "$VAR:" >> corrigeUno.res
  VAR=$(grep ERROR $NOMTMPOK | wc -w | sed -e '1,$ s/^[ ]*//')
  echo "# CORR. ERRORs:   $VAR"
  echo -n "$VAR:" >> corrigeUno.res
  # Elimina el fichero auxiliar
  rm $NOMTMPOK
  echo "-------------------------"

  # Elimina los ficheros temporales
  rm $NOMTMPSAL
  rm $NOMTMPERR
  # Elimina el ultimo fichero
  if test -e $DIRALU/$EJE.cpp;
  then
    rm $DIRALU/$EJE.cpp
  fi
  if test -e $DIRALU/$EJE;
  then
    rm $DIRALU/$EJE
  fi
  if test -e $DIRALU/$EJE.o;
  then
    rm $DIRALU/$EJE.o
  fi
}




  corrige $DIROK1 $MAKE1

