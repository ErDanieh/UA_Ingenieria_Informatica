<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="adminUser.aspx.cs" Inherits="WebApplication.adminUser" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

    <h1>Opciones Usuarios</h1>
    <div class="containerOptions" style="display: inline-grid">
        <link href="Content/adminUsuario.css" rel="stylesheet" />

        <asp:TextBox ID="nombreApellidos" type="text" placeholder="Nombre" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ID="reqNombreRegister" ValidationGroup="registerGroup"
            ControlToValidate="nombreApellidos" ErrorMessage="Por favor introduzca nombre" Display="Dynamic" ForeColor="black" />

        <asp:TextBox ID="apellido" type="text" placeholder="Apellidos" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ID="reqApellidosReg" ValidationGroup="registerGroup"
            ControlToValidate="apellido" ErrorMessage="Por favor introduzca apellidos" Display="Dynamic" ForeColor="black" />

        <asp:TextBox ID="emailReg" type="email" placeholder="Email" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ID="reqEmailRegister" Display="Dynamic" ValidationGroup="registerGroup"
            ControlToValidate="emailReg" ErrorMessage="Por favor introduzca un email" ForeColor="black" />
        <asp:RegularExpressionValidator ID="revEmailReg" runat="server" Display="Dynamic" ControlToValidate="emailReg"
            ForeColor="black" ErrorMessage="Formato de correo no válido" ValidationExpression="^([\w-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([\w-]+\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\]?)$" />

        <asp:TextBox ID="passwordReg" type="password" placeholder="Contraseña" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ID="reqPasswordRegister" Display="Dynamic" ValidationGroup="registerGroup"
            ControlToValidate="passwordReg" ErrorMessage="Por favor introduzca una contraseña" ForeColor="black" />
        <asp:RegularExpressionValidator ID="revPasswordReq" runat="server" Display="Dynamic"
            ControlToValidate="passwordReg" ForeColor="black" ErrorMessage="La contraseña debe tener 8-10 carácteres y al menos 1 número" ValidationExpression="(?!^[0-9]$)(?!^[a-zA-Z]$)^([a-zA-Z0-9]{8,10})$" />

        <asp:TextBox ID="edadRegister" type="number" placeholder="Edad" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ID="reqEdadRegister" Display="Dynamic" ValidationGroup="registerGroup"
            ControlToValidate="edadRegister" ErrorMessage="Por favor introduzca una edad" ForeColor="black" />
        <asp:RangeValidator ID="rgEdadReg" runat="server" Type="Integer" ControlToValidate="edadRegister" Display="Dynamic" MaximumValue="110" MinimumValue="16" ErrorMessage="Mayor de 15 años" ForeColor="black" />

        <asp:TextBox ID="adminVar" type="number" placeholder="Administrador" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ID="reqAdminReg" Display="Dynamic" ValidationGroup="registerGroup"
            ControlToValidate="adminVar" ErrorMessage="Por favor introduzca si es admin" ForeColor="black" />
        <asp:RangeValidator ID="rgAdmin" runat="server" ControlToValidate="adminVar" Display="Dynamic" MaximumValue="1" MinimumValue="0" ErrorMessage="0= usuario; 1=admin" ForeColor="black" />

        <asp:Button Text="Crear" ID="buttonCrear" runat="server" OnClick="buttonCrear_Click" />
        <asp:Button Text="Actualizar" ID="buttonAct" runat="server" OnClick="buttonAct_Click" />
        <asp:Button Text="Borrar" ID="buttonBorrar" runat="server" OnClick="buttonBorrar_Click" />

        <p id="infoRellenar">Rellene todos los campos para poder administrar un usuario.</p>


    </div>
    <asp:Label ID="outputMsg" runat="server"></asp:Label>
</asp:Content>
