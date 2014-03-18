<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="WebForm3.aspx.cs" Inherits="WebApp.WebForm3" %>
  <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align:center"> Tracking des indices </h2>
	
   <ajaxToolkit:ToolkitScriptManager runat="Server" EnablePartialRendering="true" ID="ScriptManager1" />
   <%-- <div class="S&P" style="float:left;width:30%;height:25%;margin-left:10%;margin-top:5%;padding-bottom:5%; padding-left:5%;border: 1px solid #496077;color:Blue;">
        <p> Modélisation de l'évolution des indices</p>
        <br></br>
        <div class="tracking" style="visibility:visible;padding-top:10%">
        <asp:Label ID="tracking" runat="server" Text="tracking"></asp:Label>
        <asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
        </div>
    </div>--%>
   
    
    <div class="Footsie" style="width:30%;height:25%;margin-right:10%;margin-top:2%;padding-bottom:10%;padding-left:5%; color: Blue; border: 1px solid #496077;float:right;">
        <p> Footsie</p>
        <br></br>
        <div class="Footsie" style="padding-left:20%">
        </div>
        <div class="Tracking" style="visibility:visible;padding-top:10%">
        <asp:Label ID="Label4" runat="server" Text="Tracking"></asp:Label>
        <asp:TextBox ID="TextBox5" runat="server"></asp:TextBox>
        </div>
    </div>

    <div class="Nikkei" style="float:left;width:30%;height:25%;margin-left:10%;margin-top:2%;padding-bottom:10%; padding-left:5%;border: 1px solid #496077;color:Blue;">
        <p> Nikkei</p>
        <br></br>
        <div class="Nikkei" style="padding-left:20%">
        </div>
        <div class="Tracking" style="visibility:visible;padding-top:10%">
        <asp:Label ID="Label1" runat="server" Text="Tracking"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
        </div>
    </div>

    <div class="Eurostoxx" style="width:30%;margin-right:10%;margin-top:2%;padding-bottom:10%;padding-left:5%; color: Blue; border: 1px solid #496077;float:right;">
        <p> Eurostoxx</p>
        <br></br>
        <div class="Eurostoxx" style="padding-left:20%">
        </div>
        <div class="Tracking" style="visibility:visible;padding-top:10%">
        <asp:Label ID="Label2" runat="server" Text="Tracking"></asp:Label>
        <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
        </div>
    </div>

    <div class="S&P" style="float:left;width:30%;height:35%;margin-left:10%;margin-top:2%;padding-bottom:10%; padding-left:5%;border: 1px solid #496077;color:Blue;">
        <p>S&P 500</p>
        <br></br>
        <div class="S&P 500" style="padding-left:20%">
        </div>
        <div class="Tracking" style="visibility:visible;padding-top:10%">
        <asp:Label ID="Label3" runat="server" Text="Tracking"></asp:Label>
        <asp:TextBox ID="TextBox4" runat="server"></asp:TextBox>
        </div>
    </div>

</asp:Content>
