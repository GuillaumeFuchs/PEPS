<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="WebForm4.aspx.cs" Inherits="WebApp.WebForm4" %>
  <%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">

</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align:center"> Affichage des cours </h2>


    <div class="but" id="simulation" style="width:200px;height:300px;margin-top:100px;margin-left:150px;margin-right:150px; float:left;" runat="server">
            <%--<asp:Button ID="Button1" CssClass="run" runat="server" Text="Affiche" onclick="Simulate" />--%>
            <asp:Button ID="first" runat="server" onclick="Simulate" style="margin-bottom:20px;" Text="Footsie" />
            <asp:Button ID="second"  onclick="Simulate" runat="server" style="margin-bottom:20px;" Text="S&P 500" />
            <asp:Button ID="third"  onclick="Simulate" runat="server" style="margin-bottom:20px;" Text="Nikkei" />
            <asp:Button ID="fourth"  onclick="Simulate" runat="server" style="margin-bottom:20px;" Text="Eurostoxx" />
   </div>
	<div id="Asset"  runat="server" Height="600px" Width="800px" style="display:none;">
	<asp:Chart ID="Chart1" runat="server" Height="400px" Width="600px" style="float:left; margin-top:60px;margin-left:60px;">
			<Series>
				<asp:Series ChartType="Line">
				</asp:Series>
			</Series>
			<ChartAreas>
				<asp:ChartArea Name="ChartArea1">
					<AxisX Title="Temps">
					</AxisX>
					<AxisY Title="Cours">
					</AxisY>
				</asp:ChartArea>
			</ChartAreas>
		</asp:Chart>
        <div class="Perf"  style="float:left; margin-top:150px;">
        <p> Performance </p>
        <asp:TextBox ID="Perf_Asset" runat="server"></asp:TextBox>
        </div>
	</div>
    <%--<div id="Ftse" style="display:none;" runat="server">
	<asp:Chart ID="Chart2" runat="server" Height="400px" Width="600px" style="margin-top:60px;">
			<Series>
				<asp:Series ChartType="Line">
				</asp:Series>
			</Series>
			<ChartAreas>
				<asp:ChartArea Name="ChartArea2">
					<AxisX Title="Temps">
					</AxisX>
					<AxisY Title="Cours">
					</AxisY>
				</asp:ChartArea>
			</ChartAreas>
		</asp:Chart>
        <div class="foot"  style="float:right; margin-top:150px;margin-right:120px;">
        <p> Performance Footsie</p>
        <asp:TextBox ID="Perf_Footsie" runat="server"></asp:TextBox>
        </div>
	</div>

    <div id="N225" style="display:none;" runat="server">
	<asp:Chart ID="Chart3" runat="server" Height="400px" Width="600px" style="float:left; margin-top:60px;margin-left:60px;">
			<Series>
				<asp:Series ChartType="Line">
				</asp:Series>
			</Series>
			<ChartAreas>
				<asp:ChartArea Name="ChartArea3">
					<AxisX Title="Temps">
					</AxisX>
					<AxisY Title="Cours">
					</AxisY>
				</asp:ChartArea>
			</ChartAreas>
		</asp:Chart>
        <div class="Nik"  style="float:left; margin-top:150px;">
        <p> Performance Nikkei</p>
        <asp:TextBox ID="Perf_Nikkei" runat="server"></asp:TextBox>
        </div>
	</div>
    <div id="SP" style="display:none;" runat="server" Height="600px" Width="800px">
	<asp:Chart ID="Chart4" runat="server" Height="400px" Width="600px" style="margin-top:60px;">
			<Series>
				<asp:Series ChartType="Line">
				</asp:Series>
			</Series>
			<ChartAreas>
				<asp:ChartArea Name="ChartArea4">
					<AxisX Title="Temps">
					</AxisX>
					<AxisY Title="Cours">
					</AxisY>
				</asp:ChartArea>
			</ChartAreas>
		</asp:Chart>
        <div class="foot"  style="float:right; margin-top:150px;margin-right:120px;">
        <p> Performance S&P 500</p>
        <asp:TextBox ID="Perf_SP" runat="server"></asp:TextBox>
        </div>
	</div>--%>
    </asp:Content>