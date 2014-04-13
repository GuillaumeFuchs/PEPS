<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="test.aspx.cs" Inherits="WebApp.WebForm7" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
<link rel="Stylesheet" type="text/css" href="styles/style.css"></link>
    <script src="http://ajax.microsoft.com/ajax/jquery/jquery-1.4.2.min.js" type="text/javascript"></script>
    <script type="text/javascript" src="scripts/jquery.datepick.js"></script>
    <script type="text/javascript">
        $(function () {
            $('#startdate').datepick({ dateFormat: 'dd/mm/yyyy' });
            $('#enddate').datepick({ dateFormat: 'dd/mm/yyyy' });
        });    
    </script>
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
    <div id="content">
        From <asp:TextBox ID="startdate" class="field" runat="server"></asp:TextBox> -
        To <asp:TextBox ID="enddate" class="field" runat="server"></asp:TextBox>
    </div>
</asp:Content>
