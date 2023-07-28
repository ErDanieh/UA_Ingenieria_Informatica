package ppss;

public class Cine {


    public boolean[] asientos;
    public boolean reservaButacasV1(boolean[] asientos, int solicitados)
                                throws ButacasException {

        boolean reserva = false;
        int j = 0;
        int sitiosLibres = 0;
        int primerLibre;

        if(solicitados > 0) {

            if(solicitados > asientos.length){
                throw new ButacasException("No se puede procesar la solicitud");
            }

            while ((j < asientos.length) && (sitiosLibres < solicitados)) {
                if (!asientos[j]) {
                    sitiosLibres++;
                } else {
                    sitiosLibres = 0;
                }
                j++;
            }
            if (sitiosLibres == solicitados) {
                primerLibre = (j - solicitados);
                reserva = true;
                for (int k = primerLibre; k < (primerLibre + solicitados); k++) {
                    asientos[k] = true;
                }
            }

        }
        this.asientos =  asientos;
        return reserva;
    }
}
