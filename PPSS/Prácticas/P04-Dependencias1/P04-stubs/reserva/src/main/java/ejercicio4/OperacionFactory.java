package ejercicio4;

public class OperacionFactory {

    private static IOperacionBO operacion = null;

    public static IOperacionBO create(){
        if(operacion != null){
            return operacion;
        }else{
            return new Operacion();
        }
    }

    public static void setOperacion(IOperacionBO operacion1){
        operacion = operacion1;
    }

}
