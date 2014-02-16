<%@ Page Title="Page d'accueil" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
    CodeBehind="Default.aspx.cs" Inherits="WebApp._Default" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
    <h2>
        PEPS !
    </h2>

	<p>
	Calcul le prix d'un call européen selon le modèle de B&S avec la valeur simulé avec MC et la valeur théorique selon la formule fermée de B&S.
    </p>
	<p>
	    <asp:TextBox ID="TextBox1" runat="server" Width="40px">t</asp:TextBox>
        <asp:TextBox ID="TextBox2" runat="server" Width="40px">S0</asp:TextBox>
        <asp:TextBox ID="TextBox3" runat="server" Width="40px">K</asp:TextBox>
        <asp:TextBox ID="TextBox4" runat="server" Width="40px">sigma</asp:TextBox>
        <asp:TextBox ID="TextBox5" runat="server" Width="40px">r</asp:TextBox>
        <asp:TextBox ID="TextBox6" runat="server" Width="40px">T</asp:TextBox>
        <asp:TextBox ID="TextBox7" runat="server" Width="40px">N</asp:TextBox>
        <asp:TextBox ID="TextBox8" runat="server" Width="40px">H</asp:TextBox>
        <asp:TextBox ID="TextBox9" runat="server" Width="40px">M</asp:TextBox>
    	<asp:Button ID="Button1" runat="server" onclick="Button1_Click" Text="Compute_price_call" />
		
        <asp:Label ID="Label1" runat="server" Text="prix"></asp:Label>
        <asp:Label ID="Label2" runat="server" Text="largeur ic 95%"></asp:Label>
        <asp:Label ID="Label3" runat="server" Text="prix B&amp;S"></asp:Label>
	</p>
	<p>
		</br>	
	Calcul le delta d'un call européen selon le modèle de B&S avec la valeur simulé avec MC et la valeur théorique selon la formule fermée de B&S.
    </p>
	<p>
	    <asp:TextBox ID="TextBox10" runat="server" Width="40px">t</asp:TextBox>
        <asp:TextBox ID="TextBox11" runat="server" Width="40px">S0</asp:TextBox>
        <asp:TextBox ID="TextBox12" runat="server" Width="40px">K</asp:TextBox>
        <asp:TextBox ID="TextBox13" runat="server" Width="40px">sigma</asp:TextBox>
        <asp:TextBox ID="TextBox14" runat="server" Width="40px">r</asp:TextBox>
        <asp:TextBox ID="TextBox15" runat="server" Width="40px">T</asp:TextBox>
        <asp:TextBox ID="TextBox16" runat="server" Width="40px">N</asp:TextBox>
        <asp:TextBox ID="TextBox17" runat="server" Width="40px">H</asp:TextBox>
        <asp:TextBox ID="TextBox18" runat="server" Width="40px">M</asp:TextBox>
    	<asp:Button ID="Button2" runat="server" onclick="Button2_Click" Text="Compute_delta_call" />
		
        <asp:Label ID="Label4" runat="server" Text="delta"></asp:Label>
        <asp:Label ID="Label5" runat="server" Text="largeur ic 95%"></asp:Label>
        <asp:Label ID="Label6" runat="server" Text="delta B&amp;S"></asp:Label>
	</p>
	
	<p>
		</br>	
	Calcul la variation moyenne entre le prix d'un call européen selon le modèle de B&S avec la valeur simulé avec MC et la valeur théorique selon la formule fermée de B&S avec un échantillon et donne l'écart max.
    </p>
	<p>
        <asp:TextBox ID="TextBox19" runat="server" Width="40px">S0</asp:TextBox>
        <asp:TextBox ID="TextBox20" runat="server" Width="40px">K</asp:TextBox>
        <asp:TextBox ID="TextBox21" runat="server" Width="40px">sigma</asp:TextBox>
        <asp:TextBox ID="TextBox22" runat="server" Width="40px">r</asp:TextBox>
        <asp:TextBox ID="TextBox23" runat="server" Width="40px">T</asp:TextBox>
        <asp:TextBox ID="TextBox24" runat="server" Width="40px">N</asp:TextBox>
        <asp:TextBox ID="TextBox25" runat="server" Width="40px">M</asp:TextBox>
		<asp:TextBox ID="TextBox26" runat="server" Width="40px">samples</asp:TextBox>
    	<asp:Button ID="Button3" runat="server" onclick="Button3_Click" Text="Compute_price_call_samples" />
		
        <asp:Label ID="Label7" runat="server" Text="var"></asp:Label>
        <asp:Label ID="Label8" runat="server" Text="spread max"></asp:Label>
	</p>
	
	<p>
		</br>	
	Calcul la variation moyenne entre le delta d'un call européen selon le modèle de B&S avec la valeur simulé avec MC et la valeur théorique selon la formule fermée de B&S avec un échantillon et donne l'écart max.
    </p>
	<p>
        <asp:TextBox ID="TextBox27" runat="server" Width="40px">S0</asp:TextBox>
        <asp:TextBox ID="TextBox28" runat="server" Width="40px">K</asp:TextBox>
        <asp:TextBox ID="TextBox29" runat="server" Width="40px">sigma</asp:TextBox>
        <asp:TextBox ID="TextBox30" runat="server" Width="40px">r</asp:TextBox>
        <asp:TextBox ID="TextBox31" runat="server" Width="40px">T</asp:TextBox>
        <asp:TextBox ID="TextBox32" runat="server" Width="40px">N</asp:TextBox>
        <asp:TextBox ID="TextBox33" runat="server" Width="40px">M</asp:TextBox>
		<asp:TextBox ID="TextBox34" runat="server" Width="40px">samples</asp:TextBox>
    	<asp:Button ID="Button4" runat="server" onclick="Button4_Click" Text="Compute_delta_call_samples" />
		
        <asp:Label ID="Label9" runat="server" Text="var"></asp:Label>
        <asp:Label ID="Label10" runat="server" Text="spread max"></asp:Label>
	</p>

	<p>
		</br>
		Calcul du portefeuille de couverture d'un call européen selon le modèle de B&S
	</p>
	<p>
	<asp:Button ID="Button5" runat="server" onclick="Button5_Click" Text="Compute_couv" />
	        <asp:Label ID="Label11" runat="server" Text="pl"></asp:Label>
        <asp:Label ID="Label12" runat="server" Text="plt"></asp:Label>
		</p>
</asp:Content>
