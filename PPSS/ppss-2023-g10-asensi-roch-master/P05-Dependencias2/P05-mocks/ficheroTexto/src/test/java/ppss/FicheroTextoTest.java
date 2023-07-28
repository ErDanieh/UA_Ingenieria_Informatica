package ppss;

import static org.junit.jupiter.api.Assertions.*;
import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
class FicheroTextoTest {

    @Test
    void contarCaracteresC1(){
        //Creamos el control
        IMocksControl ctrl = EasyMock.createStrictControl();
        // Hacemos el mock parcial de nuestra clase para testear
        FicheroTexto ficheroTestable = EasyMock.partialMockBuilder(FicheroTexto.class).addMockedMethod("getFileReader").mock(ctrl);
        //Hacemos el mock de nuestra dependencia externa
        FileReader fileReaderMock =  ctrl.mock(FileReader.class);

        //Definimos las entradas y salidas esperadas
        String nombreFichero = "src/test/resources/ficheroC1.txt";
        String mensajeExceptionEsperado = nombreFichero + " (Error al leer el archivo)";

        //Programamos las secuencias que se deben de seguir
        assertDoesNotThrow(()-> EasyMock.expect(ficheroTestable.getFileReader(nombreFichero)).andReturn(fileReaderMock));
        assertDoesNotThrow(()->EasyMock.expect(fileReaderMock.read()).andReturn((int) 'a').andReturn((int)'b').andThrow(new IOException()));

        ctrl.replay();
        FicheroException exceptionObtenida = assertThrows(FicheroException.class,()-> ficheroTestable.contarCaracteres(nombreFichero));
        assertEquals(mensajeExceptionEsperado, exceptionObtenida.getMessage());
        ctrl.verify();

    }

    @Test
    void contarCaracteresC2(){
        //Creamos el control
        IMocksControl ctrl = EasyMock.createStrictControl();
        // Hacemos el mock parcial de nuestra clase a testear con la factoria local
        FicheroTexto ficheroTextoTestable = EasyMock.partialMockBuilder(FicheroTexto.class).addMockedMethod("getFileReader").mock(ctrl);
        // Hacemos el mock  de nuestra dependencia externa
        FileReader fileReaderMock = ctrl.mock(FileReader.class);

        //Definimos las entradas y salidas esperadas
        String nombreFichero = "src/test/resources/ficheroC2.txt";
        String mensajeExceptionEsperado = nombreFichero + " (Error al cerrar el archivo)";

        //Programamos las secuencias que se deben de seguir
        assertDoesNotThrow(()-> EasyMock.expect(ficheroTextoTestable.getFileReader(nombreFichero)).andReturn(fileReaderMock));
        assertDoesNotThrow(()-> EasyMock.expect(fileReaderMock.read()).andReturn((int)'a').andReturn((int)'b').andReturn((int)'c').andReturn(-1));

        //Hacemos que lance la excepcion en la ultima llamada al mock
        assertDoesNotThrow(()-> fileReaderMock.close());
        EasyMock.expectLastCall().andThrow(new IOException());

        //assertDoesNotThrow(()->EasyMock.expect(fileReaderMock.close()).andReturn(new IOException()));

        ctrl.replay();
        FicheroException exceptionObtenida = assertThrows(FicheroException.class, ()->ficheroTextoTestable.contarCaracteres(nombreFichero));
        assertEquals(mensajeExceptionEsperado,exceptionObtenida.getMessage());
        ctrl.verify();



    }

}