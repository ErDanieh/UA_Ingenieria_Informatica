using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mail;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Security.Cryptography;
using library;
using System.Text;

namespace WebApplication
{
    public partial class LogReg : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            HttpCookie userCookie;
            userCookie = Request.Cookies["UserID"];
            if (userCookie != null)
            {
                Response.Redirect("Perfil.aspx");
            }
        }


        protected void requestLogin(object sender, EventArgs e)
        {
            Page.Validate("loginGroup");
            if (Page.IsValid)
            {
                ENUsuario user = new ENUsuario();
                user.emailUsuario = emailLogin.Text;
                HttpCookie userCookie;
                string password = PassHash(passwordLogin.Text);

                if (emailLogin.Text != "" && passwordLogin.Text != "" && user.readUsuario())
                {
                    if (user.passwordUsuario == password)
                    {
                        userCookie = new HttpCookie("UserID", emailLogin.Text);
                        userCookie.Expires = DateTime.Now.AddMonths(1);
                        Response.Cookies.Add(userCookie);
                        Response.Redirect("Perfil.aspx");
                    }
                    else
                    {
                        outputMsg.Text = "Contraseña invalida.";
                    }
                }
                else
                {
                    outputMsg.Text = "El usuario con email " + emailLogin.Text + "no existe.";

                }
            }
        }

        protected void requestRegister(object sender, EventArgs e)
        {
            Page.Validate("registerGroup");
            if (Page.IsValid)
            {


                ENUsuario user = new ENUsuario();

                string nombre = nombreApellidos.Text;
                string apellidosU = apellidos.Text;
                bool nomFin = false;
                int tipoUsuario = 4;

                



                HttpCookie userCookie;

                if (edadRegister.Text != null && nombreApellidos.Text != "" && apellidos.Text != "" && emailReg.Text != "" && passwordReg.Text != "" && !user.readUsuario())
                {
                    user.nombreUsuario = nombre;
                    user.apellidoUsuario = apellidosU;
                    user.emailUsuario = emailReg.Text;
                    user.edadUsuario = int.Parse(edadRegister.Text);
                    user.passwordUsuario = PassHash(passwordReg.Text);
                    user.tipoUsuario = 0;

                    ENDescuento descuento = new ENDescuento(4);

                    if (user.edadUsuario <= 7) descuento.rangoDescuento = 1;
                    else if (user.edadUsuario <= 23) descuento.rangoDescuento = 2;
                    else if (user.edadUsuario >= 65) descuento.rangoDescuento = 3;
                    user.descuentosUsuario = descuento;

                    if (user.createUsuario())
                    {
                        SmtpClient smtpClient = new SmtpClient("smtp.gmail.com", 587);
                        MailMessage message = new MailMessage();
                        try
                        {
                            MailAddress fromAddress = new MailAddress("cinemahubua@gmail.com", "Administración Cinehub");
                            MailAddress toAddress = new MailAddress(emailReg.Text, nombre);
                            message.From = fromAddress;
                            message.To.Add(toAddress);
                            message.Subject = "BIENVENIDO A CINEHUB";
                            message.Body = "Acabas de registrarte en nuestra web. \n" + "Su nombre es: " + nombre + "\n Su contraseña es: " + passwordReg.Text + "\n Su edad es: " + edadRegister.Text + "\n Gracias por confiar en nosotros.";
                            smtpClient.EnableSsl = true;
                            smtpClient.Credentials = new System.Net.NetworkCredential("cinemahubua@gmail.com", "cinemahub22*");
                            smtpClient.Send(message);

                        }
                        catch (Exception ex)
                        {

                        }
                        userCookie = new HttpCookie("UserID", emailReg.Text);
                        userCookie.Expires = DateTime.Now.AddMonths(1);
                        Response.Cookies.Add(userCookie);
                        Response.Redirect("Perfil.aspx");
                    }
                    else
                    {
                        outputMsg.Text = "No se ha podido crear el usuario. Error.";
                    }
                }
                else
                {
                    outputMsg.Text = "Email no valido: " + emailLogin.Text + " ya esta registrado";

                }

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
    }
}