<%@ Page Title="PEPS" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
	CodeBehind="Default.aspx.cs" Inherits="WebApp._Default" %>

<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<div style="border-style: solid; padding: 10px">
		<p>
			Calcul du prix d'un call européen selon le modèle de Black & Scholes.
			<br />
			Affiche le prix selon une simulation de Monte-Carlo en considérant la trajectoire
			du sous-jacent selon le modèle de B&S.
			<br />
			Affiche le prix selon la formule théorique de B&S.
			<br />
		</p>
		<div>
			Paramètres donnés:
			<ul>
				<li>SO (prix spot) = 100,0 </li>
				<li>K (strike) = 100,0 </li>
				<li>T (maturité) = 1</li>
				<li>sigma (volatilité) = 20%</li>
				<li>r (taux sans risque) = 0,05%</li>
				<li>M (nombre de simulations de Monte-Carlo) = 50 000</li>
			</ul>
		</div>
		<div>
			Paramètres à déterminer:
			<ul>
				<li>t (temps où calculer le prix du call) à déterminer</li>
				<li>H (nombre de pas de temps utilisé pour simulé le sous-jacent jusqu'à l'instant t) à déterminer</li>
			</ul>
		</div>
		<p>
			<asp:TextBox ID="TextBox1" runat="server" Width="40px">t</asp:TextBox>
			<asp:TextBox ID="TextBox2" runat="server" Width="40px">H</asp:TextBox>
			<asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="Go" />
			<asp:Label ID="Label1" runat="server" Text="Prix simulé" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
			<asp:Label ID="Label2" runat="server" Text="Largeur IC(95%)" BorderStyle="Solid"
				BorderWidth="1px"></asp:Label>
			<asp:Label ID="Label3" runat="server" Text="Prix BS" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
		</p>
	</div>
	<div style="border-style: solid; padding: 10px">
		<p>
			Calcul du delta d'un call européen selon le modèle de Black & Scholes.
			<br />
			Affiche le delta selon une simulation de Monte-Carlo en considérant la trajectoire
			du sous-jacent selon le modèle de B&S.
			<br />
			Affiche le delta selon la formule théorique de B&S.
			<br />
		</p>
		<div>
			Paramètres:
			<ul>
				<li>SO (prix spot) = 100,0 </li>
				<li>K (strike) = 100,0 </li>
				<li>T (maturité) = 1</li>
				<li>sigma (volatilité) = 20%</li>
				<li>r (taux sans risque) = 0,05%</li>
				<li>M (nombre de simulations de Monte-Carlo) = 50 000</li>
				<li>t (temps où calculer le delta du call) à déterminer</li>
				<li>H (nombre de pas de temps utilisé pour simulé le sous-jacent jusqu'à l'instant t)
					à déterminer</li>
			</ul>
		</div>
		<p>
			<asp:TextBox ID="TextBox3" runat="server" Width="40px">t</asp:TextBox>
			<asp:TextBox ID="TextBox4" runat="server" Width="40px">H</asp:TextBox>
			<asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="Go" />
			<asp:Label ID="Label4" runat="server" Text="Delta" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
			<asp:Label ID="Label5" runat="server" Text="Largeur IC(95%)" BorderStyle="Solid"
				BorderWidth="1px"></asp:Label>
			<asp:Label ID="Label6" runat="server" Text="Delta BS" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
		</p>
	</div>
	<div style="border-style: solid; padding: 10px">
		<p>
			Calcul la variation moyenne entre le prix d'un call européen selon le modèle de
			B&S avec la valeur simulé avec MC et la valeur théorique selon la formule fermée
			de B&S à partir d'un échantillon de taille samples et donne l'écart max. Les différents
			temps où sont calculés les deltas sont aléatoires.
		</p>
		<div>
			Paramètres:
			<ul>
				<li>SO (prix spot) = 100,0 </li>
				<li>K (strike) = 100,0 </li>
				<li>T (maturité) = 1</li>
				<li>sigma (volatilité) = 20%</li>
				<li>r (taux sans risque) = 0,05%</li>
				<li>M (nombre de simulations de Monte-Carlo) = 50 000</li>
				<li>samples (nombre de simulations) à déterminer</li>
			</ul>
		</div>
		<p>
			<asp:TextBox ID="TextBox5" runat="server" Width="40px">samples</asp:TextBox>
			<asp:Button ID="Button3" runat="server" OnClick="Button3_Click" Text="Go" />
			<asp:Label ID="Label7" runat="server" Text="Variation moyenne" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
			<asp:Label ID="Label8" runat="server" Text="Spread max" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
		</p>
	</div>
	<div style="border-style: solid; padding: 10px">
		<p>
			Calcul la variation moyenne entre le delta d'un call européen selon le modèle de
			B&S avec la valeur simulé avec MC et la valeur théorique selon la formule fermée
			de B&S à partir d'un échantillon de taille samples et donne l'écart max. Les différents
			temps où sont calculés les deltas sont aléatoires.
		</p>
		<div>
			Paramètres:
			<ul>
				<li>SO (prix spot) = 100,0 </li>
				<li>K (strike) = 100,0 </li>
				<li>T (maturité) = 1</li>
				<li>sigma (volatilité) = 20%</li>
				<li>r (taux sans risque) = 0,05%</li>
				<li>M (nombre de simulations de Monte-Carlo) = 50 000</li>
				<li>samples (nombre de simulations) à déterminer</li>
			</ul>
		</div>
		<p>
			<asp:TextBox ID="TextBox6" runat="server" Width="40px">samples</asp:TextBox>
			<asp:Button ID="Button4" runat="server" OnClick="Button4_Click" Text="Go" />
			<asp:Label ID="Label9" runat="server" Text="Variation moyenne" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
			<asp:Label ID="Label10" runat="server" Text="Spread max" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
		</p>
	</div>
	
</asp:Content>
