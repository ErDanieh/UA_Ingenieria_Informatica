package ejercicio4;

import ejercicio4.excepciones.IsbnInvalidoException;
import ejercicio4.excepciones.SocioInvalidoException;
import ejercicio4.excepciones.JDBCException;

public class OperacionStub implements IOperacionBO{
    private boolean throwISBN = false;
    private boolean throwJDBC = false;
    private boolean throwSocioInvalido = false;

    public void setThrowISBN(boolean throwISBN) {
        this.throwISBN = throwISBN;
    }

    public void setThrowJDBC(boolean throwJDBC) {
        this.throwJDBC = throwJDBC;
    }

    public void setThrowSocioInvalido(boolean throwSocioInvalido) {
        this.throwSocioInvalido = throwSocioInvalido;
    }

    @Override
    public void operacionReserva(String socio, String isbn) throws IsbnInvalidoException, JDBCException, SocioInvalidoException {
        if(throwISBN) throw new IsbnInvalidoException();
        if(throwJDBC) throw new JDBCException();
        if(throwSocioInvalido) throw new SocioInvalidoException();
    }
}
