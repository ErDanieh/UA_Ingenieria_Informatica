using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace WebApplication
{
    public partial class adminSesion : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void buttonCrear_Click(object sender, EventArgs e)
        {
            rfsala.ValidationGroup = "groupAgregar";
            rfhora.ValidationGroup = "groupAgregar";
            rfpelicula.ValidationGroup = "groupAgregar";
            Page.Validate("groupAgregar");
            if (Page.IsValid)
            {
                ENSesion sesion = new ENSesion();
                ENPelicula pelicula = new ENPelicula();
                pelicula.idPelicula = int.Parse(idPelicula.Text);
                ENHorario horario = new ENHorario();
                horario.idHorario = DateTime.Parse(idHora.Text);
                ENSala sala = new ENSala();
                sala.salaSala = int.Parse(idSala.Text);

                sesion.horaSesion = horario;
                sesion.salaSesion = sala;
                sesion.peliculaSesion = pelicula;


                if (sesion.createSesion() == true)
                {
                    outputMsg.Text = "Sesion " + sesion.salaSesion.salaSala + " (" + sesion.horaSesion.idHorario + ")  creada.";
                }
                else
                {
                    outputMsg.Text = "Sesion " + sesion.salaSesion.salaSala + " (" + sesion.horaSesion.idHorario + ") NO creada.";
                }
            }
        }

        protected void buttonAct_Click(object sender, EventArgs e)
        {
            rfsala.ValidationGroup = "groupAgregar";
            rfhora.ValidationGroup = "groupAgregar";
            rfpelicula.ValidationGroup = "groupAgregar";
            Page.Validate("groupAgregar");

            if (Page.IsValid)
            {
                ENSesion sesion = new ENSesion();
                ENPelicula pelicula = new ENPelicula();
                pelicula.idPelicula = int.Parse(idPelicula.Text);
                ENHorario horario = new ENHorario();
                horario.idHorario = DateTime.Parse(idHora.Text);
                ENSala sala = new ENSala();
                sala.salaSala = int.Parse(idSala.Text);

                sesion.horaSesion = horario;
                sesion.salaSesion = sala;
                sesion.peliculaSesion = pelicula;


                if (sesion.updateSesion() == true)
                {
                    outputMsg.Text = "Sesion " + sesion.salaSesion.salaSala + " (" + sesion.horaSesion.idHorario + ")  actualizada.";
                }
                else
                {
                    outputMsg.Text = "Sesion " + sesion.salaSesion.salaSala + " (" + sesion.horaSesion.idHorario + ") NO actualizada.";
                }
            }
        }

        protected void buttonBorrar_Click(object sender, EventArgs e)
        {
            rfsala.ValidationGroup = "groupAgregar";
            rfhora.ValidationGroup = "groupAgregar";
            rfpelicula.ValidationGroup = "groupAgregar";
            Page.Validate("groupAgregar");

            if (Page.IsValid)
            {
                ENSesion sesion = new ENSesion();
                ENHorario horario = new ENHorario();
                horario.idHorario = DateTime.Parse(idHora.Text);
                ENPelicula pelicula = new ENPelicula();
                pelicula.idPelicula = int.Parse(idPelicula.Text);
                ENSala sala = new ENSala();
                sala.salaSala = int.Parse(idSala.Text);

                sesion.horaSesion = horario;
                sesion.salaSesion = sala;
                sesion.peliculaSesion = pelicula;

                if (sesion.deleteSesion() == true)
                {
                    outputMsg.Text = "Sesion " + sesion.salaSesion.salaSala + " (" + sesion.horaSesion.idHorario + ")  borrada.";
                }
                else
                {
                    outputMsg.Text = "Sesion " + sesion.salaSesion.salaSala + " (" + sesion.horaSesion.idHorario + ") NO borrada."; ;
                }
            }
        }
    }
}