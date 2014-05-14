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
		<table style="float:left;">
			<tr>
				<td>
					<asp:Chart ID="Chart1" runat="server" Height="600px" Width="800px" Style="margin-left: 20%;"
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
					        <AxisY Title="Composition du portefeuille" Maximum="180" Minimum="100">
                                <MajorGrid Interval="Auto" />
                                <ScaleView Size="NotSet" />
					        </AxisY>
				        </asp:ChartArea>
			            </ChartAreas>
					</asp:Chart>
				</td>
			</tr>
		</table>
        <asp:Chart ID="Chart4" runat="server" Width="400px" style="display:inline;margin-left:200px;">
            <Series>
                <asp:Series Name="Parts" XValueMember="Indices" YValueMembers="Parts" 
                    IsVisibleInLegend="true" IsValueShownAsLabel="true" ChartType="Pie" ToolTip="Pourcentage des actifs risqués #PERCENT">
                </asp:Series>
            </Series>
            <ChartAreas>
                <asp:ChartArea Name="ChartArea1" Area3DStyle-Enable3D="true">
                    <AxisX LineColor="DarkGray">
                        <MajorGrid LineColor="LightGray" />
                    </AxisX>
                    <AxisY LineColor="DarkGray">
                        <MajorGrid LineColor="LightGray" />
                    </AxisY>  
                    <Area3DStyle Enable3D="True"></Area3DStyle>
                </asp:ChartArea>
            </ChartAreas>
            <Legends>
                <asp:Legend>
                </asp:Legend>
            </Legends>
        </asp:Chart>
        <asp:Chart ID="Chart6" runat="server" Width="800px">
            <Series>
                <asp:Series Name="FTSE 100" ChartType="StackedColumn100" XValueMember="date" 
                    YValueMembers="Column1" Color="Cyan" IsVisibleInLegend="true" ToolTip="Le #VALX, le FTSE réprésentait #PERCENT{P} du portefeuille risqué" >
                </asp:Series>
                <asp:Series Name="S&P 500" ChartType="StackedColumn100" XValueMember="date" 
                    YValueMembers="Column2" Color="Orange" IsVisibleInLegend="true" ToolTip="Le #VALX, le S&P réprésentait #PERCENT du portefeuille risqué">
                </asp:Series>
                <asp:Series Name="NIKKEI 225" ChartType="StackedColumn100" XValueMember="date" 
                    YValueMembers="Column3" Color ="Red" IsVisibleInLegend="true" ToolTip="Le #VALX, le NIKKEI réprésentait #PERCENT du portefeuille risqué">
                </asp:Series>
                <asp:Series Name="EUROSTOXX 50" ChartType="StackedColumn100" XValueMember="date" 
                    YValueMembers="Column4" Color="DarkBlue" ToolTip="Le #VALX, l'EUROSTOXX réprésentait #PERCENT du portefeuille risqué">
                </asp:Series>
            </Series>
            <ChartAreas>
                <asp:ChartArea Name="ChartArea1" Area3DStyle-Enable3D="true">
             <AxisY>
                 <MajorGrid LineColor="LightGray" />
             </AxisY>
             <AxisX>
                 <MajorGrid LineColor="LightGray" />
             </AxisX>
             <Area3DStyle Enable3D="True"></Area3DStyle>
         </asp:ChartArea>
            </ChartAreas>
            <Legends>
                <asp:Legend>
                </asp:Legend>
            </Legends>
        </asp:Chart>
	</div>
     <div>
        
    </div>
    



        


	<%--<div id="Portfolio_computation" runat="server">
		<asp:Button ID="Start" runat="server" Text="Start" OnClick="Start_Click" />
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
	</div>--%>
</asp:Content>