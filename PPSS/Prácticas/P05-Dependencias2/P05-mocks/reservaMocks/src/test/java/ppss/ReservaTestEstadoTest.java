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
public class ReservaTestEstadoTest {
    Reserva reservaTestable;
    FactoriaBOs factoriaBOsStub;

    IOperacionBO operacionStub;
    @BeforeEach
    void setup(){
        reservaTestable  = EasyMock.partialMockBuilder(Reserva.class).addMockedMethod("compruebaPermisos").niceMock();
        factoriaBOsStub = EasyMock.niceMock(FactoriaBOs.class);
        operacionStub = EasyMock.niceMock(IOperacionBO.class);
        reservaTestable.setFactoria(factoriaBOsStub);
    }

    @Test
    void ReservaStubTestC1 (){

        String login = "xxxx";
        String password = "xxxx";
        String IdenSocio = "Pepe";
        String[] isbns = {"33333"};
        String mensajeEsperado = "ERROR de permisos; ";
        EasyMock.expect(reservaTestable.compruebaPermisos(login,password, Usuario.BIBLIOTECARIO)).andReturn(false);
        EasyMock.replay(reservaTestable,factoriaBOsStub,operacionStub);
        ReservaException exceptionObtenida = assertThrows(ReservaException.class, ()-> reservaTestable.realizaReserva(login,password,IdenSocio,isbns));
        assertEquals(mensajeEsperado,exceptionObtenida.getMessage());
        EasyMock.verify(reservaTestable,factoriaBOsStub,operacionStub);
    }

    @Test
    void ReservaStubTestC2 (){


        String login = "ppss";
        String password = "ppss";
        String IdenSocio = "Pepe";
        String[] isbns = {"22222","33333"};


        EasyMock.expect(reservaTestable.compruebaPermisos(login,password, Usuario.BIBLIOTECARIO)).andReturn(true);
        EasyMock.expect(factoriaBOsStub.getOperacionBO()).andReturn(operacionStub);

        assertDoesNotThrow(()-> operacionStub.operacionReserva(IdenSocio, isbns[0]));
        EasyMock.expectLastCall().andVoid();
        assertDoesNotThrow(()-> operacionStub.operacionReserva(IdenSocio, isbns[1]));
        EasyMock.expectLastCall().andVoid();


        EasyMock.replay(reservaTestable,factoriaBOsStub,operacionStub);

        assertDoesNotThrow(()-> reservaTestable.realizaReserva(login,password,IdenSocio,isbns));

        EasyMock.verify(reservaTestable,factoriaBOsStub,operacionStub);
    }

    @Test
    void ReservaStubTestC3(){


        //Programamos entradas y salidas
        String login = "ppss";
        String password = "ppss";
        String idenSocio = "Pepe";
        String isbns[] = {"11111","22222","55555"};
        String mensajeEsperado = "ISBN invalido:11111; ISBN invalido:55555; ";


        //Programamos las expectativas\
        EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(true);

        EasyMock.expect(factoriaBOsStub.getOperacionBO()).andReturn(operacionStub);
        assertDoesNotThrow(()->operacionStub.operacionReserva(idenSocio,isbns[0]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());
        assertDoesNotThrow(()->operacionStub.operacionReserva(idenSocio,isbns[1]));
        EasyMock.expectLastCall().andVoid();
        assertDoesNotThrow(()->operacionStub.operacionReserva(idenSocio,isbns[2]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());

        EasyMock.replay(reservaTestable,factoriaBOsStub,operacionStub);

        ReservaException ex = assertThrows(ReservaException.class,()-> reservaTestable.realizaReserva(login,password,idenSocio,isbns));

        assertEquals(mensajeEsperado,ex.getMessage());
    }

    @Test
    void ReservaStubTestC4(){


        //Programamos entradas y salidas
        String login = "ppss";
        String password = "ppss";
        String idenSocio = "Luis";
        String isbns[] = {"22222"};
        String mensajeEsperado = "SOCIO invalido; ";


        //Programamos las expectativas\
        EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(true);

        EasyMock.expect(factoriaBOsStub.getOperacionBO()).andReturn(operacionStub);

        assertDoesNotThrow(()->operacionStub.operacionReserva(idenSocio,isbns[0]));
        EasyMock.expectLastCall().andThrow(new SocioInvalidoException());

        EasyMock.replay(reservaTestable,factoriaBOsStub,operacionStub);

        ReservaException ex = assertThrows(ReservaException.class,()-> reservaTestable.realizaReserva(login,password,idenSocio,isbns));

        assertEquals(mensajeEsperado,ex.getMessage());
    }

    @Test
    void ReservaStubTestC5(){


        //Programamos entradas y salidas
        String login = "ppss";
        String password = "ppss";
        String idenSocio = "Pepe";
        String isbns[] = {"11111","22222","33333"};
        String mensajeEsperado = "ISBN invalido:11111; CONEXION invalida; ";


        //Programamos las expectativas\
        EasyMock.expect(reservaTestable.compruebaPermisos(login,password,Usuario.BIBLIOTECARIO)).andReturn(true);

        EasyMock.expect(factoriaBOsStub.getOperacionBO()).andReturn(operacionStub);
        assertDoesNotThrow(()->operacionStub.operacionReserva(idenSocio,isbns[0]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());
        assertDoesNotThrow(()->operacionStub.operacionReserva(idenSocio,isbns[1]));
        EasyMock.expectLastCall().andVoid();
        assertDoesNotThrow(()->operacionStub.operacionReserva(idenSocio,isbns[2]));
        EasyMock.expectLastCall().andThrow(new JDBCException());

        EasyMock.replay(reservaTestable,factoriaBOsStub,operacionStub);

        ReservaException ex = assertThrows(ReservaException.class,()-> reservaTestable.realizaReserva(login,password,idenSocio,isbns));

        assertEquals(mensajeEsperado,ex.getMessage());
    }


}
