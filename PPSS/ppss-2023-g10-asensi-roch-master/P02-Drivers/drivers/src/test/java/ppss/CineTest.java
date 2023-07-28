package ppss;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.stream.Stream;


class CineTest {

    public Cine cine;
    @BeforeEach
    void setupCine(){
        this.cine = new Cine();
    }

    @Test
    void reservaButacasC1(){
        boolean vectorVacio[] = new boolean[0];
        int solicitados = 3;
        ButacasException exception = assertThrows(ButacasException.class,() -> cine.reservaButacasV1(vectorVacio,solicitados));
        assertEquals("No se puede procesar la solicitud",exception.getMessage());
    }

    @Test
    void reservaButacasC2(){

        boolean vectorVacio[] = new boolean[0];
        int solicitados = 0;

        boolean reservadas = assertDoesNotThrow(() -> cine.reservaButacasV1(vectorVacio, solicitados), "Excepcion lanzada");
        assertAll("ReservaButacasC2", ()-> assertArrayEquals(cine.asientos, vectorVacio),
                ()->assertEquals(false, reservadas));
    }

    @Test
    void reservaButacasC3(){

        boolean asientos[] = new boolean[5];
        asientos[0] = false;
        asientos[1] = false;
        asientos[2] = false;
        asientos[3] = true;
        asientos[4] = true;

        boolean asientosEsperados[] = new boolean[5];
        asientosEsperados[0] = true;
        asientosEsperados[1] = true;
        asientosEsperados[2] = false;
        asientosEsperados[3] = true;
        asientosEsperados[4] = true;
        int solicitados = 2;

        boolean reservadas = assertDoesNotThrow(() -> cine.reservaButacasV1(asientos, solicitados), "Excepcion lanzada");
        assertAll("ReservaButacasC3", ()-> assertArrayEquals( asientosEsperados, cine.asientos ),
                ()->assertEquals(true, reservadas));

    }

    @Test
    void reservaButacasC4(){

        boolean asientos[] = new boolean[3];
        asientos[0] = true;
        asientos[1] = true;
        asientos[2] = true;
        int solicitados = 1;

        boolean reservadas = assertDoesNotThrow(() -> cine.reservaButacasV1(asientos, solicitados), "Excepcion lanzada");

        assertAll("ReservaButacasC4", ()-> assertArrayEquals( asientos, cine.asientos ),
                ()->assertEquals(false, reservadas));

    }

    @ParameterizedTest
    @Tag("parametrizado")
    @MethodSource("casosDePrueba")
    void reservaButacasC5(boolean [] asientos, int solicitados, boolean[] arrayEsperado, boolean boolEsperado){

        boolean boolObtenido = assertDoesNotThrow(()->cine.reservaButacasV1(asientos,solicitados));
        assertAll("",
                ()->assertEquals(boolEsperado, boolObtenido),
                ()->assertArrayEquals(arrayEsperado, cine.asientos));
    }

    private static Stream<Arguments> casosDePrueba(){
        return Stream.of(
                Arguments.of(new boolean[]{}, 3,new boolean[]{},false),
                Arguments.of(new boolean[]{}, 0, new boolean[]{}, false),
                Arguments.of(new boolean[]{false, false, false, true, true}, 2, new boolean[]{true,true,false,true,true}, true),
                Arguments.of(new boolean[]{true, true, true}, 1, new boolean[]{true,true,true}, false)
        );
    }






}