<%@ Page Title="PEPS" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
    CodeBehind="About.aspx.cs" Inherits="WebApp.About" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
    	<h2>
			Volatilités historiques et corrélations historiques
		</h2>

        <div>
            <p>
                Nombre de jour à partir desquelles on calcule les volatilités et corrélations
            </p>
            <p>
			    <asp:Label ID="Label3" runat="server" Text="Période considérée"></asp:Label>
                <asp:TextBox ID="TextBox1" runat="server" Width="40px">0</asp:TextBox>
                <asp:Button ID="Button2" runat="server" Onclick="Compute_Volat"  Text="Calcul volatilité" />
		    </p>
        </div>
        <div>


             <p>
                    Volatilité des différents indices sur la période considérée 
            </p>
            <ul>
                
                <p>
                <asp:Label ID="Label10" runat="server" Text="Eurostoxx" Width="80px"></asp:Label>
                <asp:Label ID="Label1" runat="server" Width ="60px">0</asp:Label>
                </p>
                <p>
                <asp:Label ID="Label12" runat="server" Text="Footsie" Width ="80px"></asp:Label>
			    <asp:Label ID="Label2" runat="server" Width="60px">0</asp:Label>
                </p>
                <p>
                <asp:Label ID="Label14" runat="server" Text="Nikkei" Width ="80px"></asp:Label>
			    <asp:Label ID="Label4" runat="server" Width="60px">0</asp:Label>
                </p>
                <p>
                <asp:Label ID="Label15" runat="server" Text="S&P 500" Width ="80px"></asp:Label>
			    <asp:Label ID="Label5" runat="server" Width="460px">0</asp:Label>
			    </p>
            </ul>
            
	</div>
</asp:Content>
