<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true"
	CodeBehind="Couverture.aspx.cs" Inherits="WebApp.WebForm1" %>

<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align: center">
		Affichage du portefeuille de couverture
	</h2>
    <div style="height: 30px">
                    <div style="float:left;width:20%;font-weight:bold">Nombre de rebalancement:</div>
                    <div id="slider1" style="float:left;width:70%;position:relative;top:5px"></div>
                    <asp:HiddenField ID="hidden_estimate" runat="server" />
                    <asp:TextBox ID="estimate_time" style="float:left;width: 35px;border:0; color: #f6931f; font-weight: bold; margin-left:5px;" runat="server">300</asp:TextBox>
    </div>
	<div id="Affichage" runat="server" height="1000px" width="1200px" ><%--style="display: none;">--%>
		<table>
			<tr>
				<td>
					<asp:Chart ID="Chart1" runat="server" Height="400px" Width="500px" Style="margin-left: 20%;"
						EnableViewState="true">
						<Series>
							<asp:Series ChartType="Line" Name="1">
							</asp:Series>
							<asp:Series ChartType="Line" Name="2">
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
				</td>
				<td>
					<asp:Chart ID="Chart2" runat="server" Height="400px" Width="500px" Style="margin-left: 20%;"
						EnableViewState="true">
						<Titles>
							<asp:Title Text="Couverture">
							</asp:Title>
						</Titles>
						<Series>
							<asp:Series ChartType="Line" Name="1">
							</asp:Series>
							<asp:Series ChartType="Line" Name="2">
							</asp:Series>
						</Series>
						<ChartAreas>
							<asp:ChartArea Name="ChartArea1">
								<AxisX Title="Temps">
								</AxisX>
								<AxisY Title="Value">
								</AxisY>
							</asp:ChartArea>
						</ChartAreas>
					</asp:Chart>
				</td>
			</tr>
			<tr>
				<td colspan="2">
					<asp:Chart ID="Chart3" runat="server" Height="400px" Width="500px" Style="margin-left: 20%;"
						EnableViewState="true">
						<Titles>
							<asp:Title Text="Couverture">
							</asp:Title>
						</Titles>
						<Series>
							<asp:Series ChartType="Line" Name="1">
							</asp:Series>
						</Series>
						<ChartAreas>
							<asp:ChartArea Name="ChartArea1">
								<AxisX Title="Temps">
								</AxisX>
								<AxisY Title="Value">
								</AxisY>
							</asp:ChartArea>
						</ChartAreas>
					</asp:Chart>
				</td>
			</tr>
		</table>
	</div>
	<div id="Portfolio_computation" runat="server">
		<asp:Button ID="Start" runat="server" Text="Start" OnClick="Start_Click" />
		<asp:Button ID="Next_day" runat="server" Text="" OnClick="Next_day_Click" Visible="false" />
		<div>
			Portefeuille:
			<asp:Label ID="Portfolio_value" runat="server" Text=""></asp:Label>
		</div>
		<div>
			Produit:
			<asp:Label ID="Product_value" runat="server" Text=""></asp:Label>
		</div>
		<div>
			Erreur de couverture:
			<asp:Label ID="Err_value" runat="server" Text=""></asp:Label>
		</div>
		<asp:Label ID="Label1" runat="server" Text=""></asp:Label>
		<asp:Label ID="Label2" runat="server" Text=""></asp:Label>
		<asp:Label ID="Label3" runat="server" Text=""></asp:Label>
		<asp:Label ID="Label4" runat="server" Text=""></asp:Label>
	</div>
</asp:Content>