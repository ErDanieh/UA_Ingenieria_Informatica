package ejercicio1;


import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.params.provider.ValueSource;

class GestorLlamadasTest {
    //Usamos el clon
    GestorLlamadasTesteable g;

    @BeforeEach
    void setup(){g = new GestorLlamadasTesteable();}

    @Test
    void CalculaConsumoC1(){
        int minutos = 10;
        int hora = 15;
        double resultadoEsperado = 208;

        g.setHoraActual(hora);

        double resultadoObtenido = g.calculaConsumo(minutos);
        assertEquals(resultadoEsperado,resultadoObtenido);
    }

    @Test
    void CalculaConsumoC2(){
        int minutos = 10;
        int hora = 22;
        double resultadoEsperado = 105;

        g.setHoraActual(hora);
        double resultadoObtenido = g.calculaConsumo(minutos);
        assertEquals(resultadoEsperado,resultadoObtenido);
    }

}