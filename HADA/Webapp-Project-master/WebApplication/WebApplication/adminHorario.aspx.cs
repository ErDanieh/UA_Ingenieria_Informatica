using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace WebApplication
{
    public partial class adminHorario : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }


        protected void buttonCrear_Click(object sender, EventArgs e)
        {
            Page.Validate("agregarBorrar");
            if (Page.IsValid)
            {
                ENHorario horario = new ENHorario();
                horario.idHorario = DateTime.Parse(idH.Text);
                if (horario.createHorario() == true)
                {
                    outputMsg.Text = "Horario " + horario.idHorario + "  creado.";
                }
                else
                {
                    outputMsg.Text = "Horario NO creado.";
                }
            }

        }

        protected void buttonBorrar_Click(object sender, EventArgs e)
        {
            Page.Validate("agregarBorrar");
            if (Page.IsValid)
            {
                ENHorario horario = new ENHorario();
                horario.idHorario = DateTime.Parse(idH.Text);

                if (horario.deleteHorario() == true)
                {
                    outputMsg.Text = "Horario " + horario.idHorario + "  borrado.";
                }
                else
                {
                    outputMsg.Text = "Horario " + horario.idHorario + "  NO se ha borrado.";
                }
            }

        }
    }
}