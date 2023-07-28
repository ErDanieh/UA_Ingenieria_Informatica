<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="Perfil.aspx.cs" Inherits="WebApplication.Perfil" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/perfil.css" rel="stylesheet" />

    <div class="containerOptions" style="display: inline-grid">
        <asp:Label ID="nombreUsuario" runat="server" Text="Hola,  "></asp:Label>
    </div>

    <h2>Mis Peliculas Pendientes</h2>

    <div class="carteleraContainer">
        <asp:ListView ID="ListView1" runat="server">
            <ItemTemplate>
                <div class="list" runat="server">

                    <a class="thumbnail" href="<%#"/Pelicula.aspx?p="+ Eval("id") %>">
                        <img class="cartelPelicula" visible='<%# !Eval("miniatura").Equals("") %>' src="<%#Eval("miniatura") %>" alt="cartel_pelicula">
                    </a>

                &nbsp;</div>
            </ItemTemplate>
        </asp:ListView>
    </div>
    <asp:Button OnClick="eliminarPendientes" ID="eliminarPendiente" runat="server" Text="Eliminar Peliculas Pendientes" OnClientClick="return confirm('¿Estás seguro que deseas eliminar tus películas pendientes?')" />
    <asp:Button OnClick="onmisTickets" ID="misTickets" runat="server" Text="Mis Tickets" style="margin-left: 161px" Width="127px" />
    <h3>Cambiar contraeña</h3>

    <asp:Button OnClick="cerrarSesion" ID="closeSesion" runat="server" Text="Cerrar sesion" />

</asp:Content>
