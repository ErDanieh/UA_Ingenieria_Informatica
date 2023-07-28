<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="CompraCheckout.aspx.cs" Inherits="WebApplication.CompraCheckout" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/CompraCheckout.css" rel="stylesheet" />
    <h1>MÉTODO DE PAGO</h1>



    <div class="containerOptions">
        <asp:Label ID="nombrePelicula" runat="server" Text=""></asp:Label>
        <asp:Image ID="imagenPelicula" runat="server" ImageUrl="" />

        <p>PRECIO A PAGAR:</p>
        <asp:Label ID="Label2" runat="server" Text=""></asp:Label>
        <br />
        <p id="asientos">Numero de asientos comprados : </p>
        <asp:Label ID="Label3" runat="server" Text=""></asp:Label>

        <p id="metodo">Método de pago: </p>
        <p id="text_tarjeta">Tarjeta de crédito/débito </p>

        <p id="text_numtj">Número de tarjeta: </p>
        <asp:TextBox ID="numTarjeta" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ForeColor="Red" ErrorMessage="*" ControlToValidate="numTarjeta"></asp:RequiredFieldValidator>
        <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ForeColor="Red" ErrorMessage="XXXX-XXXX-XXXX-XXXX" ControlToValidate="numTarjeta"
            ValidationExpression="\d{4}-\d{4}-\d{4}-\d{4}" Display="Dynamic">
        </asp:RegularExpressionValidator>

        <p id="fecha_txt">Fecha de caducidad: </p>
        <asp:DropDownList ID="mes" runat="server" AutoPostBack="False">
            <asp:ListItem Value="">--</asp:ListItem>
            <asp:ListItem Value="01">01</asp:ListItem>
            <asp:ListItem Value="02">02</asp:ListItem>
            <asp:ListItem Value="03">03</asp:ListItem>
            <asp:ListItem Value="04">04</asp:ListItem>
            <asp:ListItem Value="05">05</asp:ListItem>
            <asp:ListItem Value="06">06</asp:ListItem>
            <asp:ListItem Value="07">07</asp:ListItem>
            <asp:ListItem Value="08">08</asp:ListItem>
            <asp:ListItem Value="09">09</asp:ListItem>
            <asp:ListItem Value="10">10</asp:ListItem>
            <asp:ListItem Value="11">11</asp:ListItem>
            <asp:ListItem Value="12">12</asp:ListItem>
        </asp:DropDownList>
        <asp:RequiredFieldValidator ID="comprobarMes" ControlToValidate="mes" InitialValue="" runat="server" ForeColor="Red" ErrorMessage="*" Display="Dynamic"></asp:RequiredFieldValidator>

        <asp:DropDownList ID="año" runat="server" AutoPostBack="false">
            <asp:ListItem Value="">--</asp:ListItem>
            <asp:ListItem Value="2020">2020</asp:ListItem>
            <asp:ListItem Value="2021">2021</asp:ListItem>
            <asp:ListItem Value="2022">2022</asp:ListItem>
            <asp:ListItem Value="2023">2023</asp:ListItem>
            <asp:ListItem Value="2024">2024</asp:ListItem>
            <asp:ListItem Value="2025">2025</asp:ListItem>
            <asp:ListItem Value="2026">2026</asp:ListItem>
            <asp:ListItem Value="2027">2027</asp:ListItem>
            <asp:ListItem Value="2028">2028</asp:ListItem>
            <asp:ListItem Value="2029">2029</asp:ListItem>
            <asp:ListItem Value="2030">2030</asp:ListItem>
            <asp:ListItem Value="2031">2031</asp:ListItem>
            <asp:ListItem Value="2032">2032</asp:ListItem>
            <asp:ListItem Value="2033">2033</asp:ListItem>
            <asp:ListItem Value="2034">2034</asp:ListItem>
            <asp:ListItem Value="2035">2035</asp:ListItem>
            <asp:ListItem Value="2036">2036</asp:ListItem>
            <asp:ListItem Value="2037">2037</asp:ListItem>
            <asp:ListItem Value="2038">2038</asp:ListItem>
            <asp:ListItem Value="2039">2039</asp:ListItem>
            <asp:ListItem Value="2040">2040</asp:ListItem>
            <asp:ListItem Value="2041">2041</asp:ListItem>
        </asp:DropDownList>
        <asp:RequiredFieldValidator ID="comprobarAño" ControlToValidate="año" InitialValue="" runat="server" ForeColor="Red" ErrorMessage="*" Display="Dynamic"></asp:RequiredFieldValidator>

        <p id="code_text">Código de seguridad </p>

        <asp:TextBox ID="codigoseguridad" runat="server"></asp:TextBox>
        <asp:RequiredFieldValidator runat="server" ForeColor="Red" ErrorMessage="*" ControlToValidate="codigoseguridad"></asp:RequiredFieldValidator>
        <asp:RegularExpressionValidator ID="RegularExpressionValidator3" runat="server" ForeColor="Red" ErrorMessage="Código de seguridad incorrecto" ControlToValidate="codigoseguridad"
            ValidationExpression="\d{3}" Display="Dynamic">
        </asp:RegularExpressionValidator>



        <asp:Button ID="pagar" runat="server" CssClass="boton" Text="Pagar" OnClick="pagar_Click"></asp:Button>
        <asp:Button ID="seguirComprando" runat="server" CssClass="boton" Text="Seguir comprando" PostBackUrl="~/Index.aspx"></asp:Button>
        <br />
        <asp:Label ID="correo" runat="server" Text=""></asp:Label>
        <br />


    </div>
    <asp:Panel ID="entradaComprada" runat="server" Style="width: 100%; display: flex;">
        <div id="lateral1" style="width: 35%"></div>

        <div id="compra" style="padding: 0px 10px 10px 10px; width: 30%">

            <div>
                <asp:Label ID="precioEntrada" runat="server"></asp:Label>
            </div>

            <br />
            <br />

            <asp:Label ID="EntradaAviso" runat="server" Text=""></asp:Label>
            <br />
            <img runat="server" id="imgCtrl" />
            <br />


        </div>
    </asp:Panel>
</asp:Content>