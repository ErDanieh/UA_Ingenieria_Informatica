package ejercicio3;

public class AlquilaCochesTestable extends AlquilaCoches {


    IService s;

    public AlquilaCochesTestable(IService ser){
        this.s = ser;
    }

    @Override
    public IService getServicio(){
        return s;
    }

    public void setCalendario(Calendario c){
        calendario = c;
    }

}
