<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" ErrorPage="~/ErrorPage.aspx" AutoEventWireup="true" CodeBehind="Pelicula.aspx.cs" Inherits="WebApplication.Pelicula" EnableEventValidation="false" ValidateRequest="false" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>

<asp:Content ID="placeholderPelicula" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/Pelicula.css" rel="stylesheet" />
    <link rel="stylesheet" href="Content/foundation.css" />
    <link rel="stylesheet" href="Content/motion-ui.css" />
    <link rel="stylesheet" href="Content/style.css" />
    <link href='https://fonts.googleapis.com/css?family=Lato:300,400,700' rel='stylesheet' type='text/css'>
    <link href='https://fonts.googleapis.com/css?family=Lato:300,400,700' rel='stylesheet' type='text/css'>
    <script src="Scripts/vendor/modernizr.js"></script>

    <div class="PeliculaContainer">

        <div class="colummIzq">
            <asp:ImageButton OnMouseOver="prueba" CssClass="cartelPeliculaIndividual" runat="server" ID="imagenPelicula" />

            <asp:Button ID="pendientes" runat="server" CssClass="BotonesComprar" Text="Añadir a pendientes" OnClick="pendientes_Click"></asp:Button>
        </div>



        <div class="infoPelicula">
            <div>
                <asp:Label class="nombrePelicula" ID="nombrePelicula" runat="server"></asp:Label>
                <asp:Label class="duracion" ID="duracion" runat="server"></asp:Label>
                <asp:Label class="valoracion" ID="valoracion" runat="server"> </asp:Label>

            </div>
            <asp:Label class="genero" ID="genero" runat="server"></asp:Label>
            <br />
            <asp:Label class="descripcion" ID="descripcion" runat="server"></asp:Label>

            <br />
            <h1>Trailer </h1>
            <iframe runat="server" id="trailer" width="720" height="400" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture"></iframe>
            <h1>Horarios </h1>
            <asp:DropDownList ID="seleccionDia" runat="server" AutoPostBack="true" OnSelectedIndexChanged="seleccionDiaChanged" onClick="MostrarA" CssClass="seleccionadorHorario">
            </asp:DropDownList>

            <asp:DropDownList ID="seleccionHora" class="mostraa" runat="server" AutoPostBack="true" OnSelectedIndexChanged="seleccionHoraChanged" CssClass="seleccionadorHorario">
            </asp:DropDownList>

            <asp:Button ID="compraEntradas" runat="server" Text="Reservar" OnClick="Button1_Click" OnClientClick="clientValidate(); return false" />

        </div>

    </div>



    <script src="Scripts/jquery.min.js"></script>
    <script src="Scripts/bootstrap.min.js"></script>
    <script src="Scripts/scripts.js"></script>
    <script src="js/vendor/jquery.js"></script>
    <script src="Scripts/vendor/motion-ui.js"></script>
    <script src="Scripts/foundation.min.js"></script>
    <script src="Scripts/script.js"></script>
    <script type="text/javascript">
        var maxIntentosCompra = 2;
        var numIntentosCompra = 0;
        var currentFila = "";
        var ButacasSeleccionadas = new Map();
        var ButacasSeleccionadas2 = new Map();
        var numButacasSeleccionadas = 0;
        var numButacasSeleccionables = 131;
        var leftNextSelectable = "";
        var rightNextSelectable = "";
        var distanciaSanitaria = "false";
        var reservada = "True"
        var nowMiliseconds = new Date().getTime();
        var SesionTicks = 1620575100000;
        var SessionExpired = (SesionTicks < nowMiliseconds);


        function OnMyMethodComplete(result, userContext, methodName) {
            
        }

        function holaktal() {
            for (i = 1; i < 42; i++) {
                var Butaca = $("#butaca_" + i);
                var ButacaStatus = Butaca.attr("data-vendible")

                if (ButacaStatus == reservada) {
                    MarkAsForbidden(Butaca)
                }
            }

        }

        function clientValidate() {
            ButacasSeleccionadas.forEach(guardaReserva);
            
             window.location = "CompraCheckout.aspx?p=" + document.getElementById("<%=peliS.ClientID%>").value + "&PR=" + document.getElementById("<%=labelPrecio.ClientID%>").innerHTML + "&NUM="+ ButacasSeleccionadas.size ;
            return false
        }


        function MostrarA(){
            $('.transform').toggleClass('transform-active');
            return false;
        }

        function guardaReserva(value, key, map) {
            var fecha = document.getElementById("<%=fechaS.ClientID%>").innerHTML
            var pelicula = document.getElementById("<%=peliS.ClientID%>").value
            PageMethods.MyMethod(key, pelicula, fecha, OnMyMethodComplete);
            sleep(1000);
            return false

        }
        function butaca_click(butacaId) {
            if (numButacasSeleccionadas < 0) numButacasSeleccionadas = 0;
            var Butaca = $("#butaca_" + butacaId);
            if (Butaca != null) changeButacaStatus(Butaca)
        }

        function butacaIsEnabled(Butaca) {
            if (Butaca == null) return false;
            var ButacaImage = Butaca.attr("src");
            return ButacaImage.includes("ButacaTipo_001") || ButacaImage.includes("ButacaTipo_100") || ButacaImage.includes("ButacaTipo_010") || ButacaImage.includes("ButacaTipo_012") || ButacaImage.includes("ButacaTipo_200");
        }
        function butacaIsSelected(Butaca) { return (Butaca != null && Butaca.attr("src") != null && Butaca.attr("src").includes("ButacaTipo_200")); }


        function butacaIsSelectable(Butaca) {
            var butacaId = getId(Butaca);
            return butacaIsEnabled(Butaca);
        }

        function sleep(milliseconds) {
            var start = new Date().getTime();
            for (var i = 0; i < 1e7; i++) {
                if ((new Date().getTime() - start) > milliseconds) {
                    break;
                }
            }
        }

        function getId(Butaca) {
            var butacaId = Butaca.attr("id");
            return butacaId.substring(butacaId.indexOf("_") + 1);
        }

        function changeButacaStatus(Butaca) {
            if (butacaIsSelected(Butaca)) {
                deselectButaca(Butaca);
            } else {
                if (butacaIsSelectable(Butaca)) selectButaca(Butaca);
            }
        }

        function selectButaca(Butaca) {
            var idButaca = getId(Butaca);
            numButacasSeleccionadas = numButacasSeleccionadas + 1;
            ButacasSeleccionadas.set(idButaca, { butaca: Butaca, imgOriginal: Butaca.attr("src") });
            Butaca.attr("src", "assets/butacas/ButacaTipo_200.png");
            var precio = numButacasSeleccionadas * 4.90
            document.getElementById("<%=labelPrecio.ClientID%>").innerHTML = precio.toFixed(2);
        }

        function deselectButaca(Butaca) {
            var idButaca = getId(Butaca);
            numButacasSeleccionadas = numButacasSeleccionadas - 1;
            if (numButacasSeleccionadas < 0) numButacasSeleccionadas = 0;
            Butaca.attr("src", ButacasSeleccionadas.get(idButaca).imgOriginal);
            ButacasSeleccionadas.delete(idButaca);
            var precio = numButacasSeleccionadas * 4.90
            document.getElementById("<%=labelPrecio.ClientID%>").innerHTML = precio.toFixed(2);
        }



        function MarkAsForbidden(butaca) {
            if (butaca != null) {
                butaca.attr("src", "assets/butacas/ButacaTipo_reservada.png");
                if (ButacasSeleccionadas.delete(getId(butaca))) numButacasSeleccionadas = numButacasSeleccionadas - 1;
                if (numButacasSeleccionadas < 0) numButacasSeleccionadas = 0;
                butaca.css('border', "solid 2px red");
            }
        }

        function setButacaAsUnavailable(butacaId) {
            var Butaca = $("#butaca_" + butacaId);
            if (Butaca != null) {
                Butaca.attr("src", "assets/butacas/ButacaTipo_011.png");
                if (ButacasSeleccionadas.delete(butacaId)) numButacasSeleccionadas = numButacasSeleccionadas - 1;
                if (numButacasSeleccionadas < 0) numButacasSeleccionadas = 0;
                Butaca.css('border', "solid 2px red");
            }
        }



        function substractButacaNoNumerada() {
            if (numButacasSeleccionadas > 0) {
                numButacasSeleccionadas--;
                if (numButacasSeleccionadas < 0) numButacasSeleccionadas = 0;
                $('#numButacasLabel').text(numButacasSeleccionadas);
                $('#numButacasSeleccionablesLabel').text((numButacasSeleccionables - numButacasSeleccionadas));
            }
        }
        function addButacaNoNumerada() {
            if (numButacasSeleccionadas < numButacasSeleccionables) {
                numButacasSeleccionadas++;
                $('#numButacasLabel').text(numButacasSeleccionadas);
                $('#numButacasSeleccionablesLabel').text((numButacasSeleccionables - numButacasSeleccionadas));
            }
        }
        window.onload = holaktal();
        window.post
    </script>


    <asp:Label ID="outMsg" runat="server" Text=""></asp:Label>
<asp:ScriptManager ID="ScriptManager1" 
    EnablePageMethods="true" 
    EnablePartialRendering="true" runat="server" />



    <br />
            <div class="Right-Side">
            <div class="box transform">
                <div class="container-fluid vh-300 sambaStart">
                    <div class="row">
                        <div class="col-12">

                            <div id='stars'></div>
                            <div id='stars2'></div>
                            <div id='stars3'></div>

                            <div class="asientosContainer">
                                <asp:ListView ID="ListView2" runat="server">
                                    <ItemTemplate>
                                        <div class="list" runat="server">
                                            <table class="parent">
                                                <tr>
                                                    <td>
                                                        <a class="thumbnail">
                                                            <img class="butaca" id="<%#"butaca_"+ Eval("id_asiento") %>" data-vendible="<%#Eval("estado")%>" onclick="<%#"butaca_click("+ Eval("id_asiento") + ")"   %>" src="assets/butacas/ButacaTipo_001.png">
                                                        </a>
                                                    &nbsp;</td>
                                                </tr>
                                            </table>
                                        </div>
                                    </ItemTemplate>
                                </asp:ListView>
                            </div>
                        </div>
                    </div>
                    <div id="title">
                        <asp:Label ID="labelPrecio" class="preci0" runat="server" Text="0"> </asp:Label>
                    </div>
                </div>
            </div>


        </div>

    <asp:Label ID="fechaS" class="hidden" runat="server" Text="Label"></asp:Label>
    <asp:TextBox ID="peliS" class=" hidden" runat="server" ReadOnly="True"></asp:TextBox>
    <style>
        .hidden {
            visibility: hidden;
        }

        .box {
            height: 0px;
        }

        .transform {
            -webkit-transition: all 2s ease;
            -moz-transition: all 2s ease;
            -o-transition: all 2s ease;
            -ms-transition: all 2s ease;
            transition: all 2s ease;
        }

        .transform-active {
            height: 550px;
        }
        .Right-Side{
            height: 20px;
            width: 600px;
            position:  sticky;
            margin-left: 260px;
            margin-bottom: 600px;
}
        .asientosContainer {
            display: grid;
            justify-content: center;
            align-content: center;
            grid-gap: 0.1px;
            grid-template-columns: repeat(8, 1fr);
        }

        .butaca {
            min-width: 10px;
            min-height: 10px;
            max-width: 100%;
            max-height: 100%;
        }

        .sambaStart {
            height: 150%;
            background: radial-gradient(ellipse at bottom, #1b2735 0%, #090a0f 100%);
            overflow: hidden;
            border-radius: 60px/20px;
        }

        .vh-300 {
            height: 110%;
        }

        #stars {
            width: 1px;
            height: 1px;
            background: transparent;
            box-shadow: 1426px 843px #FFF, 1152px 196px #FFF, 976px 1921px #FFF, 1474px 1954px #FFF, 285px 44px #FFF, 386px 915px #FFF, 1150px 682px #FFF, 176px 1398px #FFF, 1046px 976px #FFF, 1447px 627px #FFF, 469px 1521px #FFF, 317px 90px #FFF, 1412px 1112px #FFF, 1112px 841px #FFF, 88px 1941px #FFF, 1418px 1766px #FFF, 434px 578px #FFF, 343px 553px #FFF, 1883px 1567px #FFF, 1098px 868px #FFF, 1946px 697px #FFF, 1237px 1298px #FFF, 363px 361px #FFF, 1767px 1434px #FFF, 154px 1029px #FFF, 1713px 1880px #FFF, 1179px 185px #FFF, 1090px 1877px #FFF, 1317px 825px #FFF, 1331px 857px #FFF, 899px 199px #FFF, 652px 159px #FFF, 745px 1583px #FFF, 627px 1340px #FFF, 403px 1282px #FFF, 1054px 1991px #FFF, 1761px 375px #FFF, 1435px 992px #FFF, 1397px 222px #FFF, 776px 1280px #FFF, 889px 1791px #FFF, 1463px 960px #FFF, 629px 1538px #FFF, 832px 1074px #FFF, 1233px 1434px #FFF, 724px 316px #FFF, 1503px 957px #FFF, 49px 1374px #FFF, 624px 1761px #FFF, 82px 1542px #FFF, 1232px 1564px #FFF, 97px 1944px #FFF, 1272px 165px #FFF, 1251px 556px #FFF, 749px 1819px #FFF, 1063px 231px #FFF, 1100px 1955px #FFF, 1022px 86px #FFF, 1071px 129px #FFF, 64px 1450px #FFF, 1977px 1184px #FFF, 1992px 1921px #FFF, 1514px 515px #FFF, 1027px 80px #FFF, 335px 1947px #FFF, 1965px 1349px #FFF, 1915px 1747px #FFF, 790px 1162px #FFF, 739px 1292px #FFF, 602px 1650px #FFF, 368px 369px #FFF, 1137px 720px #FFF, 580px 1781px #FFF, 1488px 1808px #FFF, 691px 801px #FFF, 729px 1769px #FFF, 1833px 1893px #FFF, 1059px 639px #FFF, 344px 1618px #FFF, 1666px 1585px #FFF, 1885px 1119px #FFF, 1182px 461px #FFF, 983px 545px #FFF, 1946px 1679px #FFF, 1491px 1254px #FFF, 764px 1317px #FFF, 501px 1996px #FFF, 1526px 1522px #FFF, 575px 661px #FFF, 837px 1315px #FFF, 1988px 1057px #FFF, 679px 198px #FFF, 701px 701px #FFF, 690px 852px #FFF, 226px 634px #FFF, 1577px 602px #FFF, 178px 1103px #FFF, 1439px 788px #FFF, 1788px 998px #FFF, 835px 722px #FFF, 816px 571px #FFF, 1240px 1656px #FFF, 849px 727px #FFF, 1066px 838px #FFF, 1809px 860px #FFF, 95px 525px #FFF, 524px 841px #FFF, 1668px 375px #FFF, 239px 620px #FFF, 495px 1491px #FFF, 860px 1615px #FFF, 437px 7px #FFF, 1122px 1081px #FFF, 1694px 1432px #FFF, 871px 647px #FFF, 289px 1760px #FFF, 1558px 542px #FFF, 1234px 1026px #FFF, 1299px 1965px #FFF, 827px 1713px #FFF, 1736px 1120px #FFF, 149px 1319px #FFF, 1338px 1888px #FFF, 1304px 1030px #FFF, 1230px 1008px #FFF, 1442px 921px #FFF, 1584px 352px #FFF, 1898px 845px #FFF, 744px 1026px #FFF, 494px 646px #FFF, 224px 1697px #FFF, 592px 1435px #FFF, 1546px 1494px #FFF, 1006px 1620px #FFF, 371px 530px #FFF, 1682px 1409px #FFF, 702px 1802px #FFF, 921px 17px #FFF, 279px 1183px #FFF, 1389px 1846px #FFF, 119px 1846px #FFF, 1495px 414px #FFF, 1351px 1903px #FFF, 1049px 1712px #FFF, 919px 1816px #FFF, 1052px 605px #FFF, 155px 117px #FFF, 1764px 655px #FFF, 1850px 915px #FFF, 1162px 760px #FFF, 1920px 407px #FFF, 1331px 1351px #FFF, 776px 800px #FFF, 1785px 1555px #FFF, 1526px 1606px #FFF, 386px 91px #FFF, 1156px 1502px #FFF, 209px 1297px #FFF, 239px 10px #FFF, 1313px 437px #FFF, 1889px 572px #FFF, 423px 785px #FFF, 1819px 1127px #FFF, 1640px 136px #FFF, 420px 1265px #FFF, 773px 1402px #FFF, 1745px 536px #FFF, 1995px 182px #FFF, 968px 543px #FFF, 329px 1457px #FFF, 1233px 1088px #FFF, 439px 1844px #FFF, 234px 114px #FFF, 1374px 205px #FFF, 1146px 643px #FFF, 1843px 1587px #FFF, 1122px 1816px #FFF, 691px 665px #FFF, 1495px 944px #FFF, 53px 663px #FFF, 1403px 1002px #FFF, 1999px 1176px #FFF, 1319px 1529px #FFF, 434px 333px #FFF, 905px 1980px #FFF, 394px 1393px #FFF, 450px 1280px #FFF, 868px 741px #FFF, 216px 1622px #FFF, 222px 1079px #FFF, 612px 1650px #FFF, 976px 1715px #FFF, 1834px 53px #FFF, 1px 1077px #FFF, 609px 712px #FFF, 1162px 1402px #FFF, 1570px 869px #FFF, 546px 61px #FFF, 1951px 1945px #FFF, 564px 1164px #FFF, 534px 1247px #FFF, 1309px 1890px #FFF, 1813px 969px #FFF, 114px 792px #FFF, 1104px 1777px #FFF, 115px 1009px #FFF, 1541px 565px #FFF, 226px 653px #FFF, 183px 494px #FFF, 1218px 49px #FFF, 1436px 344px #FFF, 1668px 247px #FFF, 468px 1274px #FFF, 1992px 1185px #FFF, 244px 1699px #FFF, 783px 695px #FFF, 271px 1746px #FFF, 1239px 1571px #FFF, 1089px 1317px #FFF, 1251px 1056px #FFF, 1950px 920px #FFF, 342px 829px #FFF, 438px 85px #FFF, 132px 1759px #FFF, 1221px 129px #FFF, 614px 405px #FFF, 1227px 134px #FFF, 177px 1555px #FFF, 278px 1694px #FFF, 1215px 42px #FFF, 165px 108px #FFF, 1299px 262px #FFF, 607px 777px #FFF, 162px 1604px #FFF, 1486px 711px #FFF, 506px 466px #FFF, 20px 1274px #FFF, 747px 1507px #FFF, 871px 1028px #FFF, 873px 52px #FFF, 258px 1040px #FFF, 157px 330px #FFF, 517px 1747px #FFF, 162px 1116px #FFF, 1856px 1308px #FFF, 691px 1890px #FFF, 376px 1885px #FFF, 1415px 1843px #FFF, 337px 571px #FFF, 221px 1479px #FFF, 1025px 274px #FFF, 485px 1805px #FFF, 505px 1517px #FFF, 1313px 597px #FFF, 1412px 77px #FFF, 447px 1374px #FFF, 461px 1917px #FFF, 23px 934px #FFF, 754px 1701px #FFF, 496px 1834px #FFF, 26px 1850px #FFF, 995px 851px #FFF, 877px 379px #FFF, 281px 1305px #FFF, 592px 847px #FFF, 1735px 1656px #FFF, 608px 764px #FFF, 1537px 50px #FFF, 1591px 141px #FFF, 317px 1977px #FFF, 1177px 1694px #FFF, 207px 227px #FFF, 125px 992px #FFF, 1025px 599px #FFF, 1681px 1110px #FFF, 1531px 288px #FFF, 1408px 1393px #FFF, 426px 1105px #FFF, 656px 1418px #FFF, 957px 1613px #FFF, 1450px 1116px #FFF, 1485px 992px #FFF, 1991px 1401px #FFF, 1595px 1258px #FFF, 473px 1782px #FFF, 605px 263px #FFF, 662px 1215px #FFF, 1127px 1103px #FFF, 684px 1640px #FFF, 401px 1035px #FFF, 933px 1544px #FFF, 1135px 1674px #FFF, 1121px 1587px #FFF, 1319px 1546px #FFF, 827px 724px #FFF, 619px 664px #FFF, 1741px 1834px #FFF, 1033px 1566px #FFF, 1165px 65px #FFF, 856px 1446px #FFF, 308px 1504px #FFF, 907px 1161px #FFF, 1499px 1029px #FFF, 1399px 1240px #FFF, 855px 1109px #FFF, 1400px 1553px #FFF, 1540px 993px #FFF, 1702px 979px #FFF, 412px 1857px #FFF, 45px 1308px #FFF, 1948px 1576px #FFF, 1534px 927px #FFF, 479px 1249px #FFF, 624px 1904px #FFF, 417px 1823px #FFF, 1510px 310px #FFF, 963px 1534px #FFF, 1781px 348px #FFF, 215px 1083px #FFF, 739px 190px #FFF, 1843px 1071px #FFF, 593px 502px #FFF, 1239px 1043px #FFF, 645px 1487px #FFF, 1866px 242px #FFF, 1549px 36px #FFF, 1935px 663px #FFF, 142px 1466px #FFF, 1672px 487px #FFF, 145px 1483px #FFF, 957px 201px #FFF, 459px 855px #FFF, 1773px 988px #FFF, 446px 335px #FFF, 1982px 1239px #FFF, 1519px 1661px #FFF, 594px 424px #FFF, 870px 1800px #FFF, 125px 1136px #FFF, 636px 442px #FFF, 414px 1677px #FFF, 1204px 1588px #FFF, 1587px 1250px #FFF, 796px 507px #FFF, 181px 861px #FFF, 1602px 1106px #FFF, 58px 674px #FFF, 585px 1706px #FFF, 586px 1501px #FFF, 1602px 614px #FFF, 1614px 1179px #FFF, 282px 1907px #FFF, 1689px 348px #FFF, 1033px 302px #FFF, 290px 1260px #FFF, 236px 926px #FFF, 174px 98px #FFF, 1427px 95px #FFF, 22px 1019px #FFF, 275px 1241px #FFF, 1203px 1330px #FFF, 798px 1713px #FFF, 445px 983px #FFF, 805px 1879px #FFF, 672px 973px #FFF, 269px 235px #FFF, 1526px 1791px #FFF, 790px 1860px #FFF, 109px 516px #FFF, 321px 1783px #FFF, 1700px 714px #FFF, 22px 913px #FFF, 1152px 1567px #FFF, 1588px 1367px #FFF, 206px 418px #FFF, 1761px 951px #FFF, 828px 682px #FFF, 1942px 1786px #FFF, 866px 409px #FFF, 1400px 560px #FFF, 1303px 264px #FFF, 1559px 1200px #FFF, 211px 393px #FFF, 1760px 327px #FFF, 559px 1359px #FFF, 1621px 1748px #FFF, 1228px 470px #FFF, 992px 504px #FFF, 50px 781px #FFF, 722px 553px #FFF, 430px 1530px #FFF, 969px 1682px #FFF, 912px 1094px #FFF, 1605px 121px #FFF, 269px 1321px #FFF, 1387px 1504px #FFF, 1809px 1668px #FFF, 1790px 1537px #FFF, 702px 392px #FFF, 1066px 1097px #FFF, 1772px 1632px #FFF, 169px 1237px #FFF, 650px 324px #FFF, 1927px 1938px #FFF, 939px 517px #FFF, 591px 128px #FFF, 1433px 1030px #FFF, 1548px 416px #FFF, 1302px 721px #FFF, 133px 1460px #FFF, 1221px 1954px #FFF, 1957px 340px #FFF, 1080px 1787px #FFF, 1068px 1315px #FFF, 830px 1082px #FFF, 272px 1374px #FFF, 995px 1440px #FFF, 594px 760px #FFF, 1209px 1185px #FFF, 1193px 1340px #FFF, 157px 256px #FFF, 62px 338px #FFF, 1319px 1319px #FFF, 1330px 729px #FFF, 1439px 1589px #FFF, 60px 1410px #FFF, 1205px 690px #FFF, 1493px 1982px #FFF, 1595px 515px #FFF, 1968px 814px #FFF, 1265px 403px #FFF, 572px 1577px #FFF, 806px 112px #FFF, 336px 1414px #FFF, 982px 585px #FFF, 768px 248px #FFF, 1381px 958px #FFF, 585px 560px #FFF, 40px 1193px #FFF, 961px 1316px #FFF, 1795px 498px #FFF, 361px 473px #FFF, 365px 252px #FFF, 1459px 1423px #FFF, 442px 792px #FFF, 1932px 1437px #FFF, 877px 1131px #FFF, 1585px 1717px #FFF, 548px 232px #FFF, 488px 432px #FFF, 1234px 688px #FFF, 250px 1388px #FFF, 167px 1334px #FFF, 793px 777px #FFF, 979px 1802px #FFF, 1328px 1189px #FFF, 1817px 554px #FFF, 637px 543px #FFF, 304px 503px #FFF, 1664px 1112px #FFF, 674px 1529px #FFF, 1761px 1834px #FFF, 1003px 1724px #FFF, 1591px 291px #FFF, 925px 1020px #FFF, 378px 72px #FFF, 1447px 17px #FFF, 797px 1880px #FFF, 1910px 11px #FFF, 1877px 543px #FFF, 1567px 1293px #FFF, 1021px 213px #FFF, 1778px 1923px #FFF, 884px 1392px #FFF, 820px 1005px #FFF, 1492px 662px #FFF, 1741px 1327px #FFF, 1182px 1680px #FFF, 1555px 1065px #FFF, 819px 1438px #FFF, 1953px 995px #FFF, 1918px 48px #FFF, 1307px 1282px #FFF, 989px 605px #FFF, 1829px 880px #FFF, 279px 1559px #FFF, 187px 442px #FFF, 1993px 1598px #FFF, 1393px 1023px #FFF, 218px 1524px #FFF, 445px 1060px #FFF, 1741px 1748px #FFF, 1577px 943px #FFF, 1845px 373px #FFF, 1541px 1069px #FFF, 102px 1906px #FFF, 1851px 1054px #FFF, 1310px 269px #FFF, 1935px 14px #FFF, 876px 695px #FFF, 832px 575px #FFF, 1928px 312px #FFF, 1864px 1684px #FFF, 1369px 923px #FFF, 1840px 1795px #FFF, 136px 1077px #FFF, 1372px 26px #FFF, 386px 492px #FFF, 391px 1128px #FFF, 472px 824px #FFF, 679px 1495px #FFF, 938px 1510px #FFF, 415px 1126px #FFF, 728px 198px #FFF, 1570px 1315px #FFF, 234px 1612px #FFF, 639px 41px #FFF, 1132px 289px #FFF, 347px 800px #FFF, 759px 1595px #FFF, 1224px 374px #FFF, 1px 1769px #FFF, 637px 608px #FFF, 308px 592px #FFF, 1065px 960px #FFF, 794px 1460px #FFF, 1510px 206px #FFF, 1178px 1755px #FFF, 1599px 1956px #FFF, 691px 1131px #FFF, 256px 271px #FFF, 1291px 1522px #FFF, 1048px 1639px #FFF, 964px 976px #FFF, 803px 987px #FFF, 787px 2000px #FFF, 419px 1750px #FFF, 158px 79px #FFF, 759px 1444px #FFF, 1116px 1442px #FFF, 987px 1524px #FFF, 1201px 1358px #FFF, 1622px 275px #FFF, 390px 1284px #FFF, 1623px 598px #FFF, 191px 1296px #FFF, 725px 652px #FFF, 1478px 854px #FFF, 385px 1530px #FFF, 1859px 1135px #FFF, 1760px 1140px #FFF, 1751px 1483px #FFF, 773px 1859px #FFF, 1228px 744px #FFF, 469px 1201px #FFF, 1568px 1475px #FFF, 1329px 1994px #FFF, 768px 1507px #FFF, 1713px 1161px #FFF, 1993px 1294px #FFF, 194px 39px #FFF, 1872px 1371px #FFF, 295px 437px #FFF, 22px 1391px #FFF, 1334px 1846px #FFF, 639px 1876px #FFF, 1939px 1270px #FFF, 811px 1428px #FFF, 1317px 1446px #FFF, 1854px 1342px #FFF, 1681px 1487px #FFF, 1748px 771px #FFF, 1058px 1446px #FFF, 1585px 1908px #FFF, 765px 643px #FFF, 1751px 1176px #FFF, 480px 741px #FFF, 487px 608px #FFF, 684px 900px #FFF, 1866px 583px #FFF, 296px 754px #FFF, 312px 1183px #FFF, 988px 1556px #FFF, 1476px 1985px #FFF, 594px 1200px #FFF, 728px 1542px #FFF, 1314px 331px #FFF, 654px 419px #FFF, 1122px 1623px #FFF, 62px 1154px #FFF, 1556px 1824px #FFF, 218px 31px #FFF, 1701px 18px #FFF, 1672px 1958px #FFF, 376px 1061px #FFF, 1763px 1025px #FFF, 1060px 1218px #FFF, 1839px 1702px #FFF, 22px 904px #FFF, 826px 51px #FFF, 1681px 315px #FFF, 235px 1227px #FFF, 1350px 1219px #FFF, 1610px 548px #FFF, 1002px 211px #FFF, 1626px 693px #FFF, 1757px 205px #FFF, 724px 889px #FFF, 997px 1988px #FFF, 62px 839px #FFF, 505px 1123px #FFF, 1562px 1210px #FFF, 1475px 716px #FFF, 1534px 1110px #FFF, 665px 266px #FFF, 1068px 1063px #FFF, 14px 907px #FFF, 176px 44px #FFF, 1737px 275px #FFF, 1126px 1716px #FFF, 606px 1075px #FFF, 1676px 677px #FFF, 1456px 1934px #FFF, 566px 569px #FFF, 1029px 669px #FFF, 1277px 1220px #FFF, 1662px 508px #FFF, 1355px 1829px #FFF, 1704px 846px #FFF, 1289px 1481px #FFF, 940px 834px #FFF, 556px 162px #FFF, 1347px 1122px #FFF, 410px 627px #FFF, 1693px 420px #FFF, 1008px 1221px #FFF, 218px 1118px #FFF, 1983px 1588px #FFF, 399px 149px #FFF, 94px 1339px #FFF, 1833px 1054px #FFF, 82px 1438px #FFF, 394px 852px #FFF, 1786px 910px #FFF, 1397px 203px #FFF, 1450px 1692px #FFF, 249px 171px #FFF, 1715px 1935px #FFF, 115px 1966px #FFF, 225px 932px #FFF, 1713px 1040px #FFF, 1311px 1409px #FFF, 752px 1894px #FFF, 1042px 361px #FFF, 1032px 768px #FFF, 90px 1095px #FFF, 357px 84px #FFF, 1028px 1051px #FFF, 1794px 1310px #FFF, 1532px 1910px #FFF, 1533px 1680px #FFF, 1892px 1087px #FFF, 521px 133px #FFF, 1936px 1694px #FFF, 646px 287px #FFF, 717px 682px #FFF, 937px 1091px #FFF, 1278px 652px #FFF, 1149px 107px #FFF, 49px 1107px #FFF, 838px 1425px #FFF, 523px 1253px #FFF, 1813px 1747px #FFF, 1575px 1628px #FFF, 1416px 1204px #FFF, 1146px 481px #FFF, 482px 1643px #FFF, 1072px 488px #FFF, 1971px 1889px #FFF, 1626px 1231px #FFF, 569px 713px #FFF, 1769px 1045px #FFF, 803px 1902px #FFF, 1415px 709px #FFF, 977px 265px #FFF, 864px 596px #FFF, 1090px 1019px #FFF, 1095px 1699px #FFF, 331px 1000px #FFF, 1445px 685px #FFF, 353px 583px #FFF, 550px 193px #FFF, 934px 156px #FFF, 721px 1299px #FFF, 817px 1021px #FFF, 560px 623px #FFF, 1618px 1459px #FFF, 284px 1232px #FFF, 1527px 925px #FFF, 1735px 1369px #FFF;
            animation: animStar 50s linear infinite;
        }

            #stars:after {
                content: " ";
                position: absolute;
                top: 2000px;
                width: 1px;
                height: 1px;
                background: transparent;
                box-shadow: 1426px 843px #FFF, 1152px 196px #FFF, 976px 1921px #FFF, 1474px 1954px #FFF, 285px 44px #FFF, 386px 915px #FFF, 1150px 682px #FFF, 176px 1398px #FFF, 1046px 976px #FFF, 1447px 627px #FFF, 469px 1521px #FFF, 317px 90px #FFF, 1412px 1112px #FFF, 1112px 841px #FFF, 88px 1941px #FFF, 1418px 1766px #FFF, 434px 578px #FFF, 343px 553px #FFF, 1883px 1567px #FFF, 1098px 868px #FFF, 1946px 697px #FFF, 1237px 1298px #FFF, 363px 361px #FFF, 1767px 1434px #FFF, 154px 1029px #FFF, 1713px 1880px #FFF, 1179px 185px #FFF, 1090px 1877px #FFF, 1317px 825px #FFF, 1331px 857px #FFF, 899px 199px #FFF, 652px 159px #FFF, 745px 1583px #FFF, 627px 1340px #FFF, 403px 1282px #FFF, 1054px 1991px #FFF, 1761px 375px #FFF, 1435px 992px #FFF, 1397px 222px #FFF, 776px 1280px #FFF, 889px 1791px #FFF, 1463px 960px #FFF, 629px 1538px #FFF, 832px 1074px #FFF, 1233px 1434px #FFF, 724px 316px #FFF, 1503px 957px #FFF, 49px 1374px #FFF, 624px 1761px #FFF, 82px 1542px #FFF, 1232px 1564px #FFF, 97px 1944px #FFF, 1272px 165px #FFF, 1251px 556px #FFF, 749px 1819px #FFF, 1063px 231px #FFF, 1100px 1955px #FFF, 1022px 86px #FFF, 1071px 129px #FFF, 64px 1450px #FFF, 1977px 1184px #FFF, 1992px 1921px #FFF, 1514px 515px #FFF, 1027px 80px #FFF, 335px 1947px #FFF, 1965px 1349px #FFF, 1915px 1747px #FFF, 790px 1162px #FFF, 739px 1292px #FFF, 602px 1650px #FFF, 368px 369px #FFF, 1137px 720px #FFF, 580px 1781px #FFF, 1488px 1808px #FFF, 691px 801px #FFF, 729px 1769px #FFF, 1833px 1893px #FFF, 1059px 639px #FFF, 344px 1618px #FFF, 1666px 1585px #FFF, 1885px 1119px #FFF, 1182px 461px #FFF, 983px 545px #FFF, 1946px 1679px #FFF, 1491px 1254px #FFF, 764px 1317px #FFF, 501px 1996px #FFF, 1526px 1522px #FFF, 575px 661px #FFF, 837px 1315px #FFF, 1988px 1057px #FFF, 679px 198px #FFF, 701px 701px #FFF, 690px 852px #FFF, 226px 634px #FFF, 1577px 602px #FFF, 178px 1103px #FFF, 1439px 788px #FFF, 1788px 998px #FFF, 835px 722px #FFF, 816px 571px #FFF, 1240px 1656px #FFF, 849px 727px #FFF, 1066px 838px #FFF, 1809px 860px #FFF, 95px 525px #FFF, 524px 841px #FFF, 1668px 375px #FFF, 239px 620px #FFF, 495px 1491px #FFF, 860px 1615px #FFF, 437px 7px #FFF, 1122px 1081px #FFF, 1694px 1432px #FFF, 871px 647px #FFF, 289px 1760px #FFF, 1558px 542px #FFF, 1234px 1026px #FFF, 1299px 1965px #FFF, 827px 1713px #FFF, 1736px 1120px #FFF, 149px 1319px #FFF, 1338px 1888px #FFF, 1304px 1030px #FFF, 1230px 1008px #FFF, 1442px 921px #FFF, 1584px 352px #FFF, 1898px 845px #FFF, 744px 1026px #FFF, 494px 646px #FFF, 224px 1697px #FFF, 592px 1435px #FFF, 1546px 1494px #FFF, 1006px 1620px #FFF, 371px 530px #FFF, 1682px 1409px #FFF, 702px 1802px #FFF, 921px 17px #FFF, 279px 1183px #FFF, 1389px 1846px #FFF, 119px 1846px #FFF, 1495px 414px #FFF, 1351px 1903px #FFF, 1049px 1712px #FFF, 919px 1816px #FFF, 1052px 605px #FFF, 155px 117px #FFF, 1764px 655px #FFF, 1850px 915px #FFF, 1162px 760px #FFF, 1920px 407px #FFF, 1331px 1351px #FFF, 776px 800px #FFF, 1785px 1555px #FFF, 1526px 1606px #FFF, 386px 91px #FFF, 1156px 1502px #FFF, 209px 1297px #FFF, 239px 10px #FFF, 1313px 437px #FFF, 1889px 572px #FFF, 423px 785px #FFF, 1819px 1127px #FFF, 1640px 136px #FFF, 420px 1265px #FFF, 773px 1402px #FFF, 1745px 536px #FFF, 1995px 182px #FFF, 968px 543px #FFF, 329px 1457px #FFF, 1233px 1088px #FFF, 439px 1844px #FFF, 234px 114px #FFF, 1374px 205px #FFF, 1146px 643px #FFF, 1843px 1587px #FFF, 1122px 1816px #FFF, 691px 665px #FFF, 1495px 944px #FFF, 53px 663px #FFF, 1403px 1002px #FFF, 1999px 1176px #FFF, 1319px 1529px #FFF, 434px 333px #FFF, 905px 1980px #FFF, 394px 1393px #FFF, 450px 1280px #FFF, 868px 741px #FFF, 216px 1622px #FFF, 222px 1079px #FFF, 612px 1650px #FFF, 976px 1715px #FFF, 1834px 53px #FFF, 1px 1077px #FFF, 609px 712px #FFF, 1162px 1402px #FFF, 1570px 869px #FFF, 546px 61px #FFF, 1951px 1945px #FFF, 564px 1164px #FFF, 534px 1247px #FFF, 1309px 1890px #FFF, 1813px 969px #FFF, 114px 792px #FFF, 1104px 1777px #FFF, 115px 1009px #FFF, 1541px 565px #FFF, 226px 653px #FFF, 183px 494px #FFF, 1218px 49px #FFF, 1436px 344px #FFF, 1668px 247px #FFF, 468px 1274px #FFF, 1992px 1185px #FFF, 244px 1699px #FFF, 783px 695px #FFF, 271px 1746px #FFF, 1239px 1571px #FFF, 1089px 1317px #FFF, 1251px 1056px #FFF, 1950px 920px #FFF, 342px 829px #FFF, 438px 85px #FFF, 132px 1759px #FFF, 1221px 129px #FFF, 614px 405px #FFF, 1227px 134px #FFF, 177px 1555px #FFF, 278px 1694px #FFF, 1215px 42px #FFF, 165px 108px #FFF, 1299px 262px #FFF, 607px 777px #FFF, 162px 1604px #FFF, 1486px 711px #FFF, 506px 466px #FFF, 20px 1274px #FFF, 747px 1507px #FFF, 871px 1028px #FFF, 873px 52px #FFF, 258px 1040px #FFF, 157px 330px #FFF, 517px 1747px #FFF, 162px 1116px #FFF, 1856px 1308px #FFF, 691px 1890px #FFF, 376px 1885px #FFF, 1415px 1843px #FFF, 337px 571px #FFF, 221px 1479px #FFF, 1025px 274px #FFF, 485px 1805px #FFF, 505px 1517px #FFF, 1313px 597px #FFF, 1412px 77px #FFF, 447px 1374px #FFF, 461px 1917px #FFF, 23px 934px #FFF, 754px 1701px #FFF, 496px 1834px #FFF, 26px 1850px #FFF, 995px 851px #FFF, 877px 379px #FFF, 281px 1305px #FFF, 592px 847px #FFF, 1735px 1656px #FFF, 608px 764px #FFF, 1537px 50px #FFF, 1591px 141px #FFF, 317px 1977px #FFF, 1177px 1694px #FFF, 207px 227px #FFF, 125px 992px #FFF, 1025px 599px #FFF, 1681px 1110px #FFF, 1531px 288px #FFF, 1408px 1393px #FFF, 426px 1105px #FFF, 656px 1418px #FFF, 957px 1613px #FFF, 1450px 1116px #FFF, 1485px 992px #FFF, 1991px 1401px #FFF, 1595px 1258px #FFF, 473px 1782px #FFF, 605px 263px #FFF, 662px 1215px #FFF, 1127px 1103px #FFF, 684px 1640px #FFF, 401px 1035px #FFF, 933px 1544px #FFF, 1135px 1674px #FFF, 1121px 1587px #FFF, 1319px 1546px #FFF, 827px 724px #FFF, 619px 664px #FFF, 1741px 1834px #FFF, 1033px 1566px #FFF, 1165px 65px #FFF, 856px 1446px #FFF, 308px 1504px #FFF, 907px 1161px #FFF, 1499px 1029px #FFF, 1399px 1240px #FFF, 855px 1109px #FFF, 1400px 1553px #FFF, 1540px 993px #FFF, 1702px 979px #FFF, 412px 1857px #FFF, 45px 1308px #FFF, 1948px 1576px #FFF, 1534px 927px #FFF, 479px 1249px #FFF, 624px 1904px #FFF, 417px 1823px #FFF, 1510px 310px #FFF, 963px 1534px #FFF, 1781px 348px #FFF, 215px 1083px #FFF, 739px 190px #FFF, 1843px 1071px #FFF, 593px 502px #FFF, 1239px 1043px #FFF, 645px 1487px #FFF, 1866px 242px #FFF, 1549px 36px #FFF, 1935px 663px #FFF, 142px 1466px #FFF, 1672px 487px #FFF, 145px 1483px #FFF, 957px 201px #FFF, 459px 855px #FFF, 1773px 988px #FFF, 446px 335px #FFF, 1982px 1239px #FFF, 1519px 1661px #FFF, 594px 424px #FFF, 870px 1800px #FFF, 125px 1136px #FFF, 636px 442px #FFF, 414px 1677px #FFF, 1204px 1588px #FFF, 1587px 1250px #FFF, 796px 507px #FFF, 181px 861px #FFF, 1602px 1106px #FFF, 58px 674px #FFF, 585px 1706px #FFF, 586px 1501px #FFF, 1602px 614px #FFF, 1614px 1179px #FFF, 282px 1907px #FFF, 1689px 348px #FFF, 1033px 302px #FFF, 290px 1260px #FFF, 236px 926px #FFF, 174px 98px #FFF, 1427px 95px #FFF, 22px 1019px #FFF, 275px 1241px #FFF, 1203px 1330px #FFF, 798px 1713px #FFF, 445px 983px #FFF, 805px 1879px #FFF, 672px 973px #FFF, 269px 235px #FFF, 1526px 1791px #FFF, 790px 1860px #FFF, 109px 516px #FFF, 321px 1783px #FFF, 1700px 714px #FFF, 22px 913px #FFF, 1152px 1567px #FFF, 1588px 1367px #FFF, 206px 418px #FFF, 1761px 951px #FFF, 828px 682px #FFF, 1942px 1786px #FFF, 866px 409px #FFF, 1400px 560px #FFF, 1303px 264px #FFF, 1559px 1200px #FFF, 211px 393px #FFF, 1760px 327px #FFF, 559px 1359px #FFF, 1621px 1748px #FFF, 1228px 470px #FFF, 992px 504px #FFF, 50px 781px #FFF, 722px 553px #FFF, 430px 1530px #FFF, 969px 1682px #FFF, 912px 1094px #FFF, 1605px 121px #FFF, 269px 1321px #FFF, 1387px 1504px #FFF, 1809px 1668px #FFF, 1790px 1537px #FFF, 702px 392px #FFF, 1066px 1097px #FFF, 1772px 1632px #FFF, 169px 1237px #FFF, 650px 324px #FFF, 1927px 1938px #FFF, 939px 517px #FFF, 591px 128px #FFF, 1433px 1030px #FFF, 1548px 416px #FFF, 1302px 721px #FFF, 133px 1460px #FFF, 1221px 1954px #FFF, 1957px 340px #FFF, 1080px 1787px #FFF, 1068px 1315px #FFF, 830px 1082px #FFF, 272px 1374px #FFF, 995px 1440px #FFF, 594px 760px #FFF, 1209px 1185px #FFF, 1193px 1340px #FFF, 157px 256px #FFF, 62px 338px #FFF, 1319px 1319px #FFF, 1330px 729px #FFF, 1439px 1589px #FFF, 60px 1410px #FFF, 1205px 690px #FFF, 1493px 1982px #FFF, 1595px 515px #FFF, 1968px 814px #FFF, 1265px 403px #FFF, 572px 1577px #FFF, 806px 112px #FFF, 336px 1414px #FFF, 982px 585px #FFF, 768px 248px #FFF, 1381px 958px #FFF, 585px 560px #FFF, 40px 1193px #FFF, 961px 1316px #FFF, 1795px 498px #FFF, 361px 473px #FFF, 365px 252px #FFF, 1459px 1423px #FFF, 442px 792px #FFF, 1932px 1437px #FFF, 877px 1131px #FFF, 1585px 1717px #FFF, 548px 232px #FFF, 488px 432px #FFF, 1234px 688px #FFF, 250px 1388px #FFF, 167px 1334px #FFF, 793px 777px #FFF, 979px 1802px #FFF, 1328px 1189px #FFF, 1817px 554px #FFF, 637px 543px #FFF, 304px 503px #FFF, 1664px 1112px #FFF, 674px 1529px #FFF, 1761px 1834px #FFF, 1003px 1724px #FFF, 1591px 291px #FFF, 925px 1020px #FFF, 378px 72px #FFF, 1447px 17px #FFF, 797px 1880px #FFF, 1910px 11px #FFF, 1877px 543px #FFF, 1567px 1293px #FFF, 1021px 213px #FFF, 1778px 1923px #FFF, 884px 1392px #FFF, 820px 1005px #FFF, 1492px 662px #FFF, 1741px 1327px #FFF, 1182px 1680px #FFF, 1555px 1065px #FFF, 819px 1438px #FFF, 1953px 995px #FFF, 1918px 48px #FFF, 1307px 1282px #FFF, 989px 605px #FFF, 1829px 880px #FFF, 279px 1559px #FFF, 187px 442px #FFF, 1993px 1598px #FFF, 1393px 1023px #FFF, 218px 1524px #FFF, 445px 1060px #FFF, 1741px 1748px #FFF, 1577px 943px #FFF, 1845px 373px #FFF, 1541px 1069px #FFF, 102px 1906px #FFF, 1851px 1054px #FFF, 1310px 269px #FFF, 1935px 14px #FFF, 876px 695px #FFF, 832px 575px #FFF, 1928px 312px #FFF, 1864px 1684px #FFF, 1369px 923px #FFF, 1840px 1795px #FFF, 136px 1077px #FFF, 1372px 26px #FFF, 386px 492px #FFF, 391px 1128px #FFF, 472px 824px #FFF, 679px 1495px #FFF, 938px 1510px #FFF, 415px 1126px #FFF, 728px 198px #FFF, 1570px 1315px #FFF, 234px 1612px #FFF, 639px 41px #FFF, 1132px 289px #FFF, 347px 800px #FFF, 759px 1595px #FFF, 1224px 374px #FFF, 1px 1769px #FFF, 637px 608px #FFF, 308px 592px #FFF, 1065px 960px #FFF, 794px 1460px #FFF, 1510px 206px #FFF, 1178px 1755px #FFF, 1599px 1956px #FFF, 691px 1131px #FFF, 256px 271px #FFF, 1291px 1522px #FFF, 1048px 1639px #FFF, 964px 976px #FFF, 803px 987px #FFF, 787px 2000px #FFF, 419px 1750px #FFF, 158px 79px #FFF, 759px 1444px #FFF, 1116px 1442px #FFF, 987px 1524px #FFF, 1201px 1358px #FFF, 1622px 275px #FFF, 390px 1284px #FFF, 1623px 598px #FFF, 191px 1296px #FFF, 725px 652px #FFF, 1478px 854px #FFF, 385px 1530px #FFF, 1859px 1135px #FFF, 1760px 1140px #FFF, 1751px 1483px #FFF, 773px 1859px #FFF, 1228px 744px #FFF, 469px 1201px #FFF, 1568px 1475px #FFF, 1329px 1994px #FFF, 768px 1507px #FFF, 1713px 1161px #FFF, 1993px 1294px #FFF, 194px 39px #FFF, 1872px 1371px #FFF, 295px 437px #FFF, 22px 1391px #FFF, 1334px 1846px #FFF, 639px 1876px #FFF, 1939px 1270px #FFF, 811px 1428px #FFF, 1317px 1446px #FFF, 1854px 1342px #FFF, 1681px 1487px #FFF, 1748px 771px #FFF, 1058px 1446px #FFF, 1585px 1908px #FFF, 765px 643px #FFF, 1751px 1176px #FFF, 480px 741px #FFF, 487px 608px #FFF, 684px 900px #FFF, 1866px 583px #FFF, 296px 754px #FFF, 312px 1183px #FFF, 988px 1556px #FFF, 1476px 1985px #FFF, 594px 1200px #FFF, 728px 1542px #FFF, 1314px 331px #FFF, 654px 419px #FFF, 1122px 1623px #FFF, 62px 1154px #FFF, 1556px 1824px #FFF, 218px 31px #FFF, 1701px 18px #FFF, 1672px 1958px #FFF, 376px 1061px #FFF, 1763px 1025px #FFF, 1060px 1218px #FFF, 1839px 1702px #FFF, 22px 904px #FFF, 826px 51px #FFF, 1681px 315px #FFF, 235px 1227px #FFF, 1350px 1219px #FFF, 1610px 548px #FFF, 1002px 211px #FFF, 1626px 693px #FFF, 1757px 205px #FFF, 724px 889px #FFF, 997px 1988px #FFF, 62px 839px #FFF, 505px 1123px #FFF, 1562px 1210px #FFF, 1475px 716px #FFF, 1534px 1110px #FFF, 665px 266px #FFF, 1068px 1063px #FFF, 14px 907px #FFF, 176px 44px #FFF, 1737px 275px #FFF, 1126px 1716px #FFF, 606px 1075px #FFF, 1676px 677px #FFF, 1456px 1934px #FFF, 566px 569px #FFF, 1029px 669px #FFF, 1277px 1220px #FFF, 1662px 508px #FFF, 1355px 1829px #FFF, 1704px 846px #FFF, 1289px 1481px #FFF, 940px 834px #FFF, 556px 162px #FFF, 1347px 1122px #FFF, 410px 627px #FFF, 1693px 420px #FFF, 1008px 1221px #FFF, 218px 1118px #FFF, 1983px 1588px #FFF, 399px 149px #FFF, 94px 1339px #FFF, 1833px 1054px #FFF, 82px 1438px #FFF, 394px 852px #FFF, 1786px 910px #FFF, 1397px 203px #FFF, 1450px 1692px #FFF, 249px 171px #FFF, 1715px 1935px #FFF, 115px 1966px #FFF, 225px 932px #FFF, 1713px 1040px #FFF, 1311px 1409px #FFF, 752px 1894px #FFF, 1042px 361px #FFF, 1032px 768px #FFF, 90px 1095px #FFF, 357px 84px #FFF, 1028px 1051px #FFF, 1794px 1310px #FFF, 1532px 1910px #FFF, 1533px 1680px #FFF, 1892px 1087px #FFF, 521px 133px #FFF, 1936px 1694px #FFF, 646px 287px #FFF, 717px 682px #FFF, 937px 1091px #FFF, 1278px 652px #FFF, 1149px 107px #FFF, 49px 1107px #FFF, 838px 1425px #FFF, 523px 1253px #FFF, 1813px 1747px #FFF, 1575px 1628px #FFF, 1416px 1204px #FFF, 1146px 481px #FFF, 482px 1643px #FFF, 1072px 488px #FFF, 1971px 1889px #FFF, 1626px 1231px #FFF, 569px 713px #FFF, 1769px 1045px #FFF, 803px 1902px #FFF, 1415px 709px #FFF, 977px 265px #FFF, 864px 596px #FFF, 1090px 1019px #FFF, 1095px 1699px #FFF, 331px 1000px #FFF, 1445px 685px #FFF, 353px 583px #FFF, 550px 193px #FFF, 934px 156px #FFF, 721px 1299px #FFF, 817px 1021px #FFF, 560px 623px #FFF, 1618px 1459px #FFF, 284px 1232px #FFF, 1527px 925px #FFF, 1735px 1369px #FFF;
            }

        #stars2 {
            width: 2px;
            height: 2px;
            background: transparent;
            box-shadow: 1073px 887px #FFF, 1669px 1087px #FFF, 13px 1505px #FFF, 254px 1039px #FFF, 1973px 108px #FFF, 1561px 155px #FFF, 1924px 1668px #FFF, 634px 1950px #FFF, 1739px 1693px #FFF, 520px 1457px #FFF, 561px 1053px #FFF, 1060px 1506px #FFF, 1933px 1261px #FFF, 1170px 1379px #FFF, 1896px 714px #FFF, 1453px 375px #FFF, 856px 1137px #FFF, 1351px 1298px #FFF, 187px 462px #FFF, 393px 1979px #FFF, 1406px 544px #FFF, 1651px 1299px #FFF, 1964px 552px #FFF, 834px 79px #FFF, 92px 1675px #FFF, 1703px 856px #FFF, 486px 1949px #FFF, 1418px 1243px #FFF, 1878px 1133px #FFF, 683px 1171px #FFF, 699px 717px #FFF, 242px 1508px #FFF, 293px 784px #FFF, 1055px 1955px #FFF, 394px 1919px #FFF, 370px 1763px #FFF, 1763px 186px #FFF, 728px 1708px #FFF, 1762px 1729px #FFF, 1570px 1321px #FFF, 864px 729px #FFF, 1952px 1256px #FFF, 790px 1281px #FFF, 827px 1078px #FFF, 1932px 156px #FFF, 1346px 154px #FFF, 1534px 1547px #FFF, 1811px 1508px #FFF, 424px 245px #FFF, 398px 1475px #FFF, 1575px 1290px #FFF, 1125px 943px #FFF, 1605px 1258px #FFF, 1266px 334px #FFF, 1098px 346px #FFF, 278px 962px #FFF, 188px 342px #FFF, 1501px 1731px #FFF, 533px 662px #FFF, 192px 460px #FFF, 1639px 1074px #FFF, 1792px 835px #FFF, 1799px 1789px #FFF, 944px 917px #FFF, 1674px 1631px #FFF, 1674px 928px #FFF, 330px 1551px #FFF, 301px 191px #FFF, 490px 1945px #FFF, 1598px 302px #FFF, 262px 1351px #FFF, 686px 763px #FFF, 1773px 736px #FFF, 1422px 608px #FFF, 1676px 1035px #FFF, 233px 888px #FFF, 75px 210px #FFF, 1601px 1068px #FFF, 1547px 1904px #FFF, 693px 636px #FFF, 1777px 751px #FFF, 1437px 466px #FFF, 1885px 530px #FFF, 28px 302px #FFF, 1267px 571px #FFF, 1765px 421px #FFF, 278px 1102px #FFF, 124px 1990px #FFF, 563px 580px #FFF, 1675px 1960px #FFF, 1129px 1755px #FFF, 1569px 1587px #FFF, 1105px 1297px #FFF, 593px 1085px #FFF, 1747px 970px #FFF, 53px 194px #FFF, 720px 1161px #FFF, 1529px 537px #FFF, 753px 1958px #FFF, 1586px 1066px #FFF, 1958px 719px #FFF, 120px 1479px #FFF, 1112px 245px #FFF, 1143px 1033px #FFF, 1881px 940px #FFF, 1290px 820px #FFF, 1092px 175px #FFF, 94px 378px #FFF, 1139px 1817px #FFF, 727px 1551px #FFF, 1158px 1193px #FFF, 1588px 1704px #FFF, 557px 1121px #FFF, 883px 932px #FFF, 494px 1976px #FFF, 765px 592px #FFF, 960px 1422px #FFF, 359px 84px #FFF, 512px 1611px #FFF, 1525px 1562px #FFF, 1369px 1120px #FFF, 1443px 1187px #FFF, 29px 1668px #FFF, 1246px 1821px #FFF, 904px 1763px #FFF, 208px 1477px #FFF, 242px 1644px #FFF, 602px 436px #FFF, 3px 1506px #FFF, 574px 124px #FFF, 397px 755px #FFF, 1570px 1129px #FFF, 1178px 1627px #FFF, 1098px 1222px #FFF, 1817px 1717px #FFF, 755px 15px #FFF, 262px 1105px #FFF, 103px 1828px #FFF, 1361px 1912px #FFF, 1406px 991px #FFF, 1832px 160px #FFF, 1797px 1706px #FFF, 982px 760px #FFF, 1847px 1088px #FFF, 1352px 938px #FFF, 724px 1113px #FFF, 1719px 861px #FFF, 1418px 1883px #FFF, 1820px 538px #FFF, 598px 740px #FFF, 1410px 290px #FFF, 1079px 1284px #FFF, 1380px 1478px #FFF, 1740px 1612px #FFF, 1762px 299px #FFF, 1851px 46px #FFF, 433px 1820px #FFF, 1818px 290px #FFF, 1864px 1212px #FFF, 1601px 666px #FFF, 316px 1924px #FFF, 1871px 720px #FFF, 479px 1179px #FFF, 961px 1052px #FFF, 1929px 1883px #FFF, 1988px 807px #FFF, 1518px 1725px #FFF, 291px 826px #FFF, 31px 1999px #FFF, 1988px 1802px #FFF, 1523px 1465px #FFF, 1633px 525px #FFF, 1234px 1873px #FFF, 1754px 1580px #FFF, 335px 47px #FFF, 818px 129px #FFF, 370px 1082px #FFF, 1134px 1558px #FFF, 1705px 847px #FFF, 826px 577px #FFF, 259px 978px #FFF, 1890px 1344px #FFF, 519px 1147px #FFF, 40px 1290px #FFF, 1106px 846px #FFF, 1661px 480px #FFF, 607px 1484px #FFF, 47px 1381px #FFF, 667px 589px #FFF, 707px 1551px #FFF, 57px 1749px #FFF, 1000px 320px #FFF, 69px 15px #FFF, 1730px 1605px #FFF, 1211px 295px #FFF, 1878px 405px #FFF, 1527px 650px #FFF, 641px 1181px #FFF, 1441px 873px #FFF, 1975px 7px #FFF;
            animation: animStar 100s linear infinite;
        }

            #stars2:after {
                content: " ";
                position: absolute;
                top: 2000px;
                width: 2px;
                height: 2px;
                background: transparent;
                box-shadow: 1073px 887px #FFF, 1669px 1087px #FFF, 13px 1505px #FFF, 254px 1039px #FFF, 1973px 108px #FFF, 1561px 155px #FFF, 1924px 1668px #FFF, 634px 1950px #FFF, 1739px 1693px #FFF, 520px 1457px #FFF, 561px 1053px #FFF, 1060px 1506px #FFF, 1933px 1261px #FFF, 1170px 1379px #FFF, 1896px 714px #FFF, 1453px 375px #FFF, 856px 1137px #FFF, 1351px 1298px #FFF, 187px 462px #FFF, 393px 1979px #FFF, 1406px 544px #FFF, 1651px 1299px #FFF, 1964px 552px #FFF, 834px 79px #FFF, 92px 1675px #FFF, 1703px 856px #FFF, 486px 1949px #FFF, 1418px 1243px #FFF, 1878px 1133px #FFF, 683px 1171px #FFF, 699px 717px #FFF, 242px 1508px #FFF, 293px 784px #FFF, 1055px 1955px #FFF, 394px 1919px #FFF, 370px 1763px #FFF, 1763px 186px #FFF, 728px 1708px #FFF, 1762px 1729px #FFF, 1570px 1321px #FFF, 864px 729px #FFF, 1952px 1256px #FFF, 790px 1281px #FFF, 827px 1078px #FFF, 1932px 156px #FFF, 1346px 154px #FFF, 1534px 1547px #FFF, 1811px 1508px #FFF, 424px 245px #FFF, 398px 1475px #FFF, 1575px 1290px #FFF, 1125px 943px #FFF, 1605px 1258px #FFF, 1266px 334px #FFF, 1098px 346px #FFF, 278px 962px #FFF, 188px 342px #FFF, 1501px 1731px #FFF, 533px 662px #FFF, 192px 460px #FFF, 1639px 1074px #FFF, 1792px 835px #FFF, 1799px 1789px #FFF, 944px 917px #FFF, 1674px 1631px #FFF, 1674px 928px #FFF, 330px 1551px #FFF, 301px 191px #FFF, 490px 1945px #FFF, 1598px 302px #FFF, 262px 1351px #FFF, 686px 763px #FFF, 1773px 736px #FFF, 1422px 608px #FFF, 1676px 1035px #FFF, 233px 888px #FFF, 75px 210px #FFF, 1601px 1068px #FFF, 1547px 1904px #FFF, 693px 636px #FFF, 1777px 751px #FFF, 1437px 466px #FFF, 1885px 530px #FFF, 28px 302px #FFF, 1267px 571px #FFF, 1765px 421px #FFF, 278px 1102px #FFF, 124px 1990px #FFF, 563px 580px #FFF, 1675px 1960px #FFF, 1129px 1755px #FFF, 1569px 1587px #FFF, 1105px 1297px #FFF, 593px 1085px #FFF, 1747px 970px #FFF, 53px 194px #FFF, 720px 1161px #FFF, 1529px 537px #FFF, 753px 1958px #FFF, 1586px 1066px #FFF, 1958px 719px #FFF, 120px 1479px #FFF, 1112px 245px #FFF, 1143px 1033px #FFF, 1881px 940px #FFF, 1290px 820px #FFF, 1092px 175px #FFF, 94px 378px #FFF, 1139px 1817px #FFF, 727px 1551px #FFF, 1158px 1193px #FFF, 1588px 1704px #FFF, 557px 1121px #FFF, 883px 932px #FFF, 494px 1976px #FFF, 765px 592px #FFF, 960px 1422px #FFF, 359px 84px #FFF, 512px 1611px #FFF, 1525px 1562px #FFF, 1369px 1120px #FFF, 1443px 1187px #FFF, 29px 1668px #FFF, 1246px 1821px #FFF, 904px 1763px #FFF, 208px 1477px #FFF, 242px 1644px #FFF, 602px 436px #FFF, 3px 1506px #FFF, 574px 124px #FFF, 397px 755px #FFF, 1570px 1129px #FFF, 1178px 1627px #FFF, 1098px 1222px #FFF, 1817px 1717px #FFF, 755px 15px #FFF, 262px 1105px #FFF, 103px 1828px #FFF, 1361px 1912px #FFF, 1406px 991px #FFF, 1832px 160px #FFF, 1797px 1706px #FFF, 982px 760px #FFF, 1847px 1088px #FFF, 1352px 938px #FFF, 724px 1113px #FFF, 1719px 861px #FFF, 1418px 1883px #FFF, 1820px 538px #FFF, 598px 740px #FFF, 1410px 290px #FFF, 1079px 1284px #FFF, 1380px 1478px #FFF, 1740px 1612px #FFF, 1762px 299px #FFF, 1851px 46px #FFF, 433px 1820px #FFF, 1818px 290px #FFF, 1864px 1212px #FFF, 1601px 666px #FFF, 316px 1924px #FFF, 1871px 720px #FFF, 479px 1179px #FFF, 961px 1052px #FFF, 1929px 1883px #FFF, 1988px 807px #FFF, 1518px 1725px #FFF, 291px 826px #FFF, 31px 1999px #FFF, 1988px 1802px #FFF, 1523px 1465px #FFF, 1633px 525px #FFF, 1234px 1873px #FFF, 1754px 1580px #FFF, 335px 47px #FFF, 818px 129px #FFF, 370px 1082px #FFF, 1134px 1558px #FFF, 1705px 847px #FFF, 826px 577px #FFF, 259px 978px #FFF, 1890px 1344px #FFF, 519px 1147px #FFF, 40px 1290px #FFF, 1106px 846px #FFF, 1661px 480px #FFF, 607px 1484px #FFF, 47px 1381px #FFF, 667px 589px #FFF, 707px 1551px #FFF, 57px 1749px #FFF, 1000px 320px #FFF, 69px 15px #FFF, 1730px 1605px #FFF, 1211px 295px #FFF, 1878px 405px #FFF, 1527px 650px #FFF, 641px 1181px #FFF, 1441px 873px #FFF, 1975px 7px #FFF;
            }

        #stars3 {
            width: 3px;
            height: 3px;
            background: transparent;
            box-shadow: 1919px 1326px #FFF, 906px 627px #FFF, 537px 527px #FFF, 319px 1927px #FFF, 401px 1246px #FFF, 1237px 93px #FFF, 1274px 258px #FFF, 38px 955px #FFF, 83px 833px #FFF, 274px 1967px #FFF, 383px 534px #FFF, 895px 1808px #FFF, 1430px 1616px #FFF, 1278px 451px #FFF, 948px 778px #FFF, 1262px 463px #FFF, 844px 1760px #FFF, 397px 1306px #FFF, 396px 1618px #FFF, 935px 989px #FFF, 428px 990px #FFF, 1772px 215px #FFF, 1775px 1306px #FFF, 452px 527px #FFF, 929px 1761px #FFF, 1795px 1521px #FFF, 1955px 1714px #FFF, 1119px 1839px #FFF, 883px 1381px #FFF, 1462px 440px #FFF, 637px 399px #FFF, 1736px 1023px #FFF, 1684px 1707px #FFF, 961px 136px #FFF, 1896px 861px #FFF, 1346px 542px #FFF, 293px 517px #FFF, 735px 977px #FFF, 975px 494px #FFF, 1862px 16px #FFF, 445px 371px #FFF, 698px 1062px #FFF, 752px 1212px #FFF, 1653px 88px #FFF, 1266px 6px #FFF, 1484px 230px #FFF, 49px 27px #FFF, 1204px 1320px #FFF, 249px 983px #FFF, 125px 134px #FFF, 1997px 498px #FFF, 793px 1676px #FFF, 103px 912px #FFF, 1617px 1672px #FFF, 1908px 46px #FFF, 242px 80px #FFF, 605px 557px #FFF, 1429px 1502px #FFF, 1340px 1279px #FFF, 114px 1961px #FFF, 585px 1120px #FFF, 1884px 1002px #FFF, 24px 1513px #FFF, 1721px 1640px #FFF, 1162px 1703px #FFF, 527px 1259px #FFF, 1731px 1279px #FFF, 1238px 1946px #FFF, 1182px 1221px #FFF, 1459px 518px #FFF, 1662px 1946px #FFF, 702px 999px #FFF, 1949px 1433px #FFF, 1406px 538px #FFF, 1407px 211px #FFF, 190px 572px #FFF, 1884px 96px #FFF, 938px 671px #FFF, 472px 1579px #FFF, 1723px 1635px #FFF, 777px 1903px #FFF, 592px 725px #FFF, 47px 648px #FFF, 1742px 141px #FFF, 264px 214px #FFF, 286px 1975px #FFF, 1053px 441px #FFF, 1940px 1562px #FFF, 186px 1085px #FFF, 197px 230px #FFF, 1035px 1031px #FFF, 775px 210px #FFF, 1996px 1561px #FFF, 1175px 1733px #FFF, 1458px 1858px #FFF, 1812px 1007px #FFF, 1204px 1765px #FFF, 1191px 1461px #FFF, 1515px 257px #FFF, 948px 441px #FFF;
            animation: animStar 150s linear infinite;
        }

            #stars3:after {
                content: " ";
                position: absolute;
                top: 2000px;
                width: 3px;
                height: 3px;
                background: transparent;
                box-shadow: 1919px 1326px #FFF, 906px 627px #FFF, 537px 527px #FFF, 319px 1927px #FFF, 401px 1246px #FFF, 1237px 93px #FFF, 1274px 258px #FFF, 38px 955px #FFF, 83px 833px #FFF, 274px 1967px #FFF, 383px 534px #FFF, 895px 1808px #FFF, 1430px 1616px #FFF, 1278px 451px #FFF, 948px 778px #FFF, 1262px 463px #FFF, 844px 1760px #FFF, 397px 1306px #FFF, 396px 1618px #FFF, 935px 989px #FFF, 428px 990px #FFF, 1772px 215px #FFF, 1775px 1306px #FFF, 452px 527px #FFF, 929px 1761px #FFF, 1795px 1521px #FFF, 1955px 1714px #FFF, 1119px 1839px #FFF, 883px 1381px #FFF, 1462px 440px #FFF, 637px 399px #FFF, 1736px 1023px #FFF, 1684px 1707px #FFF, 961px 136px #FFF, 1896px 861px #FFF, 1346px 542px #FFF, 293px 517px #FFF, 735px 977px #FFF, 975px 494px #FFF, 1862px 16px #FFF, 445px 371px #FFF, 698px 1062px #FFF, 752px 1212px #FFF, 1653px 88px #FFF, 1266px 6px #FFF, 1484px 230px #FFF, 49px 27px #FFF, 1204px 1320px #FFF, 249px 983px #FFF, 125px 134px #FFF, 1997px 498px #FFF, 793px 1676px #FFF, 103px 912px #FFF, 1617px 1672px #FFF, 1908px 46px #FFF, 242px 80px #FFF, 605px 557px #FFF, 1429px 1502px #FFF, 1340px 1279px #FFF, 114px 1961px #FFF, 585px 1120px #FFF, 1884px 1002px #FFF, 24px 1513px #FFF, 1721px 1640px #FFF, 1162px 1703px #FFF, 527px 1259px #FFF, 1731px 1279px #FFF, 1238px 1946px #FFF, 1182px 1221px #FFF, 1459px 518px #FFF, 1662px 1946px #FFF, 702px 999px #FFF, 1949px 1433px #FFF, 1406px 538px #FFF, 1407px 211px #FFF, 190px 572px #FFF, 1884px 96px #FFF, 938px 671px #FFF, 472px 1579px #FFF, 1723px 1635px #FFF, 777px 1903px #FFF, 592px 725px #FFF, 47px 648px #FFF, 1742px 141px #FFF, 264px 214px #FFF, 286px 1975px #FFF, 1053px 441px #FFF, 1940px 1562px #FFF, 186px 1085px #FFF, 197px 230px #FFF, 1035px 1031px #FFF, 775px 210px #FFF, 1996px 1561px #FFF, 1175px 1733px #FFF, 1458px 1858px #FFF, 1812px 1007px #FFF, 1204px 1765px #FFF, 1191px 1461px #FFF, 1515px 257px #FFF, 948px 441px #FFF;
            }

        #title {
            top: 50%;
            left: 0;
            right: 0;
            color: #FFF;
            text-align: center;
            font-family: "lato", sans-serif;
            font-weight: 300;
            font-size: 20px;
            letter-spacing: 10px;
            padding-left: 10px;
        }

            #title span {
                background: -webkit-linear-gradient(white, #38495a);
                -webkit-background-clip: text;
                -webkit-text-fill-color: transparent;
            }

        @keyframes animStar {
            from {
                transform: translateY(0px);
            }

            to {
                transform: translateY(-2000px);
            }
        }
    </style>
</asp:Content>
