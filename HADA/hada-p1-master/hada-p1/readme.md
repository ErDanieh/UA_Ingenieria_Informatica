Daniel Asensi Roch

P1: la opción -n del comando git revert -n head sirve para que 
al ejecutar el comando git no haga un autocommit de la eliminiación del archivo

P2: se ha restaurado el archivo readme.md

P3: Los cambios que han ocurrido al realizar el reset es que en vez de volver al commit
indicado por nosotros donde recuperariamos el archivo hacemos que el Head apunte a otra versión
de nuestro repositorio donde encontraremos los archivos y lineas de codigo
almacenados en esa versión

P4: Por lo que he podido comprobar la diferencia fundamental entre git rebase y git merge es que git rebase genera una serie
de commits para aplicarse directamente sobre el HEAD, mientras que merge directamente une las ramas y  hace una descripcion detallada del
historial de cambios realizados .