<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="adminSesion.aspx.cs" Inherits="WebApplication.adminSesion" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/adminSesion.css" rel="stylesheet" />

    <h1>Opciones Sesiones</h1>
    <div class="containerOptions" style="display: inline-grid">
        <asp:TextBox ID="idSala" type="number" placeholder="Id Sala" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfsala" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="idSala" ErrorMessage="Por favor introduzca un id Sala" ForeColor="Black" />

        <asp:TextBox ID="idHora" type="text" placeholder="Id Horario" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfhora" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="idHora" ErrorMessage="Por favor introduzca un id Horario" ForeColor="Black" />

        <asp:TextBox ID="idPelicula" type="number" placeholder="Id Pelicula" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfpelicula" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="idPelicula" ErrorMessage="Por favor introduzca un id Pelicula" ForeColor="Black" />

        <asp:Button Text="Crear" ID="buttonCrear" runat="server" OnClick="buttonCrear_Click" />
        <asp:Button Text="Actualizar" ID="buttonAct" runat="server" OnClick="buttonAct_Click" />
        <asp:Button Text="Borrar" ID="buttonBorrar" runat="server" OnClick="buttonBorrar_Click" />
    </div>

    <asp:Label ID="outputMsg" runat="server"></asp:Label>
</asp:Content>
