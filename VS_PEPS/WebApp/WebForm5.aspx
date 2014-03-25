<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="WebForm5.aspx.cs" Inherits="WebApp.WebForm5" %>
  <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align:center"> Portefeuille de Couverture </h2>

    <div class="Couv" style="width:50%;height:500px;margin-left:25%;margin-top:5%;text-align:center;border:1px solid #496077;">
        <h3> Composition réelle du portefeuille</h3>
        <br />
        <div="Compo_SP" style="padding-bottom:5%;text-align:center;">
        <p>
            <asp:Label ID="Label1" runat="server" Text="S&P"></asp:Label>
            <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
            </p>
            <br />
        <//div>
        <div="Compo_Ftse" style="margin-top:80px;">
        <p>    <asp:Label ID="Label2" runat="server" Text="Footsie"></asp:Label>
            <asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
            </p>

            <br />
        <div="Compo_Euro">
        <p>
            <asp:Label ID="Label3" runat="server" Text="Eurostoxx"></asp:Label>
            <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
            </p>
            <br />
        <div="Compo_Nikkei">
            <p>
            <asp:Label ID="Label4" runat="server" Text="Nikkei"></asp:Label>
            <asp:TextBox ID="TextBox4" runat="server"></asp:TextBox>
            </p>
            <br />
            <asp:Button ID="Button1" runat="server" Text="Enregistrer la composition" OnClick="Enregistrer" />
        
    </div>

</asp:Content>
