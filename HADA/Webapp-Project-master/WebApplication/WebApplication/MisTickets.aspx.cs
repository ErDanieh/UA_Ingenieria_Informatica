using library;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication
{
    public partial class MisTickets : System.Web.UI.Page
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
                DataTable dt = new DataTable();
                dt = ENPelicula.mostrarPelisVistas(email);
                ListView1.DataSource = dt;
                ListView1.DataBind();
            

        }

        protected void onVolver(object sender, EventArgs e)
        {
            Response.Redirect("Perfil.aspx");
        }

    }
}