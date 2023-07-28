using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace WebApplication
{

    public partial class Index : System.Web.UI.Page
    {


        protected void Page_Load(object sender, EventArgs e)
        {


            if (!Page.IsPostBack)
            {

                seleccionGenero.DataTextField = ENGenero.todosrGeneros().Tables[0].Columns["genero"].ToString();  // text field name of table dispalyed in dropdown       
                seleccionGenero.DataValueField = ENGenero.todosrGeneros().Tables[0].Columns["genero"].ToString();
                // to retrive specific  textfield name   
                seleccionGenero.DataSource = ENGenero.todosrGeneros().Tables[0];
                seleccionGenero.DataBind();  //binding dropdownlist
                seleccionGenero.Items.Insert(0, new ListItem("Seleccionar género: ", ""));


                if (Request.QueryString["par1"] != null)
                {
                    ListView1.DataSource = ENPelicula.mostrarSelect(Request.QueryString["par1"]);
                    ListView1.DataBind();
                }
                else
                {
                    ListView1.DataSource = ENPelicula.mostrarPeliculas();
                    ListView1.DataBind();
                }

            }

        }



        protected void filtradoPeliculas(object sender, EventArgs e)
        {

            ListView1.DataSource = ENPelicula.muestraGeneroOrdenado(seleccionGenero.SelectedValue, orderBy.SelectedValue);
            ListView1.DataBind();

        }
    }
}