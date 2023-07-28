<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="AdminPelicula.aspx.cs" Inherits="WebApplication.AdminPelicula" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

    <h1> Películas</h1>
    <div class="containerOptions" style="display: inline-grid">
        <link href="Content/adminPelicula.css" rel="stylesheet" />
        <asp:TextBox ID="idP" type="text" placeholder="Id" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rfid" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="idP" ErrorMessage="Por favor introduzca un id" ForeColor="black" />

        <asp:TextBox ID="miniaturaP" type="text" placeholder="Link de la miniatura" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rfminiatura" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="miniaturaP" ErrorMessage="Por favor introduzca una caratula" ForeColor="black" />
        <asp:RegularExpressionValidator ID="revminiatura" runat="server" Display="Dynamic"
            ControlToValidate="miniaturaP" ForeColor="black" ErrorMessage="Ingrese URL"
            ValidationExpression="http(s)?://([\w-]+\.)+[\w-]+(/[\w- ./?%&=]*)?" />

        <asp:TextBox ID="nombreP" type="text" placeholder="Nombre" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rfnombre" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="nombreP" ErrorMessage="Por favor introduzca un nombre" ForeColor="black" />

        <asp:TextBox ID="trailerP" type="text" placeholder="Link del trailer" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rftrailer" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="trailerP" ErrorMessage="Por favor introduzca un tráiler" ForeColor="black" />
        <asp:RegularExpressionValidator ID="revtrailer" runat="server" Display="Dynamic"
            ControlToValidate="trailerP" ForeColor="black" ErrorMessage="Ingrese URL"
            ValidationExpression="http(s)?://([\w-]+\.)+[\w-]+(/[\w- ./?%&=]*)?" />

        <asp:TextBox ID="generoP" type="text" placeholder="Género" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rfgenero" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="generoP" ErrorMessage="Por favor introduzca un género" ForeColor="black" />

        <asp:TextBox ID="DescripcionP" type="text" placeholder="Descripción" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfdescrip" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="DescripcionP" ErrorMessage="Por favor introduzca una descripción" ForeColor="black" />


        <asp:TextBox ID="duracionP" type="number" placeholder="Duración" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rfduracion" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="duracionP" ErrorMessage="Por favor introduzca una duración" ForeColor="black" />

        <asp:TextBox ID="valoracionP" type="number" placeholder="Valoración" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfval" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="valoracionP" ErrorMessage="Por favor introduzca una valoración" ForeColor="black" />
        <asp:RangeValidator ID="rgVal" runat="server" Type="Integer" ControlToValidate="valoracionP" Display="Dynamic" 
             MaximumValue="5" MinimumValue="0" ErrorMessage="Rango inválido" ForeColor="black" />

        <asp:TextBox ID="festrenoP" type="text" placeholder="Fecha Estreno" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rffestreno" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="festrenoP" ErrorMessage="Por favor introduzca la fecha de estreno" ForeColor="black" />

        <asp:Button Text="Crear" ID="buttonCrear" runat="server" OnClick="buttonCrear_Click" />
        <asp:Button Text="Actualizar" ID="buttonAct" runat="server" OnClick="buttonAct_Click" />
        <asp:Button Text="Borrar" ID="buttonBorrar" runat="server" OnClick="buttonBorrar_Click" />

        <p id="infoRellenar">Rellenar en caso de querer actualizar o eliminar una pelicula.</p>
        <asp:Label ID="outputMsg" runat="server"></asp:Label>
    </div>
    
</asp:Content>
