package ppss;

import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;


class GestorLlamadasTest {


    @Test
    void calculaConsumoC1(){
        //Verificacion basada en comportamiento necesitamos el control
        IMocksControl ctrl = EasyMock.createStrictControl();

        //Primer paso Crear el mock de la dependencia externa
        Calendario mock = ctrl.mock(Calendario.class);
        //Hacemos un mock parcial de la clase con el metodo externo, ademas se lo anadimos al control .mock(ctrl)
        GestorLlamadas gestorLlamadaTestable = EasyMock.partialMockBuilder(GestorLlamadas.class).addMockedMethod("getCalendario").mock(ctrl);

        //Lo inyectamos diciendole que queremos que nos devuelva el mock que hemos creado
        EasyMock.expect(gestorLlamadaTestable.getCalendario()).andReturn(mock);

        //Definimos entradas y salidas
        int minutos = 22;
        int hora = 10;
        double salidaEsperada = 457.6;

        //Cuando nuestro mock del calendario llame a getHoraActual quiero que devuelva la hora
        EasyMock.expect(mock.getHoraActual()).andReturn(hora);

        //Indicamos que ya estamos listos para ejecutar el mock
        ctrl.replay();

        double resultadoObtenido = gestorLlamadaTestable.calculaConsumo(minutos);

        assertEquals(salidaEsperada, resultadoObtenido);

        ctrl.verify();

    }

    @Test
    void calculaConsumoC2(){
        //Verificacion basada en comportamiento necesitamos el control
        IMocksControl ctrl = EasyMock.createStrictControl();

        //Creamos el mock de la dependencia externa
        Calendario mock = ctrl.mock(Calendario.class);
        //Hacemos un mock parcial de la clase con el metodo externo
        GestorLlamadas gestorLlamadasTestable = EasyMock.partialMockBuilder(GestorLlamadas.class).addMockedMethod("getCalendario").mock(ctrl);
        //Lo inyectamos diciendole que queremos que devuelva el mock que hemos creado
        EasyMock.expect(gestorLlamadasTestable.getCalendario()).andReturn(mock);

        //Definimos entradas y salidas
        int minutos = 13;
        int hora = 21;
        double salidaEsperada = 136.5;

        //Cuando nuestro mock del calendario llame a getHoraActual quiero que devuelva mi hora
        EasyMock.expect(mock.getHoraActual()).andReturn(hora);

        //Indicamos que ya estamos listos para ejecutar el mock
        ctrl.replay();

        double resultadoObtenido = gestorLlamadasTestable.calculaConsumo(minutos);

        assertEquals(salidaEsperada, resultadoObtenido);

        ctrl.verify();
    }



}