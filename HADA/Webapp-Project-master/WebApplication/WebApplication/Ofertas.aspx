<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="Ofertas.aspx.cs" Inherits="WebApplication.Ofertas" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/Ofertas.css" rel="stylesheet" />

    <h1 style="margin-left: 20px;">Tarifas</h1>
    <div class="containerOptions" style="display: inline-grid">
        <div id="tarifaNormal">
            <h1>4,90€</h1>
            <p>Tarifa normal</p>

        </div>

        <div>
            <h1>4,50€</h1>
            <p>Tarifa reducida* (Ver descuentos aplicables más abajo).</p>

        </div>

        <div>
            <h1>4,00€</h1>
            <p>Miércoles al Cine (Miércoles, excepto festivos y vísperas de festivo).</p>

        </div>

        <div>
            <h1>4,20€</h1>
            <p>Descuento especial mayores de 65 y desempleados. Lunes y martes. *Excepto festivos y vísperas de festivos.</p>
        </div>

        <div>
            <h1>3D</h1>
            <p>Las películas en 3D no tienen suplemento. Puedes comprar tus gafas 3D por 1,80€ si todavía no dispones de ellas.</p>
        </div>
    </div>
    <h4>*Tarifa reducida: Descuento sobre tarifa normal para Carné Joven, Carné Universitario, discapacidad, mayores de 65 y menores de 14 años. Se pedirá documento acreditativo a la entrada del cine. En el caso de los eventos, no todos aceptan descuentos, por favor, consulte en taquilla.
    </h4>

</asp:Content>
