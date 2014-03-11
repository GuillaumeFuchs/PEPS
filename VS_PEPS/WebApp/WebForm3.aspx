<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="WebForm3.aspx.cs" Inherits="WebApp.WebForm3" %>
  <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align:center"> Tracking des indices </h2>
	
    <ajaxToolkit:ToolkitScriptManager runat="Server" EnablePartialRendering="true" ID="ScriptManager1" />
    <div class="footsie" style="float:left;margin-left:10em;margin-top:5em;border: 1px solid #496077;width:50em;">
        <div id="info" style="float:left;padding-right:10em;">
            <div id="titre" style="float:left;padding:0em 10em 10em 0em;">
                <p>Footsie</p>
            </div>
            <div id="tracking" style="float:none;padding:10em 5em 10em 5em;">
                <asp:Label ID="Label1" runat="server" Text="Tracking error"></asp:Label>
                <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
            </div>
        </div>
        <div id="print_ftse" style="">
            <p>Modélisation du Footsie</p>
          <%--  <asp:Chart ID="Chart1" runat="server">
                <Series>
                    <asp:Series Name="Series1">
                    </asp:Series>
                </Series>
                <ChartAreas>
                    <asp:ChartArea Name="ChartArea1">
                    </asp:ChartArea>
                </ChartAreas>
            </asp:Chart>--%> 
        </div>
    </div>
   
    
    <div class="nikkei" style="width:10%;margin-right:10%;margin-top:5%;padding:0% 10% 10% 15%;border: 1px solid #496077;float:right">
        <p> Nikkei</p>
        <br></br>
    </div>

    <div class="s&p" style="float:left;width:10%;margin-left:10%;margin-top:3%;padding:0% 15% 10% 10%;border: 1px solid #496077;">
        <p>S&P</p>
        <br></br>
        <ajaxToolkit:ComboBox ID="ComboBox3" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
    </div>

    <div class="eurostoxx" style="width:10%;margin-right:10%;margin-top:3%;padding:0% 10% 10% 15%;border: 1px solid #496077;float:right">
        <p>Eurostoxx</p>
        <br></br>
        <ajaxToolkit:ComboBox ID="ComboBox4" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
    </div>

</asp:Content>
