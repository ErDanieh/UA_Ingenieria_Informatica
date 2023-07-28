using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace WebApplication
{
    public partial class Site1 : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            HttpCookie userCookie;
            userCookie = Request.Cookies["UserID"];
            ENUsuario user = new ENUsuario();
            string email = "";


            MenuItemCollection menuItems = MennuNav.Items;
            MenuItem adminItem = new MenuItem();

            if(userCookie != null)
            {
                email = userCookie.Value.ToString();
                user.emailUsuario = email;
            }

            if (userCookie == null )
            {
                foreach (MenuItem menuItem in menuItems)
                {
                    if (menuItem.Text == "Administrar") adminItem = menuItem;
                }
                menuItems.Remove(adminItem);
            }
            else
            {
                if(!user.readUsuario() || !user.isAdmin(email))
                {
                    foreach (MenuItem menuItem in menuItems)
                    {
                        if (menuItem.Text == "Administrar") adminItem = menuItem;
                    }
                    menuItems.Remove(adminItem);
                }
            }

        }


        protected void iconoPerfil_Click(object sender, ImageClickEventArgs e)
        {
            HttpCookie userCookie;
            userCookie = Request.Cookies["UserID"];


            if (userCookie == null)
            {
                Response.Redirect("LogReg.aspx");
            }

            else
            {
                Response.Redirect("Perfil.aspx");
            }
        }



        protected void tbBuscador_TextChanged(object sender, EventArgs e)
        {
            TextBox a = (TextBox)sender;
            Response.Redirect("Index.aspx?par1=" + a.Text);
        }

    }
}