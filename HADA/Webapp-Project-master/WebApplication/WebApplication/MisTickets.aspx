<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="MisTickets.aspx.cs" Inherits="WebApplication.MisTickets" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">

</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
        <link href="content/Index.css" rel="stylesheet" />
        <div class="containermisTickets">
            



                <h3>
								<strong> Tickets Comprados 
                                <asp:Button ID="ButtomVolver" runat="server" style="margin-left: 501px" Text="Volver" OnClick="onVolver" Width="66px" />
                                </strong>

							</h3>
							    <div class="carteleraContainer">
        <asp:ListView ID="ListView1" runat="server">
            <ItemTemplate>
                <div class="list" runat="server">
                    <table class="parent">
                        <tr>
                            <td>
                                <a class="thumbnail" href="<%#"/Pelicula.aspx?p="+ Eval("id") %>">
                                    <img class="cartelPelicula" visible='<%# !Eval("miniatura").Equals("") %>' src="<%#Eval("miniatura") %>" alt="cartel_pelicula" >
                                </a>

                            &nbsp;</td>
                        </tr>
                    </table>
                </div>
            </ItemTemplate>
        </asp:ListView>
    </div>

            </div>


</asp:Content>
