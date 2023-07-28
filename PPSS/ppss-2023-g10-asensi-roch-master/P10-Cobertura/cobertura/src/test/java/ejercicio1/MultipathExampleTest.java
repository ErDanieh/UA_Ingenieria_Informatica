package ejercicio1;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import java.util.stream.Stream;


class MultipathExampleTest {


    //Entra en ambos ifs
    @Test
    void test1 () {
        int a = 6;
        int b = 6;
        int c = 0;

        MultipathExample m = new MultipathExample();
        assertEquals(12, m.multiPath1(a,b,c));
    }

    //No entra en los ifs
    @Test
    void test2 () {
        int a = 3;
        int b = 3;
        int c = 0;

        MultipathExample m = new MultipathExample();
        assertEquals(0, m.multiPath1(a,b,c));
    }

    //Entra en el primer if
    @Test
    void test3 () {
        int a = 6;
        int b = 3;
        int c = 0;

        MultipathExample m = new MultipathExample();
        assertEquals(6, m.multiPath1(a,b,c));
    }

    //Entra en el segundo if
    @Test
    void test4 () {
        int a = 3;
        int b = 6;
        int c = 0;

        MultipathExample m = new MultipathExample();
        assertEquals(6, m.multiPath1(a,b,c));
    }

    //Para ver que no se borra el index
    @Test
    void apartadoC () {
        int a = 3;
        int b = 6;
        int c = 2;

        MultipathExample m = new MultipathExample();
        assertEquals(8, m.multiPath1(a,b,c));
    }



    @ParameterizedTest
    @MethodSource("multiPath2_args")
    public void multiPath2(int a, int b, int c, int resultadoEsperado){
        MultipathExample m = new MultipathExample();
        int resultadoObtenido = m.multiPath2(a,b,c);
        assertEquals(resultadoEsperado,resultadoObtenido);
    }

    private static Stream<Arguments> multiPath2_args(){
        return Stream.of(
                Arguments.of(5, 5, 5, 5), //No entra en ningún if
                Arguments.of(6, 4, 6, 16),//Primer if:(true && true) Segundo if: (true)
                Arguments.of(6, 5, 6, 11) //Primer if: (true && false) Segundo if: (true)
        );
    }


    @ParameterizedTest
    @MethodSource("multiPath3_args")
    public void multiPath3  (int a, int b, int c, int resultadoEsperado){
        MultipathExample m = new MultipathExample();
        int resultadoObtenido = m.multiPath3(a,b,c);
        assertEquals(resultadoEsperado,resultadoObtenido);
    }

    private static Stream<Arguments> multiPath3_args(){
        return Stream.of(
                Arguments.of(5, 5, 5, 5), //No entra en ningún if
                Arguments.of(6, 4, 6, 16),//Primer if:(true && true) Segundo if: (true)
                Arguments.of(6, 5, 6, 11) //Primer if: (true && false) Segundo if: (true)
        );
    }

}