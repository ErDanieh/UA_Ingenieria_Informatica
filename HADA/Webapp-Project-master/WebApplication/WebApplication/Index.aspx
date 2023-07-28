<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="Index.aspx.cs" Inherits="WebApplication.Index" %>


<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>


<asp:Content ID="Cartelera" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/Index.css" rel="stylesheet" />

    <div class="container">

        <div data-am-fadeshow="next-prev-navigation">

            <!-- Radio -->
            <input type="radio" name="css-fadeshow" id="slide-1" />
            <input type="radio" name="css-fadeshow" id="slide-2" />
            <input type="radio" name="css-fadeshow" id="slide-3" />

            <!-- Slides -->
            <div class="fs-slides">
                <div class="fs-slide" style="background-image: url(https://www.cinesa.es/Manager/promociones/2572/5186.jpg); background-size: contain; background-position: center; background-color: #160202;">
                </div>
                <div class="fs-slide" style="background-image: url(https://www.cinesa.es/Manager/promociones/2557/5155.jpg);"></div>
                <div class="fs-slide" style="background-image: url(assets/banner.jpg);"></div>
            </div>

            <!-- Quick Navigation -->
            <div class="fs-quick-nav">
                <label class="fs-quick-btn" for="slide-1"></label>
                <label class="fs-quick-btn" for="slide-2"></label>
                <label class="fs-quick-btn" for="slide-3"></label>
            </div>

            <!-- Prev Navigation -->
            <div class="fs-prev-nav">
                <label class="fs-prev-btn" for="slide-1"></label>
                <label class="fs-prev-btn" for="slide-2"></label>
                <label class="fs-prev-btn" for="slide-3"></label>
            </div>

            <!-- Next Navigation -->
            <div class="fs-next-nav">
                <label class="fs-next-btn" for="slide-1"></label>
                <label class="fs-next-btn" for="slide-2"></label>
                <label class="fs-next-btn" for="slide-3"></label>
            </div>

        </div>

    </div>



    <h1 class="tituloCartelera">CARTELERA </h1>


    <div class="filtrado">
        <h2>Filtrar películas: </h2>
        <div>
            <asp:DropDownList ID="seleccionGenero" runat="server" AutoPostBack="true" OnSelectedIndexChanged="filtradoPeliculas" CssClass="seleccionadorHorario">
            </asp:DropDownList>


            <asp:DropDownList ID="orderBy" runat="server" AutoPostBack="true" OnSelectedIndexChanged="filtradoPeliculas" CssClas="seleccionadorHorario">
                <%--<asp:ListItem Text="Ordenar por puntuacion: " Value=""></asp:ListItem>--%>
                <asp:ListItem Text="Ascendente" Value="ASC"></asp:ListItem>
                <asp:ListItem Text="Descendente" Value="DESC"></asp:ListItem>
            </asp:DropDownList>
        </div>

    </div>




    <div class="carteleraContainer">
        <asp:ListView ID="ListView1" runat="server">
            <ItemTemplate>
                <div class="list" runat="server">

                    <a class="thumbnail" href="<%#"/Pelicula.aspx?p="+ Eval("id") %>">
                        <img class="cartelPelicula" visible='<%# !Eval("miniatura").Equals("") %>' src="<%#Eval("miniatura") %>" alt="cartel_pelicula">
                    </a>

                </div>
            </ItemTemplate>
        </asp:ListView>
    </div>

</asp:Content>
