package ejercicio4;

import ejercicio4.excepciones.IsbnInvalidoException;
import ejercicio4.excepciones.JDBCException;
import ejercicio4.excepciones.SocioInvalidoException;

public class Operacion implements IOperacionBO {
    @Override
    public void operacionReserva(String socio, String isbn) throws IsbnInvalidoException, JDBCException, SocioInvalidoException{

    }
}
