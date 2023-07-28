package ejercicio4;



import ejercicio4.excepciones.JDBCException;
import ejercicio4.excepciones.SocioInvalidoException;
import ejercicio4.excepciones.IsbnInvalidoException;
import ejercicio4.excepciones.ReservaException;

import java.util.ArrayList;

public class Reserva {
    public boolean compruebaPermisos(String login, String password, Usuario tipoUsu) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    public void realizaReserva(String login, String password,
                               String socio, String [] isbns) throws ReservaException {

        ArrayList<String> errores = new ArrayList<>();

        //Dependencia Externa le hacemos override en el testeable
        if(!compruebaPermisos(login, password, Usuario.BIBLIOTECARIO)) {
            errores.add("ERROR de permisos");
        } else {
            //Dependencia Externa creamos una factoria de operaciones
            //IOperacionBO io = new Operacion();
            IOperacionBO io = OperacionFactory.create();
            try {
                for(String isbn: isbns) {
                    try {
                        //Dependencia Externa
                        io.operacionReserva(socio, isbn);
                    } catch (IsbnInvalidoException iie) {
                        errores.add("ISBN invalido" + ":" + isbn);
                    }
                }
            } catch (SocioInvalidoException sie) {
                errores.add("SOCIO invalido");
            } catch (JDBCException je) {
                errores.add("CONEXION invalida");
            }
        }
        if (errores.size() > 0) {
            String mensajeError = "";
            for(String error: errores) {
                mensajeError += error + "; ";
            }
            throw new ReservaException(mensajeError);
        }
    }
}
