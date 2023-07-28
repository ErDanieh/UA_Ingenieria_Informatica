using library;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication
{
    public partial class Perfil : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            HttpCookie userCookie;
            userCookie = Request.Cookies["UserID"];


            if (userCookie == null)
            {
                Response.Redirect("LogReg.aspx");
            }
            string email = userCookie.Value.ToString();
            ENUsuario user = new ENUsuario();
            user.emailUsuario = email;

            if (!user.readUsuario())
            {
                userCookie.Expires = DateTime.Now.AddDays(-1);
                Response.Redirect("LogReg.aspx");
            }

            if (!Page.IsPostBack)
            {
                nombreUsuario.Text = nombreUsuario.Text + user.nombreUsuario;
            }


            DataTable dt = new DataTable();
            dt = ENPelicula.mostrarMisPelis(email);
            ListView1.DataSource = dt;
            ListView1.DataBind();


        }

        protected void cerrarSesion(object sender, EventArgs e)
        {

            Page.Validate("novalid");
            if (Page.IsValid)
            {
                HttpCookie userCookie = new HttpCookie("UserID");
                userCookie.Expires = DateTime.Now.AddDays(-1);
                Response.Cookies.Add(userCookie);
                Response.Redirect("Index.aspx");
            }
        }


        protected void eliminarPendientes(object sender, EventArgs e)
        {

            Page.Validate("novalid");

            if (Page.IsValid)
            {
                HttpCookie userCookie;
                userCookie = Request.Cookies["UserID"];

                ENUsuario user = new ENUsuario();
                user.emailUsuario = userCookie.Value.ToString();

                user.deletePendientesTodas();
                Response.Redirect("Perfil.aspx");
            }
        }


        protected void renderCalendario(object sender, DayRenderEventArgs e)
        {

        }

        protected void onmisTickets(object sender, EventArgs e)
        {
            Response.Redirect("MisTickets.aspx");
        }

        public string PassHash(string password)
        {
            SHA1 sha = SHA1.Create();
            byte[] hashpassword = sha.ComputeHash(Encoding.Default.GetBytes(password));
            StringBuilder value = new StringBuilder();
            for (int i = 0; i < hashpassword.Length; i++)
            {
                value.Append(hashpassword[i].ToString());
            }
            return value.ToString();
        }
    }
}