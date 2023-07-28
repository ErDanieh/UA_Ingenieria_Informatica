<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="LogReg.aspx.cs" Inherits="WebApplication.LogReg" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <link href="Content/LogReg.css" rel="stylesheet" />

    <div class="containerLogReg">
        <div class="containerLogin">
            <h1>Inicia sesión</h1>
            
            <asp:TextBox ID="emailLogin" type="email" placeholder="Email" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator runat="server" Display="Dynamic" ValidationGroup="loginGroup"
                controltovalidate="emailLogin" errormessage="Por favor introduzca un email" ForeColor="Red"/>
            <asp:regularexpressionvalidator id="revEmailLog" runat="server" Display="Dynamic" 
                ControlToValidate="emailLogin" ForeColor="Red" ErrorMessage="Formato de correo no válido" ValidationExpression="^([\w-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([\w-]+\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\]?)$"/>

            <asp:TextBox ID="passwordLogin" type="password" placeholder="Contraseña" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator runat="server" id="reqPasswordLogin" Display="Dynamic" ValidationGroup="loginGroup"
                controltovalidate="passwordLogin" errormessage="Por favor introduzca contraseña" ForeColor="Red"/>
            <asp:regularexpressionvalidator id="revPasswordLog" runat="server" Display="Dynamic" 
                ControlToValidate="passwordLogin" ForeColor="Red" ErrorMessage="La contraseña es invalida." validationexpression="(?!^[0-9]$)(?!^[a-zA-Z]$)^([a-zA-Z0-9]{8,10})$"/>

            <asp:Button ID="btLogin" OnClick="requestLogin" runat="server" Text="Inicia sesion" />
        </div>

        <div class="containerLogin">
            <h1>Registrate</h1>

            <asp:TextBox ID="nombreApellidos" type="text" placeholder="Nombre" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator runat="server" id="reqNombreApellidosRegister" ValidationGroup="registerGroup"
                controltovalidate="nombreApellidos" errormessage="Por favor introduzca nombre y apellidos" ForeColor="Red"/>

             <asp:TextBox ID="apellidos" type="text" placeholder="Apellidos" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator runat="server" id="RequiredFieldValidator1" ValidationGroup="registerGroup"
                controltovalidate="nombreApellidos" errormessage="Por favor introduzca apellidos" ForeColor="Red"/>

            <asp:TextBox ID="emailReg" type="email" placeholder="Email" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator runat="server" id="reqEmailRegister"  Display="Dynamic" ValidationGroup="registerGroup"
                controltovalidate="emailReg" errormessage="Por favor introduzca un email" ForeColor="Red" />
            <asp:regularexpressionvalidator id="revEmailReg" runat="server" Display="Dynamic" ControlToValidate="emailReg" 
                ForeColor="Red" ErrorMessage="Formato de correo no válido" ValidationExpression="^([\w-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([\w-]+\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\]?)$"/>

            <asp:TextBox ID="passwordReg" type="password" placeholder="Contraseña" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator runat="server" id="reqPasswordRegister" Display="Dynamic"  ValidationGroup="registerGroup"
                controltovalidate="passwordReg" errormessage="Por favor introduzca una contraseña" ForeColor="Red"/>
            <asp:regularexpressionvalidator id="revPasswordReq" runat="server" Display="Dynamic" 
                ControlToValidate="passwordReg" ForeColor="Red" ErrorMessage="La contraseña debe tener 8-10 carácteres y al menos 1 número" validationexpression="(?!^[0-9]$)(?!^[a-zA-Z]$)^([a-zA-Z0-9]{8,10})$"/>

            <asp:TextBox ID="edadRegister" type="number" placeholder="Edad" runat="server"></asp:TextBox>
            <asp:RequiredFieldValidator runat="server" id="reqEdadRegister" Display="Dynamic" ValidationGroup="registerGroup"
                controltovalidate="edadRegister" errormessage="Por favor introduzca una edad" ForeColor="Red"/>
            <asp:RangeValidator ID="rgEdadReg" runat="server" controltovalidate="edadRegister" Display="Dynamic" MaximumValue="99" MinimumValue="16" ErrorMessage="Mayor de 15 años" ForeColor="Red"/>

            <asp:Button ID="btnRegister" OnClick="requestRegister" runat="server" Text="Registrate" />
        </div>
    </div>

    <asp:Label ID="outputMsg" runat="server"></asp:Label>



    <script src="Scripts/LogRegAnimmation.js"></script>



</asp:Content>

