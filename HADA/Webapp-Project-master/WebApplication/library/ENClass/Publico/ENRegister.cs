using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Mail;

namespace library
{
    public class ENRegister
    {
        private string email;

        private string nombre;

        private string apellido;

        private string password;

        private int edad;

        public string emailRegister
        {
            get { return email; }
            set { email = value; }
        }

        public string nombreRegister
        {
            get { return nombre; }
            set { nombre = value; }
        }

        public string apellidoRegister
        {
            get { return apellido; }
            set { apellido = value; }
        }

        public string passwordRegister
        {
            get { return password; }
            set { password = value; }
        }

        public int edadRegister
        {
            get { return edad; }
            set { edad = value; }
        }

        public ENRegister(string email, string nombre, string apellido, string password, int edad)
        {
            this.email = email;
            this.nombre = nombre;
            this.apellido = apellido;
            this.password = password;
            this.edad = edad;
        }

        public ENRegister(ENRegister registro)
        {
            this.email = registro.email;
            this.nombre = registro.nombre;
            this.apellido = registro.apellido;
            this.password = registro.password;
            this.edad = registro.edad;
        }

        public bool createUser()
        {
            CADUsuario user = new CADUsuario();

            return true; 
        }

        public override string ToString()
        {
            return null;
        }

        public static bool emailIsValid(string emailaddress)
        {
            try
            {
                MailAddress m = new MailAddress(emailaddress);

                return true;
            }
            catch (FormatException)
            {
                return false;
            }
        }
    }
}
