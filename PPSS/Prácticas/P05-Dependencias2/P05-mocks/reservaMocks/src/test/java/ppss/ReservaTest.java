package ppss;
import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ppss.excepciones.IsbnInvalidoException;
import ppss.excepciones.JDBCException;
import ppss.excepciones.ReservaException;
import ppss.excepciones.SocioInvalidoException;

import static org.junit.jupiter.api.Assertions.*;


public class ReservaTest {
    IMocksControl ctrl;
    Reserva reservaTestable;
    FactoriaBOs factoriaBOsMock;
    IOperacionBO operacionMock;




    @BeforeEach
    void setup(){
        ctrl = EasyMock.createStrictControl();
        //Hacemos el mock parcial de nuestra clase para testear
         reservaTestable =  EasyMock.partialMockBuilder(Reserva.class).addMockedMethod("compruebaPermisos").mock(ctrl);
        //Hacemos el mock de nuestra clase Factoria
        factoriaBOsMock = ctrl.mock(FactoriaBOs.class);
        //Hacemos el mock de la clase operacion
         operacionMock = ctrl.mock(IOperacionBO.class);
        reservaTestable.setFactoria(factoriaBOsMock);
    }


    @Test
    void ReservaC1(){
        //Definimos las entradas y salidas esperadas
        String login = "xxxx";
        String password = "xxxx";
        String IdenSocio = "Pepe";
        String[] isbns = {"33333"};
        String mensajeEsperado = "ERROR de permisos; ";

        //Programamos las secuencias que se deben de seguir
        EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(false);
        ctrl.replay();
        ReservaException exceptionObtenida = assertThrows(ReservaException.class, ()-> reservaTestable.realizaReserva(login,password,IdenSocio,isbns));
        assertEquals(mensajeEsperado, exceptionObtenida.getMessage());
        ctrl.verify();

    }

    @Test
    void ReservaC2(){
        //Definimos las entradas y salidas esperadas
        String login = "ppss";
        String password = "ppss";
        String IdenSocio = "Pepe";
        String[] isbns = {"22222","33333"};

        //Programamos las secuencias que se deben de seguir
        assertDoesNotThrow(()->EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(true));

        EasyMock.expect(factoriaBOsMock.getOperacionBO()).andReturn(operacionMock);

        //Opcion 1

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[0]));
        EasyMock.expectLastCall().andVoid();
        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[1]));
        EasyMock.expectLastCall().andVoid();

        //Opcion 2 Con bucle
        /**
        for (String isbn: isbns){
            Assertions.assertDoesNotThrow(
                    ()->operacionMock.operacionReserva(IdenSocio, isbn)
            );
        }
         **/
        /**
        //Opcion 3
        Assertions.assertDoesNotThrow(()->{
            operacionMock.operacionReserva(IdenSocio,isbns[0]);
            operacionMock.operacionReserva(IdenSocio,isbns[1]);
        });
         **/
        ctrl.replay();
        assertDoesNotThrow(()-> reservaTestable.realizaReserva(login,password,IdenSocio,isbns));
        ctrl.verify();
    }




    @Test
    void ReservaC3(){

        //Definimos las entradas y salidas esperadas
        String login = "ppss";
        String password = "ppss";
        String IdenSocio = "Pepe";
        String[] isbns = {"11111","22222","55555"};
        String mensajeEsperado = "ISBN invalido:11111; ISBN invalido:55555; ";

        //Programamos las secuencias que se deben de seguir
        assertDoesNotThrow(()->EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(true));

        EasyMock.expect(factoriaBOsMock.getOperacionBO()).andReturn(operacionMock);

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[0]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[1]));
        EasyMock.expectLastCall().andVoid();

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[2]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());

        ctrl.replay();

        ReservaException exceptionObtenida = assertThrows(ReservaException.class, ()-> reservaTestable.realizaReserva(login,password,IdenSocio,isbns));
        assertEquals(mensajeEsperado, exceptionObtenida.getMessage());
        ctrl.verify();

    }

    @Test
    void ReservaC4(){


        //Definimos las entradas y salidas esperadas
        String login = "ppss";
        String password = "ppss";
        String IdenSocio = "Luis";
        String[] isbns = {"22222"};
        String mensajeEsperado = "SOCIO invalido; ";

        //Programamos las secuencias que se deben de seguir
        assertDoesNotThrow(()->EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(true));

        EasyMock.expect(factoriaBOsMock.getOperacionBO()).andReturn(operacionMock);

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[0]));
        EasyMock.expectLastCall().andThrow(new SocioInvalidoException());

        ctrl.replay();

        ReservaException exceptionObtenida = assertThrows(ReservaException.class, ()-> reservaTestable.realizaReserva(login,password,IdenSocio,isbns));
        assertEquals(mensajeEsperado, exceptionObtenida.getMessage());
        ctrl.verify();

    }

    @Test
    void ReservaC5(){

        //Definimos las entradas y salidas esperadas
        String login = "ppss";
        String password = "ppss";
        String IdenSocio = "Pepe";
        String[] isbns = {"11111","22222","33333"};
        String mensajeEsperado = "ISBN invalido:11111; CONEXION invalida; ";

        //Programamos las secuencias que se deben de seguir
        assertDoesNotThrow(()->EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(true));

        EasyMock.expect(factoriaBOsMock.getOperacionBO()).andReturn(operacionMock);

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[0]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[1]));
        EasyMock.expectLastCall().andVoid();

        assertDoesNotThrow(()-> operacionMock.operacionReserva(IdenSocio, isbns[2]));
        EasyMock.expectLastCall().andThrow(new JDBCException());

        ctrl.replay();

        ReservaException exceptionObtenida = assertThrows(ReservaException.class, ()-> reservaTestable.realizaReserva(login,password,IdenSocio,isbns));
        assertEquals(mensajeEsperado, exceptionObtenida.getMessage());
        ctrl.verify();

    }

}
