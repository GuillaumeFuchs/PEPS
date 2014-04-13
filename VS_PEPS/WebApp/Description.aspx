<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Description.aspx.cs" Inherits="WebApp.WebForm6" %>
    <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.0/jquery.min.js"></script>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/jquery-ui.min.js"></script>

	<h2 style="text-align:center; padding-top:20px;"> Informations générales sur Playlist 2 </h2>

    <div class="champ" style="width:80%; height:600px; border:1px dashed black;margin: 30px 10% 0px 10%;">

        <div class="ligne1" style="padding:70px 100px 100px 100px;">
            <asp:Label ID="Label1" runat="server" Text="Date initiale" style="margin-left: 200px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>29/04/2009
            <asp:Label ID="Label2" runat="server" Text="Date actuelle" style="margin-left: 100px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>08/04/2014
            <asp:Label ID="Label3" runat="server" Text="Date d'échéance actuelle" style="margin-left: 100px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>24/05/2015
        </div>
        <div class="ligne2" style="padding:0px 100px 100px 100px;">
            <asp:Label ID="Label4" runat="server" Text="Nombre de parts total" style="margin-left: 200px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>1 000 000
            <asp:Label ID="Label5" runat="server" Text="Valeur associée" style="margin-left: 100px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>150 000 000
        </div>
        <div class="ligne3" style="padding:0px 100px 100px 100px;">
            <asp:Label ID="Label6" runat="server" Text="Nombre de parts achetées" style="margin-left: 200px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>500 000
            <asp:Label ID="Label7" runat="server" Text="Valeur associée" style="margin-left: 100px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>75 000 000
        </div>
        <div class="ligne4">
            <asp:Label ID="Label8" runat="server" Text="Ratio du nombre de parts détenus" style="margin-left: 300px;border: 1px solid black;margin-right: 30px;padding: 5px 5px 3px 5px;"></asp:Label>50%
        </div>
    
    </div>
</asp:Content>