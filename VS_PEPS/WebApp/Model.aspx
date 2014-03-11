<%@ Page Title="PEPS" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
	CodeBehind="Model.aspx.cs" Inherits="WebApp._Default" %>
    <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align:center"> Paramétrage de la simulation </h2>
	
    <ajaxToolkit:ToolkitScriptManager runat="Server" EnablePartialRendering="true" ID="ScriptManager1" />
    <div class="model_indices" style="float:left;width:10%;margin-left:10%;margin-top:5%; padding:0% 15% 10% 10%;border: 1px solid #496077;">
        <p style="float:left;"> Modélisation de l'évolution des indices</p>
        <br></br>
        <ajaxToolkit:ComboBox ID="ComboBox1" runat="server">
            <asp:ListItem Text="Black & Scholes" Value="0" />
            <asp:ListItem Text="Merton" Value="1" />
        </ajaxToolkit:ComboBox>
    </div>
   
    
    <div class="model_changes" style="width:10%;margin-right:10%;margin-top:5%;padding:0% 10% 8% 15%;border: 1px solid #496077;float:right">
        <p> Modélisation du taux de changes</p>
        <br></br>
        <ajaxToolkit:ComboBox ID="ComboBox2" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
    </div>

    <div class="model_taux" style="float:left;width:10%;margin-left:10%;margin-top:3%;padding:0% 15% 10% 10%;border: 1px solid #496077;">
        <p> Modélisation du taux</p>
        <br></br>
        <ajaxToolkit:ComboBox ID="ComboBox3" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
    </div>

    <div class="model_volatilité" style="width:10%;margin-right:10%;margin-top:3%;padding:0% 10% 10% 15%;border: 1px solid #496077;float:right">
        <p> Modélisation de la volatilité</p>
        <br></br>
        <ajaxToolkit:ComboBox ID="ComboBox4" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
    </div>

</asp:Content>
