package ppss;

import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
public class FicheroTexto {

    /**
     * Esto nos obliga a usar una factoria Local
     *
     * Queremos	implementar	drivers	para	automatizar	los	casos	de	prueba	anteriores	usando	 verificación
     * basada	 en	 el	 comportamiento.	 Debes	 tener	 en	 cuenta	 que	no	 podemos	 alterar	 en	 modo	 alguno	 la
     * invocación	a	nuestra	unidad	desde	otras	unidades,	ni	tampoco	podemos	añadir	ningún	atributo	en	la
     * clase	de	nuestro	SUT	ni	añadir	clases	adicionales		en	src/main/java
     */

    public FileReader getFileReader(String nombreFichero) throws FileNotFoundException{
        return new FileReader(nombreFichero);
    }
    public int contarCaracteres(String nombreFichero) throws FicheroException {
        int contador = 0;
        FileReader fichero = null;
        try {
            //FICHERO Refactorizad -> fichero = new FileReader(nombreFichero
            fichero = getFileReader(nombreFichero);
            int i=0;
            while (i != -1) {
                i = fichero.read();
                contador++;
            }
            contador--;
        } catch (FileNotFoundException e1) {
            throw new FicheroException(nombreFichero + " (No existe el archivo o el directorio)");
        } catch (IOException e2) {
            throw new FicheroException(nombreFichero + " (Error al leer el archivo)");
        }
        try {
            System.out.println("Antes de cerrar el fichero");
            fichero.close();
        } catch (IOException e) {
            throw new FicheroException(nombreFichero +
                    " (Error al cerrar el archivo)");
        }
        return contador;
    }
}
