using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENLogin
    {

        private string email;

        private string password;

        private ENUsuario user;

        private ENAdministrador admin;

        public string emailLogin
        {
            get { return email; }
            set { email = value; }
        }


        public string passwordLogin
        {
            get { return password; }
            set { password = value; }

        }

        public ENUsuario userLogin
        {
            get { return user; }
            set { user = value; }
        }

        public ENAdministrador adminLogin
        {
            get { return admin; }
            set { admin = value; }
        }

        public ENLogin()
        {
            this.email = "";
            this.password = "";
            this.user = null;
            this.admin = null;
        }

        public ENLogin(string email, string password)
        {
            this.email = email;
            this.password = password;
            this.user = null;
            this.admin = null;
        }

        public ENLogin(ENLogin login)
        {
            this.email = login.email;
            this.password = login.password;
            this.user = login.user;
            this.admin = login.admin;
        }

        public bool credencialesValidas(ENLogin log)
        {
            return false;
        }

        public bool readUserData()
        {
            return false;
        }

        public bool readAdminData()
        {
            return false;
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

        public override string ToString()
        {
            return null;
        }

    }
}
