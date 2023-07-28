using library.CADClass.Privado;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENComprar
    {

        private ENTicket ticket;

        private ENUsuario usuario;

        private int importe;

        public ENTicket ticketComprar
        {
            get { return ticket; }
            set { ticket = value; }
        }

        public ENUsuario usuarioComprar
        {
            get { return usuario; }
            set { usuario = value; }
        }

        public int importeComprar
        {
            get { return importe; }
            set { importe = value; }
        }

        public ENComprar(ENTicket ticket, ENUsuario usuario, ENAsiento asiento, int importe)
        {
            this.ticket = ticket;
            this.usuario = usuario;
            this.importe = importe;
        }


        public ENComprar(ENComprar compra)
        {
            this.ticket = compra.ticket;
            this.usuario = compra.usuario;
            this.importe = compra.importe;
        }


        public bool createComprar()
        {
            CADComprar compra = new CADComprar();
            if (!compra.readComprar(this))
                return compra.createComprar(this);

            return false;
        }

        public bool readComprar()
        {
            CADComprar compra = new CADComprar();
            return compra.readComprar(this);
        }

        public bool updateComprar()
        {
            ENComprar aux = new ENComprar(this);
            CADComprar compra = new CADComprar();

            if (compra.readComprar(this))
            {
                this.ticket = aux.ticket;
                this.usuario = aux.usuario;
                this.importe = aux.importe;

                return compra.updateComprar(this);
            }

            return false;
        }

        public bool deleteComprar()
        {
            CADComprar compra = new CADComprar();

            if (compra.readComprar(this))
                return compra.deleteComprar(this);

            return false;
        }

        public int importeFinal()
        {
            return importe - (importe * usuario.getDescuento());
        }

        public override string ToString()
        {
            return "Ticket: " + ticket.idTicket + ". Comprador: " + usuario + ". Importe: " + importe;
        }
    }
}
