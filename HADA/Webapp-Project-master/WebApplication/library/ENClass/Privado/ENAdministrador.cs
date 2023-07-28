using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENAdministrador 
    {
        private string email;

        private string password;


        public string emailAdmin
        {
            get { return email; }
            set { email = value; }
        }

        public string passwordAdmin
        {
            get { return password; }
            set { password = value; }
        }

        public ENAdministrador(string email, string password)
        {
            this.email = email;
            this.password = password;
        }

        public ENAdministrador(ENAdministrador admin)
        {
            this.email = admin.email;
            this.password = admin.password;
        }


        public bool readAdmin()
        {
            CADAdministrador admin = new CADAdministrador();
            return admin.readAdministrador(this);
        }

        public bool createAdmin()
        {
            CADAdministrador admin = new CADAdministrador();
            if (!admin.readAdministrador(this))
            {
                return admin.createAdministrador(this);
            }

            return false;
        }



        public bool updateAdmin()
        {
            ENAdministrador aux = new ENAdministrador(this);
            CADAdministrador admin = new CADAdministrador();

            if (admin.readAdministrador(this))
            if (admin.readAdministrador(this))
            {
                this.email = aux.email;
                this.password = aux.password;

                return admin.updateAdministrador(this);
            }

            return false;
        }

        public bool deleteAdmin()
        {
            CADAdministrador admin = new CADAdministrador();

            if (admin.readAdministrador(this))
                return admin.deleteAdministrador(this);

            return false;
        }


        public bool readSesion(ENSesion sesion)
        {
            return sesion.readSesion();
        }

        public bool crearSesion(ENSesion sesion)
        {
            return sesion.createSesion();
        }

        public bool eliminarSesion(ENSesion sesion)
        {
            return sesion.deleteSesion();
        }

        public bool updateSesion(ENSesion sesion)
        {
            return sesion.updateSesion();
        }


        public bool crearTicket(ENTicket ticket)
        {
            return ticket.createTicket();
        }

        public bool readTicket(ENTicket ticket)
        {
            return ticket.readTicket();
        }

        public bool updateTicket(ENTicket ticket)
        {
            return ticket.updateTicket();
        }

        public bool deleteTicket(ENTicket ticket)
        {
            return ticket.deleteTicket();
        }

        public bool createHorario(ENHorario horario)
        {
            return horario.createHorario();
        }
        public bool eliminarHorario(ENHorario horario)
        {
            return horario.deleteHorario();
        }
        public bool readHorario(ENHorario horario)
        {
            return horario.readHorario();
        }
        public bool updateHorario(ENHorario horario)
        {
            return horario.updateHorario();
        }

        public bool mostrarTodosUsuarios()
        {
            return true;
        }

        public bool readUsuario(ENUsuario user)
        {
            return user.readUsuario();
        }

        public bool createUsuario(ENUsuario user)
        {
            return user.createUsuario();
        }

        public bool updateUsuario(ENUsuario user)
        {
            return user.updateUsuario();
        }

        public bool deleteUsuario(ENUsuario user)
        {
            return user.deleteUsuario();
        }

        public bool readDescuento(ENDescuento descuetno)
        {
            return descuetno.readDescuento();
        }

        public bool crearDescuento(ENDescuento descuetno)
        {
            return descuetno.createDescuento();
        }

        public bool updateDescuento(ENDescuento descuento)
        {
            return descuento.updateDescuento();
        }

        public bool eliminarDescuento(ENDescuento descuento)
        {
            return descuento.deleteDescuento();
        }

        public bool crearGenero(ENGenero genero)
        {
            return genero.createGenero();
        }
        public bool readGenero(ENGenero genero)
        {
            return genero.readGenero();
        }

        public bool updateGenero(ENGenero genero)
        {
            return genero.updateGenero();
        }

        public bool deleteGenero(ENGenero genero)
        {
            return genero.deleteGenero();
        }

        public override string ToString()
        {
            return "";
        }

    }
}
