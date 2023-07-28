package ejercicio4;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ejercicio4.excepciones.ReservaException;

import static org.junit.jupiter.api.Assertions.*;
class ReservaTest {

    final String  validLogin      = "ppss";
    final String  validPassword   = "ppss";
    final String  validPartner    = "Luis";
    final String  invalidPartner  = "Pepe";
    final String  validISBNs[]    = {"11111", "22222"};
    final Usuario adminUser       = Usuario.BIBLIOTECARIO;

    ReservaTestable resTestable;
    OperacionStub   opStub;

    @BeforeEach
    void setUp() {
        opStub      = new OperacionStub();
        resTestable = new ReservaTestable();
        resTestable.setValidLogin(validLogin);
        resTestable.setValidPassword(validPassword);
        resTestable.setValidUser(adminUser);
    }


    @Test
    void C1_realizaReserva() {
        String login    = "xxxx";
        String password = "xxxx";
        String socio    = validPartner;
        String ISBNs[]  = {validISBNs[0]};

        OperacionFactory.setOperacion(opStub);

        ReservaException excepcionEsperadda = new ReservaException("ERROR de permisos; ");
        ReservaException excepcionReal = assertThrows(ReservaException.class, () -> resTestable.realizaReserva(login, password, socio, ISBNs));

        assertEquals(excepcionEsperadda.getMessage(), excepcionReal.getMessage());
    }

    @Test
    void C2_realizaReserva() {
        String login    = validLogin;
        String password = validPassword;
        String socio    = validPartner;
        String ISBNs[]  = {validISBNs[0], validISBNs[1]};

        OperacionFactory.setOperacion(opStub);

        assertDoesNotThrow(() -> resTestable.realizaReserva(login, password, socio, ISBNs));
    }

    @Test
    void C3_realizaReserva() {
        String login    = validLogin;
        String password = validPassword;
        String socio    = validPartner;
        String ISBNs[]  = {"33333"};

        opStub.setThrowISBN(true);
        OperacionFactory.setOperacion(opStub);

        ReservaException excepcionEsperadda = new ReservaException("ISBN invalido:33333; ");
        ReservaException excepcionReal = assertThrows(ReservaException.class, () -> resTestable.realizaReserva(login, password, socio, ISBNs));

        assertEquals(excepcionEsperadda.getMessage(), excepcionReal.getMessage());
    }

    @Test
    void C4_realizaReserva() {
        String login    = validLogin;
        String password = validPassword;
        String socio    = invalidPartner;
        String ISBNs[]  = {validISBNs[0]};

        opStub.setThrowSocioInvalido(true);
        OperacionFactory.setOperacion(opStub);

        ReservaException excepcionEsperadda = new ReservaException("SOCIO invalido; ");
        ReservaException excepcionReal = assertThrows(ReservaException.class, () -> resTestable.realizaReserva(login, password, socio, ISBNs));

        assertEquals(excepcionEsperadda.getMessage(), excepcionReal.getMessage());
    }

    @Test
    void C5_realizaReserva() {
        String login    = validLogin;
        String password = validPassword;
        String socio    = validPartner;
        String ISBNs[]  = {validISBNs[0]};

        opStub.setThrowJDBC(true);
        OperacionFactory.setOperacion(opStub);

        ReservaException excepcionEsperadda = new ReservaException("CONEXION invalida; ");
        ReservaException excepcionReal = assertThrows(ReservaException.class, () -> resTestable.realizaReserva(login, password, socio, ISBNs));

        assertEquals(excepcionEsperadda.getMessage(), excepcionReal.getMessage());
    }


}