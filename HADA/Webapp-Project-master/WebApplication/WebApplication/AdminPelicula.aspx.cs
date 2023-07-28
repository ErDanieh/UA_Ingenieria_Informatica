using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace WebApplication
{
    public partial class AdminPelicula : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void buttonCrear_Click(object sender, EventArgs e)
        {
            rfid.ValidationGroup = "groupAgregar";
            rfnombre.ValidationGroup = "groupAgregar";
            rfdescrip.ValidationGroup = "groupAgregar";
            rfduracion.ValidationGroup = "groupAgregar";
            rfminiatura.ValidationGroup = "groupAgregar";
            rftrailer.ValidationGroup = "groupAgregar";
            rfval.ValidationGroup = "groupAgregar";
            rffestreno.ValidationGroup = "groupAgregar";
            rfgenero.ValidationGroup = "groupAgregar";
            Page.Validate("groupAgregar");

            if (Page.IsValid)
            {
                ENPelicula pelicula = new ENPelicula();
                DateTime dateEstreno;
                string fechaE = festrenoP.Text;
                pelicula.idPelicula = int.Parse(idP.Text);
                pelicula.nombrePelicula = nombreP.Text;
                pelicula.descripcionPelicula = DescripcionP.Text;
                pelicula.duracionPelicula = int.Parse(duracionP.Text);
                pelicula.imgPelicula = miniaturaP.Text;
                pelicula.trailerPelicula = trailerP.Text;
                pelicula.valoracionPelicula = int.Parse(valoracionP.Text);
                dateEstreno = DateTime.Parse(fechaE);
                pelicula.fechaEstrenoPelicula = dateEstreno;
                pelicula.generoPelicula = new ENGenero(generoP.Text);

                if (pelicula.createPelicula() == true)
                {
                    outputMsg.Text = "Pelicula " + pelicula.idPelicula + "  creada.";
                }
                else
                {
                    outputMsg.Text = "Pelicula NO creada.";
                }
            }


        }

        protected void buttonAct_Click(object sender, EventArgs e)
        {
            rfid.ValidationGroup = "groupAgregar";
            rfnombre.ValidationGroup = "groupAgregar";
            rfdescrip.ValidationGroup = "groupAgregar";
            rfduracion.ValidationGroup = "groupAgregar";
            rfminiatura.ValidationGroup = "groupAgregar";
            rftrailer.ValidationGroup = "groupAgregar";
            rfval.ValidationGroup = "groupAgregar";
            rffestreno.ValidationGroup = "groupAgregar";
            rfgenero.ValidationGroup = "groupAgregar";
            Page.Validate("groupAgregar");

            if (Page.IsValid)
            {

                ENPelicula pelicula = new ENPelicula();
                DateTime dateEstreno;
                string fechaE = festrenoP.Text;
                pelicula.idPelicula = int.Parse(idP.Text);
                pelicula.nombrePelicula = nombreP.Text;
                pelicula.descripcionPelicula = DescripcionP.Text;
                pelicula.duracionPelicula = int.Parse(duracionP.Text);
                pelicula.imgPelicula = miniaturaP.Text;
                pelicula.trailerPelicula = trailerP.Text;
                pelicula.valoracionPelicula = int.Parse(valoracionP.Text);
                dateEstreno = DateTime.Parse(fechaE);
                pelicula.fechaEstrenoPelicula = dateEstreno;
                pelicula.generoPelicula = new ENGenero(generoP.Text);

                if (pelicula.updatePelicula() == true)
                {
                    outputMsg.Text = "Pelicula " + pelicula.idPelicula + "  actualizada.";
                }
                else
                {
                    outputMsg.Text = "Pelicula NO actualizada.";
                }
            }


        }

        protected void buttonBorrar_Click(object sender, EventArgs e)
        {
            rfid.ValidationGroup = "groupAgregar";
            rfnombre.ValidationGroup = "groupBorrar";
            rfdescrip.ValidationGroup = "groupBorrar";
            rfduracion.ValidationGroup = "groupBorrar";
            rfminiatura.ValidationGroup = "groupBorrar";
            rftrailer.ValidationGroup = "groupBorrar";
            rfval.ValidationGroup = "groupBorrar";
            rffestreno.ValidationGroup = "groupBorrar";
            rfgenero.ValidationGroup = "groupBorrar";
            Page.Validate("groupAgregar");

            if (Page.IsValid)
            {
                idP.ValidationGroup = "groupBorrar";
                Page.Validate("grupoBorrar");

                ENPelicula pelicula = new ENPelicula();

                pelicula.idPelicula = int.Parse(idP.Text);

                if (pelicula.readPelicula())
                {
                    pelicula.deletePeliculaPendientes();
                    pelicula.deletePeliculaTener();
                    pelicula.deletePeliculaSesion();

                    if(pelicula.deletePelicula())
                    {
                        outputMsg.Text = "Pelicula " + pelicula.idPelicula + "  borrada.";
                    }
                    else
                    {
                        outputMsg.Text = "Pelicula NO borrada";
                    }
                }
                else
                {
                    outputMsg.Text = "No se ha encontrado esa pelicula";
                }

            }

        }
    }
}