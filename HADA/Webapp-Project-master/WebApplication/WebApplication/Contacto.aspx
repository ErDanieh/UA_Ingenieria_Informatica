<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="Contacto.aspx.cs" Inherits="WebApplication.Contacto" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/Contacto.css" rel="stylesheet" />

    <h1>Horario de taquilla</h1>
    <div class="containerOptions">
        Sábados, Domingos y festivos: de 15:30h a 20h<br />
        Lunes a Viernes de 16:30h a 20h.
    </div>

    <h1>Horario de Atención Telefónica</h1>
    <div class="containerOptions">
        Teléfono: 966 666 666
        <br />
        Miércoles, Viernes, Sábados, domingos y festivos de 17:00h a 21h.
        <br />
        <br />
        Puedes contactar con nosotros a través del email: info.cinemaHub@gmail.com
    </div>

    <h1>Dirección:
    </h1>
    <div class="containerOptions">
        Calle de San Vicente del Raspeig,
        <br />
        03690, España
        <br />
    </div>
    <br />
    <iframe src="https://www.google.com/maps/embed?pb=!1m14!1m8!1m3!1d12509.730554795442!2d-0.5143161!3d38.3852446!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x0%3A0x506e11c403138428!2sUniversidad%20de%20Alicante!5e0!3m2!1ses!2ses!4v1619720340911!5m2!1ses!2ses" width="600" height="450" style="border: 0;" allowfullscreen="" loading="lazy"></iframe>
    <br />

</asp:Content>
