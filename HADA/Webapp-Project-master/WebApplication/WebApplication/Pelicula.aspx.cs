using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlTypes;
using System.Data.SqlClient;
using System.Data.Common;
using System.Data;
using System.Windows.Input;
using System.Web.Services;

namespace WebApplication
{
    public partial class Pelicula : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {

                char[] charsToTrim = { '*', ' ', '\'', '?' };

                if (Request.QueryString["p"].Trim(charsToTrim) != null)
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

                    imagenPelicula.ImageUrl = pParam.imgPelicula;
                    nombrePelicula.Text = pParam.nombrePelicula;
                    descripcion.Text = pParam.descripcionPelicula;
                    duracion.Text = pParam.duracionPelicula.ToString() + " m.";
                    trailer.Attributes.Add("src", pParam.trailerPelicula.ToString());
                    valoracion.Text = "Valoracion: " + pParam.valoracionPelicula.ToString() + "/5";
                    genero.Text = "Genero: " + pParam.generoPelicula.generoPelicula.ToString();

                    if (!Page.IsPostBack)
                    {
                        seleccionHora.Visible = false;
                        seleccionDia.DataTextField = ENSesion.diasSesionesPelicula(pParam.idPelicula).Tables[0].Columns["id_hora"].ToString();  // text field name of table dispalyed in dropdown   
                        seleccionDia.DataValueField = ENSesion.diasSesionesPelicula(pParam.idPelicula).Tables[0].Columns["id_values"].ToString();  // text field name of table dispalyed in dropdown       
                        seleccionDia.DataSource = ENSesion.diasSesionesPelicula(pParam.idPelicula);

                        seleccionDia.DataBind();

                        seleccionDia.Items.Insert(0, new ListItem("Seleccionar fecha: ", ""));
                        string fechaS = seleccionDia.SelectedValue.ToString() + "  " + seleccionHora.SelectedValue.ToString() + ":00";
                        int PeliS = pParam.idPelicula;
                    }
                }
                else
                {
                    Response.Redirect("ErrorPage.aspx");
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


        protected void pendientes_Click(object sender, EventArgs e)
        {

            HttpCookie userCookie;
            userCookie = Request.Cookies["UserID"];


            if (userCookie == null)
            {
                Response.Redirect("LogReg.aspx");
            }

            ENUsuario user = new ENUsuario();
            user.emailUsuario = userCookie.Value.ToString();

            if (!user.readUsuario())
            {
                Response.Redirect("LogReg.aspx");
            }

            ENPelicula pelicula = new ENPelicula();
            pelicula.idPelicula = int.Parse(Request.QueryString["p"]);
            pelicula.readPelicula();

            if (user.addPendientes(pelicula))
            {
                outMsg.Text = "Pelicula añadida.";
            }
            else if (user.deletePendientes(pelicula))
            {
                outMsg.Text = "Pelicula eliminada";
            }
            else
            {
                outMsg.Text = "No ha hecho nada";
            }


        }
        protected void seleccionHoraChanged(object sender, EventArgs e)
        {
            fechaS.Text = seleccionDia.SelectedValue.ToString() + "  " + seleccionHora.SelectedValue.ToString() + ":00";
           
            ENPelicula pParam = new ENPelicula();
            pParam.idPelicula = int.Parse(Request.QueryString["p"]);
            peliS.Text =  Convert.ToString(pParam.idPelicula);

            string idSesion= seleccionDia.SelectedValue.ToString() + "  " + seleccionHora.SelectedValue.ToString() + ":00";

            ListView2.DataSource = ENSesion.mostrarAsientos(idSesion, pParam.idPelicula);
            ListView2.DataBind();

            ClientScript.RegisterStartupScript(this.GetType(), "??", "MostrarA()", true);


        }
        protected void seleccionDiaChanged(object sender, EventArgs e)
        {
            int id_pelicula = int.Parse(Request.QueryString["p"]);

            seleccionHora.Visible = true;
            seleccionHora.DataTextField = ENSesion.mostrarHoras(id_pelicula, seleccionDia.SelectedValue).Tables[0].Columns["id_hora"].ToString();  // text field name of table dispalyed in dropdown   
            seleccionHora.DataValueField = ENSesion.mostrarHoras(id_pelicula, seleccionDia.SelectedValue).Tables[0].Columns["id_hora"].ToString();  // text field name of table dispalyed in dropdown       
            seleccionHora.DataSource = ENSesion.mostrarHoras(id_pelicula, seleccionDia.SelectedValue);
            seleccionHora.DataBind();

            seleccionHora.Items.Insert(0, new ListItem("Seleccionar hora: ", ""));
        }

        protected void compraEntradas_Click(object sender, EventArgs e)
        {

            ENPelicula pParam = new ENPelicula();

            pParam.idPelicula = int.Parse(Request.QueryString["p"]);
            HttpCookie userCookie;
            userCookie = Request.Cookies["UserID"];
            if (userCookie == null)
            {
                Response.Redirect("Perfil.aspx");
            }
            else
            {
                Response.Redirect("CompraCheckout.aspx?p=" + pParam.idPelicula);
            }


        }




     

        protected void Asientos_Click(object sender, EventArgs e)
        {


        }

        protected void Button1_Click(object sender, EventArgs e)
        {

        }

        

        [WebMethod]
        public static void MyMethod(int id, int pelicula, string fecha )
        {
            if (id != 100)
            {
            string constring;
            constring = ConfigurationManager.ConnectionStrings["BaseDatos"].ToString();
            SqlConnection conexion = null;
            conexion = new SqlConnection(constring);
            ENPelicula pParam = new ENPelicula();
          
            try
            {
                conexion.Open();
                String query = "Update [dbo].[Tener] set  estado= ' " + 1 + "' " + "WHERE id_asiento = '" + id + "' AND  id_pelicula = '" + pelicula + "' AND id_sesionHora = '" + fecha + "'";
                SqlCommand consulta = new SqlCommand(query, conexion);
                consulta.ExecuteNonQuery();
            }
            catch (SqlException err)
            {
                Console.WriteLine("User operation has failed.Error: {0}", err.Message);
            }
            catch (Exception err)
            {
                Console.WriteLine("User operation has failed.Error: {0}", err.Message);
            }
            finally
            {
                conexion.Close();
            }

            }


        }

        protected void testing_click(object sender, EventArgs e)
        {
            //Asientos -----

        }

        void Page_Error(object sender, EventArgs e)
        {
            Exception ex = Server.GetLastError();
        }
    }
}