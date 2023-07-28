package ejercicio2;


public class GestorLlamadasTesteable extends GestorLlamadas{

    Calendario c;

    @Override
    public Calendario getCalendario(){return c;}

    //Con el setter damos el valor que queremos
    public void SetCalendario(Calendario ca) {c = ca;}
}
