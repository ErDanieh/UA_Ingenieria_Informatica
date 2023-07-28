using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{

    public class CADLogin
    {
        private String constring;
        public CADLogin(ENIntegrante login)
        {
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
        }

        public bool createLogin(ENLogin login) // En la clase EN no esta completado.
        {
            return false;
        }

        public bool credencialesValidas(ENLogin login) // En la clase EN no esta completado.
        {
            return false;
        }

        public bool readUserData(ENLogin login) // En la clase EN no esta completado.
        {
            CADUsuario cUsuario = new CADUsuario();
            //return cUsuario.readUsuario(login.emailLogin);                       Me da error 
            return true;
        }

        public bool readAdminData(ENLogin login) // En la clase EN no esta completado.
        {
            return false;
        }
        public override string ToString()
        {
            return null;
        }
    }
}
