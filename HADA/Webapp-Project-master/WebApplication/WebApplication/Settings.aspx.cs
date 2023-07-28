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
    public partial class Settings : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                HttpCookie userCookie;
                userCookie = Request.Cookies["UserID"];


                if (userCookie == null)
                {
                    Response.Redirect("LogReg.aspx");
                }

                ENUsuario user = new ENUsuario();
                string email = userCookie.Value.ToString();
                user.emailUsuario = email;

                if (!user.readUsuario())
                {
                    Response.Redirect("LogReg.aspx");
                }
            }
            catch(Exception)
            {
                Response.Redirect("LogReg.aspx");
            }


        }


        protected void cambiarContra(object sender, EventArgs e)
        {
            try
            {
                Page.Validate("groupPassword");

                if (Page.IsValid)
                {
                    HttpCookie userCookie;
                    userCookie = Request.Cookies["UserID"];

                    ENUsuario user = new ENUsuario();
                    user.emailUsuario = userCookie.Value.ToString();

                    if (!user.readUsuario())
                    {
                        Response.Redirect("LogReg.aspx");
                    }

                    else if (nuevaPassword.Text != confirmarContraseña.Text)
                    {
                        resultadoCambioContra.Text = "Contraseña de confirmacion distinta.";
                    }

                    else if (user.passwordUsuario != PassHash(antiguaPassword.Text))
                    {
                        resultadoCambioContra.Text = "Contraseña de usuario incorrecta.";
                    }

                    else
                    {
                        user.passwordUsuario = PassHash(nuevaPassword.Text);
                        user.updateUsuario();
                        resultadoCambioContra.Text = "Contraseña de usuario cambiada.";
                    }
                }

            }
            catch (Exception)
            {
                Response.Redirect("ErrorPage.aspx");
            }

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

        protected void eliminarUsuario_Click(object sender, EventArgs e)
        {
            try
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

                if (Page.IsValid)
                {
                    if (user.deletePendientesTodas() == true && user.deleteUsuario() == true)
                    {
                    }

                    user.deleteUsuario();
                    userCookie.Expires = DateTime.Now.AddDays(-1);
                    Response.Cookies.Add(userCookie);
                    //Response.Redirect("Index.aspx");
                }


            }
            catch(Exception)
            {

            }
        }

        protected void cambiarNombre(object sender, EventArgs e)
        {
            try
            {
                Page.Validate("groupNombreApellido");

                if (Page.IsValid)
                {
                    HttpCookie userCookie;
                    userCookie = Request.Cookies["UserID"];

                    ENUsuario user = new ENUsuario();
                    user.emailUsuario = userCookie.Value.ToString();

                    if (!user.readUsuario())
                    {
                        Response.Redirect("LogReg.aspx");
                    }

                    else
                    {
                        user.nombreUsuario = nuevoNombre.Text;
                        user.apellidoUsuario = nuevoApellido.Text;
                        user.updateUsuario();
                    }
                }

            }
            catch (Exception)
            {
                Response.Redirect("ErrorPage.aspx");
            }
        }
    }
}