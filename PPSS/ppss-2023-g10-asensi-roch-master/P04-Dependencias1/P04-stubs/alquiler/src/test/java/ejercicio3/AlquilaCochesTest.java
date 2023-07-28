package ejercicio3;


import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import static org.junit.jupiter.api.Assertions.*;

public class AlquilaCochesTest {


    IService s;
    AlquilaCochesTestable al;

    @BeforeEach
    public void setup(){
        //Asumimos	 que	 el	 precio	 base	 para	 cualquier	 día	 es	 de	 10	 euros
        s = new ServicioStub(10);
        al = new AlquilaCochesTestable(s);

    }


    @Test
    void AlquilaCochesC1(){

        LocalDate fecha = LocalDate.of(2023,5,18);
        CalendarioStub c = new CalendarioStub(new ArrayList<>(), new ArrayList<>());
        al.setCalendario(c);
        Ticket resultado = assertDoesNotThrow(()->al.calculaPrecio(TipoCoche.CARAVANA,fecha,10));
        assertEquals(75, resultado.getPrecio_final());
    }

    @Test
    void AlquilaCochesC2(){

        LocalDate fecha = LocalDate.of(2023,6,19);
        CalendarioStub c = new CalendarioStub(Arrays.asList(20,24), new ArrayList<>());
        al.setCalendario(c);
        Ticket resultado = assertDoesNotThrow(()->al.calculaPrecio(TipoCoche.CARAVANA,fecha,7));
        assertEquals(62.5, resultado.getPrecio_final());
    }

    @Test
    void AlquilaCochesC3(){

        LocalDate fecha = LocalDate.of(2023,4,17);
        CalendarioStub c = new CalendarioStub(new ArrayList<>(), Arrays.asList(18,21,22));
        al.setCalendario(c);
        MensajeException resultado = assertThrows(MensajeException.class,()->al.calculaPrecio(TipoCoche.TURISMO,fecha,8));
        assertEquals("Error en dia: 2023-04-18; Error en dia: 2023-04-21; Error en dia: 2023-04-22; ", resultado.getMessage());
    }

}
