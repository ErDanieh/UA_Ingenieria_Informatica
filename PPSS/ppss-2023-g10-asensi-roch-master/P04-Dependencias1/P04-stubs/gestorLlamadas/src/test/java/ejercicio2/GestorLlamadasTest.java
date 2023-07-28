package ejercicio2;

import org.junit.jupiter.api.BeforeEach;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.params.provider.ValueSource;

class GestorLlamadasTest {

    GestorLlamadasTesteable g;
    CalendarioStub c;

    @BeforeEach
    void setup(){
        g = new GestorLlamadasTesteable();
        c = new CalendarioStub();
    }

    @Test
    void CalculaConsumoC1(){
        int minutos = 10;
        int hora = 15;
        double resultadoEsperado = 208;

        c.setHoraActual(15);
        g.SetCalendario(c);

        double resultadoObtenido = g.calculaConsumo(minutos);
        assertEquals(resultadoEsperado,resultadoObtenido);
    }

    @Test
    void CalculaConsumoC2(){
        int minutos = 10;
        int hora = 22;
        double resultadoEsperado = 105;

        c.setHoraActual(hora);
        g.SetCalendario(c);

        double resultadoObtenido = g.calculaConsumo(minutos);
        assertEquals(resultadoEsperado,resultadoObtenido);
    }
}