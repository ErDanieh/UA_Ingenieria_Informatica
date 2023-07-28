<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="adminSala.aspx.cs" Inherits="WebApplication.adminSala" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
        <link href="Content/adminSalas.css" rel="stylesheet" />

    <h1>Opciones Salas</h1>
    <div class="containerOptions" style="display: inline-grid">
        <asp:TextBox ID="idSala" type="number" placeholder="Id Sala" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rfIdSala" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="idSala" ErrorMessage="Por favor introduzca un id" ForeColor="Black" />

        <asp:TextBox ID="asientosSala" type="number" placeholder="Número de asientos" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator id="rfAsientosSala" runat="server" Display="Dynamic" ValidationGroup="groupAgregar"
            ControlToValidate="asientosSala" ErrorMessage="Por favor introduzca nº asientos" ForeColor="Black" />
                <asp:Button Style="margin: 5px" Text="Crear" ID="buttonCrear" runat="server" OnClick="buttonCrear_Click" />
        <asp:Button Style="margin: 5px" Text="Actualizar" ID="buttonAct" runat="server" OnClick="buttonAct_Click" />
        <asp:Button Style="margin: 5px" Text="Borrar" ID="buttonBorrar" runat="server" OnClick="buttonBorrar_Click" />
    </div>
    <div class="containerButtons">

    </div>
    <asp:Label ID="outputMsg" runat="server"></asp:Label>
</asp:Content>
