package ejercicio2;

import java.util.Calendar;

public class GestorLlamadas {

    private static final double TARIFA_NOCTURNA = 10.5;

    private static final double TARIFA_DIURNA = 20.8;

    public Calendario getCalendario(){
        Calendario c = new Calendario();
        return c;
    }

    public double calculaConsumo(int minutos){
        Calendario c = getCalendario(); //Dependencia Externa misma clase hago testeable con extends
        int hora = c.getHoraActual(); //Dependencia Externa otra clase hago un stub con extends
        if (hora < 8 || hora > 20){
            return minutos * TARIFA_NOCTURNA;
        }
        else{
            return minutos * TARIFA_DIURNA;
        }
    }

}
