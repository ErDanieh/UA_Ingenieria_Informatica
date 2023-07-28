using MessagingToolkit.QRCode.Codec;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.Mail;
using System.Net;
using System.Web;
using System.Data.SqlTypes;
using System.Data.SqlClient;
using System.Data.Common;
using System.Data;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;
using System.Text;
using System.Net.Mime;

namespace WebApplication
{
    public partial class CompraCheckout : System.Web.UI.Page
    {
        static int numIMG = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            ENPelicula pParam = new ENPelicula();
            try
            {
                pParam.idPelicula = int.Parse(Request.QueryString["p"]);
                pParam.readPelicula();

            }
            catch (HttpRequestValidationException)
            {
                Response.Redirect("ErrorPage.aspx");

            }
            catch (NullReferenceException)
            {
                Response.Redirect("ErrorPage.aspx");
            }
            finally
            {
                nombrePelicula.Text = pParam.nombrePelicula;
                imagenPelicula.ImageUrl = pParam.imgPelicula;
            }

            Label2.Text = Request.QueryString["PR"] + "€";
            Label3.Text = Request.QueryString["NUM"];


        }


        protected void pagar_Click(object sender, EventArgs e)
        {
            HttpCookie userCookie;
            userCookie = Request.Cookies["UserID"];
            SmtpClient smtpClient = new SmtpClient("smtp.gmail.com", 587);
            MailMessage message = new MailMessage();
            ENUsuario user = new ENUsuario();
            generarQr(sender, e);
            user.emailUsuario = userCookie.Value.ToString();
            try
            {
                MailAddress fromAddress = new MailAddress("cinemahubua@gmail.com", "Administración CinemaHub");
                MailAddress toAddress = new MailAddress(user.emailUsuario.ToString(), "Usuario");
                message.From = fromAddress;
                message.To.Add(toAddress);
                message.Subject = "COMPRA REALIZADA!!";
                message.Body = "Aqui tienes tu entrada:";


                message.Attachments.Add(new Attachment(HttpContext.Current.Server.MapPath("~/assets/qr"+ (numIMG-1).ToString() + ".jpeg")));
                smtpClient.EnableSsl = true;
                smtpClient.Credentials = new System.Net.NetworkCredential("cinemahubua@gmail.com", "cinemahub22*");
                smtpClient.Send(message);
                correo.Text = "Se ha enviado un correo a " + user.emailUsuario.ToString() + " con tu entrada";
            }
            catch (Exception)
            {
                correo.Text = " No se ha enviado el correo";
            }
            finally
            {

            }

            EntradaAviso.Text = "Aqui tienes tu entrada:";
            ENPelicula peli = new ENPelicula();
            peli.idPelicula = int.Parse(Request.QueryString["p"]);
            peli.readPelicula();
            user.addVistas(peli);

        }



        protected void generarQr(object sender, EventArgs e)
        {
            

            try
            {
                ENPelicula pParam = new ENPelicula();

                try
                {
                    pParam.idPelicula = int.Parse(Request.QueryString["p"]);
                }
                catch (Exception ex)
                {
                    Response.Redirect("ErrorPage.aspx");
                }

                if (!pParam.readPelicula())
                {
                    Response.Redirect("ErrorPage.aspx");
                }



                string cantMoney = Request.QueryString["PR"];
                string cantAsientos = Request.QueryString["NUM"];

                QRCodeEncoder encoder = new QRCodeEncoder();
                Bitmap img = encoder.Encode("Entrada para: " + pParam.nombrePelicula + " Precio: " + cantMoney + " Cantidad Asientos:" + cantAsientos);

                using (MemoryStream ms = new MemoryStream())
                {
                    System.Drawing.Image QR = (System.Drawing.Image)img;
                    QR.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
                    QR.Save(Server.MapPath("~/assets/qr" + numIMG.ToString() + ".jpeg"), System.Drawing.Imaging.ImageFormat.Jpeg);
                    numIMG++;
                    byte[] imageBytes = ms.ToArray();
                    imgCtrl.Src = "data:image/gif;base64," + Convert.ToBase64String(imageBytes);
                    imgCtrl.Height = 200;
                    imgCtrl.Width = 200;
                }
            }
            catch (HttpRequestValidationException)
            {
                Response.Redirect("ErrorPage.aspx");

            }
            catch (NullReferenceException)
            {
                Response.Redirect("ErrorPage.aspx");
            }


        }

    }
}
