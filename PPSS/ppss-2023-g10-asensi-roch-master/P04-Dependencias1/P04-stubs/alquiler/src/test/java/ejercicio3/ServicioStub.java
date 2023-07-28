package ejercicio3;

public class ServicioStub implements IService{

    int precio;

    //Constructor para el stub
    public ServicioStub(int precioInyectado){
        precio = precioInyectado;
    }

    @Override
    public float consultaPrecio(TipoCoche tipo){
        return precio;
    }
}
