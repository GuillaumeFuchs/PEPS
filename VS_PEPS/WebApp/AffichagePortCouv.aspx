<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="AffichagePortCouv.aspx.cs" Inherits="WebApp.AffichagePortCouv" %>

    <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
<script type="text/javascript" src="https://www.google.com/jsapi"></script>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.0/jquery.min.js"></script>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/jquery-ui.min.js"></script>
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">


	<h2 style="text-align:center"> Affichage du portefeuille de couverture </h2>
    
    
       <div id="Affichage"  runat="server" Height="1000px" Width="1200px" style="display:none;">
	    <asp:Chart ID="Chart1" runat="server" Height="800px" Width="1000px" style="margin-left:20%;">
			<Series>
				<asp:Series ChartType="Line" Name="1">
				</asp:Series>
                <asp:Series ChartType="Line" Name="2">
				</asp:Series>
                <asp:Series ChartType="Line" Name="3">
				</asp:Series>
                <asp:Series ChartType="Line" Name="4">
				</asp:Series>
			</Series>
			<ChartAreas>
				<asp:ChartArea Name="ChartArea1">
					<AxisX Title="Temps">
					</AxisX>
					<AxisY Title="Composition du portefeuille">
					</AxisY>
				</asp:ChartArea>
			</ChartAreas>
		</asp:Chart>
	    </div>
    

       
   
</asp:Content>

