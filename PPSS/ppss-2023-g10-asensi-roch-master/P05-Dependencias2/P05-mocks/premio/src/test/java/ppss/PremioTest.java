package ppss;

import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Random;

import static org.junit.jupiter.api.Assertions.*;
class PremioTest {

    @Test
    void compruebaPremioC1(){

        //Creamos el control
        IMocksControl ctrl = EasyMock.createStrictControl();

        //Creamos el partial mock de nuestra clase por la dependencia externa de dentro de la clase
        Premio premioTesteable = EasyMock.partialMockBuilder(Premio.class).addMockedMethod("generaNumero").mock(ctrl);
        //Creamos el mock de nuestra dependencia de clase externa
        ClienteWebService clienteMock = ctrl.mock(ClienteWebService.class);
        //Lo inyectamos
        premioTesteable.cliente = clienteMock;

        //Definimos las entradas y la salida esperada
        float numeroAleatorioGenerado = 0.07f;
        String resultadoObtenerPremio = "entrada final Champions";

        String premioEsperado = "Premiado con entrada final Champions";

        //Le decimos que cuando nuestro testeable llame a generaNumero devuelva el que queremos
        EasyMock.expect(premioTesteable.generaNumero()).andReturn(numeroAleatorioGenerado);

        //Le decimos que cuando nuestro Mock llame a la funcion devuelva el resultado
        assertDoesNotThrow(()->EasyMock.expect(clienteMock.obtenerPremio()).andReturn(resultadoObtenerPremio));

        //Hacemos el replay para ver que se han llamado
        ctrl.replay();

        //Sacamos el assert para ver si la salida obtenida es la esperad
        String premioObtenido = premioTesteable.compruebaPremio();
        assertEquals(premioEsperado, premioObtenido);

        //Hacemos el verify del testable y del mock
        ctrl.verify();

    }

    @Test
    void compruebaPremioC2(){
        //Creamos el control
        IMocksControl ctrl = EasyMock.createStrictControl();

        //Creamos el partial mock de nuestra clase por la dependencia externa de dentro de la clase
        Premio premioTesteable = EasyMock.partialMockBuilder(Premio.class).addMockedMethod("generaNumero").mock(ctrl);
        //Creamos el mock de nuestra dependencia de clase externa
        ClienteWebService clienteMock = ctrl.mock(ClienteWebService.class);
        //Lo inyectamos
        premioTesteable.cliente = clienteMock;

        //Definimos las entradas y la salida esperada
        float numeroAleatorioGenerado = 0.03f;
        String resultadoObtenerPremio = "entrada final Champions";
        String premioEsperado = "No se ha podido obtener el premio";


        //Le dedicimos que cuando nuestro testeable llame a generaNumero devuelva el que queremos
        EasyMock.expect(premioTesteable.generaNumero()).andReturn(numeroAleatorioGenerado);

        //Le decimos que cuando nuestro mock llame a la funcion devuelva el resultado
        assertDoesNotThrow(()->EasyMock.expect(clienteMock.obtenerPremio()).andThrow(new ClienteWebServiceException()));

        //Hacemos el replay para ver que se han llamado
        ctrl.replay();

        //Sacamos el assert para ver si la salida obtenida es la esperad
        String premioObtenido = premioTesteable.compruebaPremio();
        assertEquals(premioEsperado, premioObtenido);

        //Hacemos el verify del testable y del mock
        ctrl.verify();
    }

    @Test
    void compruebaPremioC3(){

        //Creamos el partial mock de nuestra clase para la dependencia externa de dentro de la clase
        Premio premioTesteable = EasyMock.partialMockBuilder(Premio.class).addMockedMethod("generaNumero").createMock();
        //Creamos el mock de nuestra dependencia de clase externa, en este caso no nos hace falta
        //ClienteWebService clienteMock = EasyMock.createMock(ClienteWebService.class);
        //Lo inyectamos
        //premioTesteable.cliente = clienteMock;

        //Definimos las entradas y la salida esperada
        float numeroAleatorioGenerado = 0.3f;
        String resultadoEsperado = "Sin premio";

        //Le decimos que cuando nuestro testeable llame a generaNumero devuelva el que queremos
        EasyMock.expect(premioTesteable.generaNumero()).andReturn(numeroAleatorioGenerado);

        //Hacemos el replay para ver que se han llamado
        EasyMock.replay(premioTesteable);

        //Sacamos el assert para ver si la salida obtenido es la esperada
        String premioObtenido = premioTesteable.compruebaPremio();
        assertEquals(resultadoEsperado,premioObtenido);

        //Hacemos la verificacion
        EasyMock.verify(premioTesteable);

    }
}