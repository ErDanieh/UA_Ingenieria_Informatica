using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication
{
    public partial class ControlAdmin : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void adminPeliculas(object sender, EventArgs e)
        {
            Response.Redirect("AdminPelicula.aspx");
        }

        protected void adminUsers(object sender, EventArgs e)
        {
            Response.Redirect("AdminUser.aspx");
        }

        protected void adminSala(object sender, EventArgs e)
        {
            Response.Redirect("AdminSala.aspx");
        }

        protected void adminHorarios(object sender, EventArgs e)
        {
            Response.Redirect("AdminHorario.aspx");
        }

        protected void adminSesion(object sender, EventArgs e)
        {
            Response.Redirect("AdminSesion.aspx");
        }

        protected void CloseSesion(object sender, EventArgs e)
        {
            HttpCookie userCookie = new HttpCookie("UserID");
            userCookie.Expires = DateTime.Now.AddDays(-1);
            Response.Cookies.Add(userCookie);
            Response.Redirect("Index.aspx");
        }
    }
}