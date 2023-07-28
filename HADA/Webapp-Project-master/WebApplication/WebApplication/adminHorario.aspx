<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="adminHorario.aspx.cs" Inherits="WebApplication.adminHorario" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/adminHorario.css" rel="stylesheet" />
    <h1>Opciones Horario</h1>
    <div class="containerOptions" style="display: inline-grid">

        <asp:TextBox ID="idH" type="text" placeholder="Id Horario" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator ID="rfidH" runat="server" Display="Dynamic" ValidationGroup="agregarBorrar"
            ControlToValidate="idH" ErrorMessage="Por favor introduzca un Horario" ForeColor="Black" />

        <asp:Button  Text="Crear" ID="buttonCrear" runat="server" OnClick="buttonCrear_Click" />
        <asp:Button  Text="Borrar" ID="buttonBorrar" runat="server" OnClick="buttonBorrar_Click" />


    </div>

    <asp:Label ID="outputMsg" runat="server"></asp:Label>
</asp:Content>
