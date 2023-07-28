using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace WebApplication
{
    public partial class adminSala : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void buttonCrear_Click(object sender, EventArgs e)
        {
            rfIdSala.ValidationGroup = "groupAgregar";
            rfAsientosSala.ValidationGroup = "groupAgregar";
            Page.Validate("groupAgregar");
            if (Page.IsValid)
            {
                ENSala sala = new ENSala();
                sala.salaSala = int.Parse(idSala.Text);
                sala.numAsietosSala = int.Parse(asientosSala.Text);
                Page.Validate("groupAgregar");

                if (sala.createSala() == true)
                {
                    outputMsg.Text = "Sala " + sala.salaSala + "  creada.";
                }
                else
                {
                    outputMsg.Text = "Sala NO creada.";
                }
            }
        }

        protected void buttonAct_Click(object sender, EventArgs e)
        {
            rfIdSala.ValidationGroup = "groupAgregar";
            rfAsientosSala.ValidationGroup = "groupAgregar";
            Page.Validate("groupAgregar");
            if (Page.IsValid)
            {
                ENSala sala = new ENSala();
                sala.salaSala = int.Parse(idSala.Text);
                sala.numAsietosSala = int.Parse(asientosSala.Text);

                if (sala.updateSala() == true)
                {
                    outputMsg.Text = "Sala " + sala.salaSala + "  actualizada.";
                }
                else
                {
                    outputMsg.Text = "Sala NO actualizada.";
                }
            }
        }

        protected void buttonBorrar_Click(object sender, EventArgs e)
        {
            rfIdSala.ValidationGroup = "groupAgregar";
            rfAsientosSala.ValidationGroup = "groupBorrar";
            Page.Validate("groupAgregar");

            if (Page.IsValid)
            {
                ENSala sala = new ENSala();
                sala.salaSala = int.Parse(idSala.Text);

                if (sala.deleteSala() == true)
                {
                    outputMsg.Text = "Sala " + sala.salaSala + "  eliminada.";
                }
                else
                {
                    outputMsg.Text = "Sala NO eliminada.";
                }
            }
        }
    }
}