using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace WebApplication
{
    public partial class adminUser : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void buttonCrear_Click(object sender, EventArgs e)
        {
            reqNombreRegister.ValidationGroup = "registerGroup";
            reqApellidosReg.ValidationGroup = "registerGroup";
            reqEdadRegister.ValidationGroup = "registerGroup";
            reqEmailRegister.ValidationGroup = "registerGroup";
            reqPasswordRegister.ValidationGroup = "registerGroup";
            reqAdminReg.ValidationGroup = "registerGroup";
            Page.Validate("registerGroup");

            if (Page.IsValid)
            {
                ENUsuario user = new ENUsuario();

                string nombre = nombreApellidos.Text;
                string apellidos = apellido.Text;
                bool nomFin = false;

                

                if (edadRegister.Text != null && nombreApellidos.Text != "" && apellido.Text != "" && emailReg.Text != "" && passwordReg.Text != "" && !user.readUsuario())
                {
                    user.nombreUsuario = nombre;
                    user.apellidoUsuario = apellidos;
                    user.emailUsuario = emailReg.Text;
                    user.edadUsuario = int.Parse(edadRegister.Text);
                    user.passwordUsuario = passwordReg.Text;
                    user.tipoUsuario = int.Parse(adminVar.Text);

                    ENDescuento descuento = new ENDescuento(4);

                    if (user.edadUsuario <= 7) descuento.rangoDescuento = 1;
                    else if (user.edadUsuario <= 23) descuento.rangoDescuento = 2;
                    else if (user.edadUsuario >= 65) descuento.rangoDescuento = 3;
                    user.descuentosUsuario = descuento;

                    if (user.createUsuario() == true)
                    {
                        outputMsg.Text = "Usuario creado.";
                    }
                    else
                    {
                        outputMsg.Text = "No se ha podido crear el usuario. Error.";
                    }
                }
                else
                {
                    outputMsg.Text = "Email no valido: " + emailReg.Text + " ya esta registrado";

                }
            }
        }

        protected void buttonAct_Click(object sender, EventArgs e)
        {
            reqNombreRegister.ValidationGroup = "registerGroup";
            reqApellidosReg.ValidationGroup = "registerGroup";
            reqEdadRegister.ValidationGroup = "registerGroup";
            reqEmailRegister.ValidationGroup = "registerGroup";
            reqPasswordRegister.ValidationGroup = "registerGroup";
            reqAdminReg.ValidationGroup = "registerGroup";
            Page.Validate("registerGroup");

            if (Page.IsValid)
            {
                ENUsuario user = new ENUsuario();

                string nombre = nombreApellidos.Text;
                string apellidos = apellido.Text;
                bool nomFin = false;

                

                user.nombreUsuario = nombre;
                user.apellidoUsuario = apellidos;
                user.emailUsuario = emailReg.Text;
                user.edadUsuario = int.Parse(edadRegister.Text);
                user.passwordUsuario = passwordReg.Text;
                user.tipoUsuario = int.Parse(adminVar.Text); ;

                ENDescuento descuento = new ENDescuento(4);

                if (user.edadUsuario <= 7) descuento.rangoDescuento = 1;
                else if (user.edadUsuario <= 23) descuento.rangoDescuento = 2;
                else if (user.edadUsuario >= 65) descuento.rangoDescuento = 3;
                user.descuentosUsuario = descuento;

                if (user.updateUsuario() == true)
                {
                    outputMsg.Text = "Usuario actualizado.";
                }
                else
                {
                    outputMsg.Text = "No se ha podido actualizar el usuario. Error.";
                }
            }

        }

        protected void buttonBorrar_Click(object sender, EventArgs e)
        {
            reqNombreRegister.ValidationGroup = "registerBorrar";
            reqApellidosReg.ValidationGroup = "registerBorrar";
            reqEdadRegister.ValidationGroup = "registerBorrar";
            reqEmailRegister.ValidationGroup = "registerGroup";
            reqPasswordRegister.ValidationGroup = "registerBorrar";
            reqAdminReg.ValidationGroup = "registerBorrar";
            Page.Validate("registerGroup");

            if (Page.IsValid)
            {
                ENUsuario user = new ENUsuario();
                user.emailUsuario = emailReg.Text;

                

                if (user.deletePendientesTodas() == true && user.deleteUsuario() == true )
                {
                    outputMsg.Text = "Usuario borrado.";
                }
                else
                {
                    outputMsg.Text = "Usuario " + emailReg.Text + "  NO  borrado.";
                }
            }
        }
    }
}