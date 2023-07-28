using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENUsuario
    {
        private string email;

        private string nombre;

        private string apellido;

        private string password;

        private int edad;

        private int tipo;

        private ENPelicula[] vistas;

        private ENPelicula[] pendientes;

        private ENDescuento descuento;

        private ENTicket[] tickets;

        public string emailUsuario
        {
            get { return email; }
            set { email = value; }
        }

        public string nombreUsuario
        {
            get { return nombre; }
            set { nombre = value; }
        }

        public string apellidoUsuario
        {
            get { return apellido; }
            set { apellido = value; }
        }

        public string passwordUsuario
        {
            get { return password; }
            set { password = value; }
        }

        public int edadUsuario
        {
            get { return edad; }
            set { edad = value; }
        }

        public int tipoUsuario
        {
            get { return tipo; }
            set { tipo = value; }
        }


        public ENPelicula[] vistasUsuario
        {
            get { return vistas; }
            set { vistas = value; }
        }

        public ENPelicula[] pendientesUsuario
        {
            get { return pendientes; }
            set { pendientes = value; }
        }

        public ENDescuento descuentosUsuario
        {
            get { return descuento; }
            set { descuento = value; }
        }

        public ENTicket[] ticketsUsuario
        {
            get { return tickets; }
            set { tickets = value; }
        }

        public ENUsuario()
        {
            this.email = "";
            this.nombre = "";
            this.apellido = "";
            this.password = "";
            this.edad = 0;
        }

        public ENUsuario(string email, string nombre, string apellido, string password, int edad)
        {
            this.email = email;
            this.nombre = nombre;
            this.apellido = apellido;
            this.password = password;
            this.edad = edad;
        }

        public ENUsuario(ENUsuario usuario)
        {
            this.email = usuario.email;
            this.nombre = usuario.nombre;
            this.apellido = usuario.apellido;
            this.password = usuario.password;
            this.edad = usuario.edad;
            this.tipo = usuario.tipo;
        }

        public bool readUsuario()
        {
            CADUsuario usuario = new CADUsuario();
            return usuario.readUsuario(this);
        }

        public bool createUsuario()
        {
            CADUsuario usuario = new CADUsuario();
            if (!usuario.readUsuario(this))
            {
                return usuario.createUsuario(this);
            }

            return false;
        }



        public bool updateUsuario()
        {
            ENUsuario aux = new ENUsuario(this);
            CADUsuario usuario = new CADUsuario();

            if (usuario.readUsuario(this))
            {
                this.email = aux.email;
                this.nombre = aux.nombre;
                this.apellido = aux.apellido;
                this.password = aux.password;
                this.edad = aux.edad;

                return usuario.updateUsuario(this);
            }

            return false;
        }

        public bool deleteUsuario()
        {
            CADUsuario usuario = new CADUsuario();

            if (usuario.readUsuario(this)) 
                return usuario.deleteUsuario(this);

            return false;
        }

        public bool addPendientes(ENPelicula pelicula)
        {
            CADUsuario user = new CADUsuario();

            if (pelicula != null && user.readUsuario(this))
            {
                return user.addPendientes(this, pelicula);
            }

            return false;
        }

        public bool deletePendientes(ENPelicula pelicula)
        {
            CADUsuario user = new CADUsuario();

            if (pelicula != null && user.readUsuario(this))
            {
                return user.deletePendientes(this, pelicula);
            }

            return false;
        }


        public bool deletePendientesTodas()
        {
            CADUsuario user = new CADUsuario();

            if (user.readUsuario(this))
            {
                return user.deletePendientesTodas(this);
            }
    
            return false;
        }


        public bool addVistas(ENPelicula pelicula)
        {
            CADUsuario user = new CADUsuario();
            ENUsuario auxUser = new ENUsuario(this);

            if (pelicula != null && user.readUsuario(this) )
            {
                //this.vistas.Append(pelicula);
                return user.addVistas(auxUser, pelicula);
            }

            return false;
        }

        public bool deleteVistas(ENPelicula pelicula)
        {
            CADUsuario user = new CADUsuario();

            if (pelicula != null && user.readUsuario(this) && !vistas.Contains(pelicula))
            {
                vistas = pendientes.Where(val => val != pelicula).ToArray();
                return user.deleteVistas(pelicula);
            }

            return false;
        }

        public bool deleteVistasTodas()
        {
            CADUsuario user = new CADUsuario();

            if (user.readUsuario(this))
            {
                return user.deleteVistasTodas(this);
            }

            return false;
        }

        public bool isAdmin(string email)
        {
            CADUsuario usuario = new CADUsuario();
            return usuario.isAdmin(email);
        }

        public int getDescuento()
        {
            if (edad <= 7) return 100;
            else if (edad >= 21 && edad <= 23) return 20;
            else if (edad >= 65) return 30;
            return 0;
        }

        public override string ToString()
        {
            return "Email: " + email + ". Nombre: " + nombre;
        }

       

    }
}
