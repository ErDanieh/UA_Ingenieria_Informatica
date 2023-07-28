<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="ControlAdmin.aspx.cs" Inherits="WebApplication.ControlAdmin" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/ControlAdmin.css" rel="stylesheet" />

    <h1>Administrar</h1>
    <div class="containerOptions">
        <asp:Button ID="btAdminPeliculas" OnClick="adminPeliculas" runat="server" Text="Peliculas" />
        <asp:Button ID="btAdminHorario" OnClick="adminHorarios" runat="server" Text="Horarios" />
        <asp:Button ID="btAdminSala" OnClick="adminSala" runat="server" Text="Salas" />
        <asp:Button ID="btAdminSesion" OnClick="adminSesion" runat="server" Text="Sesiones" />
        <asp:Button ID="btAdminUsers" OnClick="adminUsers" runat="server" Text="Usuarios" />
    </div>
    <div class="closebutton">
        <asp:Button ID="btClose" OnClick="CloseSesion" runat="server" Text="Cerrar Sesión" />
    </div>
</asp:Content>
