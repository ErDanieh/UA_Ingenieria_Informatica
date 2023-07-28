package ppss;

import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import javax.xml.crypto.Data;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class DataArrayTest {

    @Test
    void deleteTestC1(){

        int datos[] = {1,3,5,7};
        int aBorrar = 5;
        int esperados[] = {1,3,7};

        DataArray dataArray = new DataArray(datos);
        assertDoesNotThrow(()-> dataArray.delete(aBorrar), "Salta excepcion");
        assertAll("Test datos",
                ()->assertEquals(3,dataArray.size()),
                ()->assertArrayEquals(esperados, dataArray.getColeccion()));


    }

    @Test
    void deleteTestC2(){
        int datos[] = {1,3,3,5,7};
        int aBorrar = 3;
        int esperados[] = {1,3,5,7};

        DataArray dataArray = new DataArray(datos);
        assertDoesNotThrow(()-> dataArray.delete(aBorrar), "Salta excepcion");
        assertAll("Test datos",
                ()->assertEquals(4,dataArray.size()),
                ()->assertArrayEquals(esperados, dataArray.getColeccion()));

    }

    @Test
    void deleteTestC3(){
        int datos[] = {1,2,3,4,5,6,7,8,9,10};
        int aBorrar = 4;
        int esperados[] = {1,2,3,5,6,7,8,9,10};

        DataArray dataArray = new DataArray(datos);
        assertDoesNotThrow(()-> dataArray.delete(aBorrar), "Salta excepcion");
        assertAll("Test datos",
                ()->assertEquals(9,dataArray.size()),
                ()->assertArrayEquals(esperados, dataArray.getColeccion()));
    }

    @Test
    void deleteTestC4(){
        DataArray dataArray = new DataArray();
        DataException exception = assertThrows(DataException.class,()-> dataArray.delete(8));
        assertEquals("No hay elementos en la colección", exception.getMessage());
    }



    @Test
    void deleteTestC5(){

        int datos[] = {1,3,5,7};
        int aBorrar = -5;
        DataArray dataArray = new DataArray(datos);
        DataException exception = assertThrows(DataException.class,()-> dataArray.delete(aBorrar));
        assertEquals("El valor a borrar debe ser > 0", exception.getMessage());

    }

    @Test
    void deleteTestC6(){
        DataArray dataArray = new DataArray();
        DataException exception = assertThrows(DataException.class,()-> dataArray.delete(0));
        assertEquals("Colección vacía. Y el valor a borrar debe ser > 0", exception.getMessage());
    }

    @Test
    void deleteTestC7(){
        int datos[] = {1,3,5,7};
        int aBorrar = 8;
        DataArray dataArray = new DataArray(datos);
        DataException exception = assertThrows(DataException.class,()-> dataArray.delete(aBorrar));
        assertEquals("Elemento no encontrado", exception.getMessage());
    }


    @ParameterizedTest
    @Tag("parametrizado")
    @Tag("conExcepciones")
    @MethodSource("casosDePrueba")
    void testParametrizadoC8(int[] arrayEntrada, int elementoABorrar, String mensajeEsperado){
        DataArray dataArray = new DataArray(arrayEntrada);
        DataException exception = assertThrows(DataException.class,()-> dataArray.delete(elementoABorrar));
        assertEquals(mensajeEsperado, exception.getMessage());
    }

    private static Stream<Arguments> casosDePrueba(){
        return Stream.of(
                Arguments.of(new int[]{}, 8, "No hay elementos en la colección"),
                Arguments.of(new int[]{1,3,5,7}, -5, "El valor a borrar debe ser > 0"),
                Arguments.of(new int[]{}, 0, "Colección vacía. Y el valor a borrar debe ser > 0"),
                Arguments.of(new int[]{1,3,5,7}, 8, "Elemento no encontrado")
        );
    }

    @ParameterizedTest
    @Tag("parametrizado")
    @MethodSource("casosDePruebaC")
    void testParametrizadoC9(int[] arrayEntrada, int elementoABorrar, int[] arrayEsperado){
        DataArray dataArray = new DataArray(arrayEntrada);
        assertDoesNotThrow(()->dataArray.delete(elementoABorrar));
        assertArrayEquals(arrayEsperado,dataArray.getColeccion());
    }

    private static Stream<Arguments> casosDePruebaC(){
        return Stream.of(
                Arguments.of(new int[]{1,3,5,7}, 5, new int[]{1,3,7}),
                Arguments.of(new int[]{1,3,3,5,7}, 3, new int[]{1,3,5,7}),
                Arguments.of(new int[]{1,2,3,4,5,6,7,8,9,10}, 4, new int[]{1,2,3,5,6,7,8,9,10})
        );
    }

}