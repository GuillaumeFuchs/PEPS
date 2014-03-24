<%@ Page Title="PEPS" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
	CodeBehind="Model.aspx.cs" Inherits="WebApp._Default" %>
    <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.0/jquery.min.js"></script>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/jquery-ui.min.js"></script>

	<h2 style="text-align:center"> Paramétrage de la simulation </h2>

    <ajaxToolkit:ToolkitScriptManager runat="Server" EnablePartialRendering="true" ID="ScriptManager1" />
    <div class="model_indices" style="float:left;width:30%;height:25%;margin-left:10%;margin-top:5%;padding-bottom:5%; padding-left:5%;border: 1px solid #496077;color:Blue;">
        <p> Modélisation de l'évolution des indices</p>
        <br></br>
        <div class="model" style="padding-left:20%">
        <asp:DropDownList ID="ComboBox1" runat="server" AutoPostBack="true">
            <asp:ListItem Text="Black & Scholes" Value="0" />
            <asp:ListItem Text="Merton" Value="1"/>
        </asp:DropDownList>
        </div>
        <div class="param1" style="visibility:hidden;padding-top:10%">
        <p><asp:Label ID="Label2" runat="server" Text="r"></asp:Label>
        <asp:TextBox ID="TextBox2" runat="server"></asp:TextBox></p>
        <p><asp:Label ID="Label3" runat="server" Text="spot"></asp:Label>
        <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox></p>
        </div>
    </div>
   
    
    <div class="model_changes" style="width:30%;height:25%;margin-right:10%;margin-top:5%;padding-bottom:5%;padding-left:5%; color: Blue; border: 1px solid #496077;float:right;">
        <p> Modélisation du taux de changes</p>
        <br></br>
        <div class="model_ch" style="padding-left:20%">
        <ajaxToolkit:ComboBox ID="ComboBox2" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
        </div>
        <div class="param1" style="visibility:hidden;padding-top:10%">
        <asp:Label ID="Label1" runat="server" Text="Label"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
        </div>
    </div>

    <div class="model_taux" style="float:left;width:30%;height:35%;margin-left:10%;margin-top:2%;padding-bottom:10%; padding-left:5%;border: 1px solid #496077;color:Blue;">
        <p> Modélisation du taux</p>
        <br></br>
        <div class="model_ta" style="padding-left:20%">
        <ajaxToolkit:ComboBox ID="ComboBox3" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
        </div>
    </div>

    <div class="model_volatilité" style="width:30%;margin-right:10%;margin-top:2%;padding-bottom:10%;padding-left:5%; color: Blue; border: 1px solid #496077;float:right;">
        <p> Modélisation de la volatilité</p>
        <br></br>
        <div class="model_vol" style="padding-left:20%">
        <ajaxToolkit:ComboBox ID="ComboBox4" runat="server">
            <asp:ListItem Text="Constant" Value="0" />
        </ajaxToolkit:ComboBox>
        </div>
        <div class="param1" style="visibility:hidden;padding-top:10%">
        <asp:Label ID="Label4" runat="server" Text="Volatilité"></asp:Label>
        <asp:TextBox ID="TextBox4" runat="server"></asp:TextBox>
        </div>
    </div>

    <script type="text/javascript">
        function ajout_param() {
            if ($(".param1").css('visibility') == 'hidden' && $("#<%=div_parameters.ClientID%>") {
                $(".param1").css('visibility', 'visible');
            }else{
        }
    </script>

</asp:Content>
