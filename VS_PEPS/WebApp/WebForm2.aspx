<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="WebForm2.aspx.cs" Inherits="WebApp.WebForm2" %>
<%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align:center"> Paramétrage du Backtest </h2>
	
    <ajaxToolkit:ToolkitScriptManager runat="Server" EnablePartialRendering="true" ID="ScriptManager1" />
    <div class="model_indices" style="float:left;width:20%;margin-left:35%;margin-top:5%; padding:0% 10% 13% 10%;border: 1px solid #496077;">
        <p style="float:left;"> Paramétrage</p>
        <br/>
        <br/>
        <p>
        <asp:Label ID="Label1" runat="server" Text="Date de départ"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
        <cc1:CalendarExtender ID="CalendarExtender1" runat="server" CssClass="yui" Enabled="true" TargetControlID="TextBox1" StartDate="04/25/2009">
    </cc1:CalendarExtender>
    <br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
    <p>
    <asp:Label ID="Label2" runat="server" Text="Fenêtre d'estimation (jour)"></asp:Label>
        <asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
    </p>
    <p>
    <asp:Label ID="Label3" runat="server" Text="Fenêtre de valisation (jour)"></asp:Label>
        <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
    </p>
    </div>
    
</asp:Content>

