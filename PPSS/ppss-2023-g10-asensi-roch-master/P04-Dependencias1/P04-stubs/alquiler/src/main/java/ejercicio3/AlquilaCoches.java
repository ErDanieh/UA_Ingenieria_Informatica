package ejercicio3;


import java.time.LocalDate;
public class AlquilaCoches {
    protected Calendario calendario = new Calendario();

    //Factoria Local para la dependencia
    protected IService getServicio (){
        return new Servicio();
    }

    public Ticket calculaPrecio(TipoCoche tipo, LocalDate inicio, int ndias)
            throws MensajeException {
        //No es dependencia porque es lo que devolvemos
        Ticket ticket = new Ticket();
        float precioDia,precioTotal =0.0f;
        float porcentaje = 0.25f;

        String observaciones = "";

        //Dependencia
        //IService servicio = new Servicio();
        IService servicio = getServicio();
        //Dependencia tenemos que hacer override
        precioDia = servicio.consultaPrecio(tipo);

        for (int i=0; i<ndias;i++) {
            //No es dependencia libreria standart
            LocalDate otroDia = inicio.plusDays((long)i);
            try {
                //Dependencia
                if (calendario.es_festivo(otroDia)) {
                    precioTotal += (1+ porcentaje)*precioDia;
                } else {
                    precioTotal += (1- porcentaje)*precioDia;
                }
            } catch (CalendarioException ex) {
                observaciones += "Error en dia: "+otroDia+"; ";
            }
        }

        if (observaciones.length()>0) {
            throw new MensajeException(observaciones);
        }

        ticket.setPrecio_final(precioTotal);
        return ticket;
    }
}
