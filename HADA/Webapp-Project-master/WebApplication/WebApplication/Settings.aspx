<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="Settings.aspx.cs" Inherits="WebApplication.Settings" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/perfil.css" rel="stylesheet" />

    <h3>Cambiar nombre y apellido</h3>
    <div id="cambiarNombre">
        <asp:TextBox ID="nuevoNombre" runat="server" placeholder="Nuevo nombre"></asp:TextBox>
        <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" Display="Dynamic" ValidationGroup="groupNombreApellido"
            ControlToValidate="nuevoNombre" ErrorMessage="Introduce un nuevo nombre." ForeColor="Red" />
        <asp:RegularExpressionValidator ID="nombreAlphabetic" runat="server" Display="Dynamic" ValidationGroup="groupNombreApellido"
            ControlToValidate="nuevoNombre" ForeColor="Red" ErrorMessage="Solo se admmiten caracteres alfabéticos." ValidationExpression="^[a-zA-Z]*$" />

        <asp:TextBox ID="nuevoApellido" runat="server" placeholder="Nuevo apellido"></asp:TextBox>
        <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" Display="Dynamic" ValidationGroup="groupNombreApellido"
            ControlToValidate="nuevoApellido" ErrorMessage="Introduce un nuevo apellido." ForeColor="Red" />
        <asp:RegularExpressionValidator ID="apellidoAlphabetic" runat="server" Display="Dynamic" ValidationGroup="groupNombreApellido"
            ControlToValidate="nuevoApellido" ForeColor="Red" ErrorMessage="Solo se admmiten caracteres alfabéticos." ValidationExpression="^[a-zA-Z]*$" />

        <asp:Button ID="btnNombre" runat="server" Text="Actualizar nombre" OnClientClick="return confirm('¿Estás seguro que deseas cambiar su nombre de usuario?')" OnClick="cambiarNombre" />
    </div>

    <h3>Cambiar contraeña</h3>
    <div id="cambiarPassword">
        <asp:TextBox ID="antiguaPassword" runat="server" placeholder="Contraseña antigua"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfantigua" runat="server" Display="Dynamic" ValidationGroup="groupPassword"
            ControlToValidate="antiguaPassword" ErrorMessage="Introduzca contraseña antigua" ForeColor="Red" />

        <asp:TextBox ID="nuevaPassword" runat="server" placeholder="Nueva contraseña"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfnueva" runat="server" Display="Dynamic" ValidationGroup="groupPassword"
            ControlToValidate="nuevaPassword" ErrorMessage="Introduzca contraseña nueva" ForeColor="Red" />
        <asp:RegularExpressionValidator ID="revnueva" runat="server" Display="Dynamic" ValidationGroup="groupPassword"
            ControlToValidate="nuevaPassword" ForeColor="Red" ErrorMessage="Formato incorrecto" ValidationExpression="(?!^[0-9]$)(?!^[a-zA-Z]$)^([a-zA-Z0-9]{8,10})$" />

        <asp:TextBox ID="confirmarContraseña" runat="server" placeholder="Confirmar contraseña"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfrepetida" runat="server" Display="Dynamic" ValidationGroup="groupPassword"
            ControlToValidate="confirmarContraseña" ErrorMessage="Repita la nueva contraseña" ForeColor="Red" />
        <asp:RegularExpressionValidator ID="revrepetida" runat="server" Display="Dynamic" ValidationGroup="groupPassword"
            ControlToValidate="confirmarContraseña" ForeColor="Red" ErrorMessage="Formato incorrecto" ValidationExpression="(?!^[0-9]$)(?!^[a-zA-Z]$)^([a-zA-Z0-9]{8,10})$" />

        <asp:CompareValidator ID="mismapassword" runat="server" Display="Dynamic" ValidationGroup="groupPassword"
            ControlToValidate="nuevaPassword" ControlToCompare="confirmarContraseña" ErrorMessage="Las contraseñas no coinciden" ForeColor="Red" />

        <asp:Button ID="btCambiarContra" runat="server" Text="Cambiar contraseña" OnClick="cambiarContra" />
        <asp:Label ID="resultadoCambioContra" runat="server" Text=""></asp:Label>
    </div>
    <asp:Button ID="eliminarUsuario" runat="server" Text="Eliminar Cuenta" OnClientClick="return confirm('¿Estás seguro que deseas eliminar tu cuenta en CinemaHub?')" OnClick="eliminarUsuario_Click"/>
</asp:Content>
