using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENTicket
    {
        private int id;

        private ENAsiento asiento;

        private ENUsuario usuario;

        public ENAsiento asientoTicket
        {
            get { return asiento; }
            set { asiento = value; }
        }

        public ENUsuario usuarioTicket
        {
            get { return usuario; }
            set { usuario = value; }
        }

        public int idTicket
        {
            get { return id; }
            set { id = value; }
        }

        public ENTicket(ENAsiento asiento, ENUsuario usuario, int id)
        {
            this.asiento = asiento;
            this.usuario = usuario;
            this.id = id;
        }

        public ENTicket(ENTicket ticket)
        {
            this.id = ticket.id;
            this.usuario = ticket.usuario;
            this.asiento = ticket.asiento;
        }

        public bool createTicket()
        {
            CADTicket ticket = new CADTicket();
            if (!ticket.readTicket(this))
            {
                return ticket.createTicket(this);
            }

            return false;
        }

        public bool readTicket()
        {
            CADTicket ticket = new CADTicket();
            return ticket.readTicket(this);
        }

        public bool updateTicket()
        {
            ENTicket aux = new ENTicket(this);
            CADTicket ticket = new CADTicket();

            if (ticket.readTicket(this))
            {
                this.asiento = aux.asiento;
                this.usuario = aux.usuario;

                return ticket.updateTicket(this);
            }

            return false;
        }

        public bool deleteTicket()
        {
            CADTicket ticket = new CADTicket();

            if (ticket.readTicket(this))
                return ticket.deleteTicket(this);

            return false;
        }

        public override string ToString()
        {
            return "Ticket: " + this.id + ". Propietario: " + this.usuario.nombreUsuario + ". Asiento: " + asiento.idAsiento;
        }

    }
}
