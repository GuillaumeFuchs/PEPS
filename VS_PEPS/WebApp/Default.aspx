<%@ Page Title="Page d'accueil" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
    CodeBehind="Default.aspx.cs" Inherits="WebApp._Default" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
    <h2>
        Bienvenue dans ASP.NET!
    </h2>
    <p>
        Pour en savoir plus sur ASP.NET, consultez <a href="http://www.asp.net" title="Site Web ASP.NET">www.asp.net</a>.
    </p>
    <p>
        Vous pouvez également trouver de la <a href="http://go.microsoft.com/fwlink/?LinkID=152368"
            title="Documentation ASP.NET sur MSDN">documentation sur ASP.NET sur MSDN</a>.</p>
	<p>
        &nbsp;<asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox4" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox5" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox6" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox7" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox8" runat="server"></asp:TextBox>
    </p>
	<p>
        <asp:TextBox ID="TextBox9" runat="server"></asp:TextBox>
    	<asp:Button ID="Button1" runat="server" onclick="Button1_Click" Text="Button" />
    </p>
	<p>
        <asp:Label ID="Label1" runat="server" Text="prix"></asp:Label>
    </p>
	<p>
        <asp:Label ID="Label2" runat="server" Text="ic"></asp:Label>
    </p>
	<p>
        <asp:Label ID="Label3" runat="server" Text="prix B&amp;S"></asp:Label>
    </p>
</asp:Content>
