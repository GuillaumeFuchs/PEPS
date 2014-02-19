<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true"
	CodeBehind="Couverture.aspx.cs" Inherits="WebApp.WebForm1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
	<div style="border-style: solid; padding: 10px">
		<p>
			Calcul du portefeuille de couverture d'un call européen selon le modèle de B&S
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
				<li>H (nombre de date de rebalancement) à déterminer (multiple de 10)</li>
			</ul>
		</div>
		<p>
			<asp:TextBox ID="TextBox7" runat="server" Width="40px">H</asp:TextBox>
			<asp:Button ID="Button5" runat="server" OnClick="Button5_Click" Text="Go" />
			<asp:Label ID="Label11" runat="server" Text="P&L" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
			<asp:Label ID="Label12" runat="server" Text="P&L théorique" BorderStyle="Solid" BorderWidth="1px"></asp:Label>
	</div>
	<div>
		<div style="float: left; overflow-y: scroll; height: 600px">
			<asp:Table ID="Table1" runat="server" Height="50px" Width="62px" CellPadding="5"
				GridLines="Both">
			</asp:Table>
		</div>
		<div style="float: right">
			<asp:Chart ID="Chart1" runat="server" Height="600px" Width="500px">
				<Series>
					<asp:Series ChartType="Line">
					</asp:Series>
				</Series>
				<ChartAreas>
					<asp:ChartArea Name="ChartArea1">
						<AxisX Title="Temps">
						</AxisX>
						<AxisY Title="Nb d'actions à posséder">
						</AxisY>
					</asp:ChartArea>
				</ChartAreas>
			</asp:Chart>
		</div>
	</div>
</asp:Content>
