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
        <div class="bloc1" style="float:left;clear:none;">


             <p>
                    Volatilité des différents indices sur la période considérée 
            </p>
            <ul>
                
                <p>
                <asp:Label ID="Label10" runat="server" Text="Eurostoxx" Width="130px"></asp:Label>
                <asp:Label ID="Label1" runat="server" Width ="60px">0</asp:Label>
                </p>
                <p>
                <asp:Label ID="Label12" runat="server" Text="Footsie" Width ="130px"></asp:Label>
			    <asp:Label ID="Label2" runat="server" Width="60px">0</asp:Label>
                </p>
                <p>
                <asp:Label ID="Label14" runat="server" Text="Nikkei" Width ="130px"></asp:Label>
			    <asp:Label ID="Label4" runat="server" Width="60px">0</asp:Label>
                </p>
                <p>
                <asp:Label ID="Label15" runat="server" Text="S&P 500" Width ="130px"></asp:Label>
			    <asp:Label ID="Label5" runat="server" Width="260px">0</asp:Label>
			    </p>
            </ul>


            
	</div>

    <div class="bloc2" style="padding-top:5px;">
            <p>
                    Correlation entre les différents indices sur la période considérée 
            </p>
            <ul>
                <p style="padding-left:10px;">
                 <asp:Table ID="Table1" runat="server" CellPadding="5" GridLines="Both">
                <asp:TableRow>
                     <asp:TableCell></asp:TableCell>
                     <asp:TableCell>Eurostoxx</asp:TableCell>
                     <asp:TableCell>Footsie</asp:TableCell>
                     <asp:TableCell>Nikkei</asp:TableCell>
                     <asp:TableCell>S&P 500</asp:TableCell>
               </asp:TableRow>
               <asp:TableRow>
                    <asp:TableCell>Eurostoxx</asp:TableCell>
                    <asp:TableCell>1</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>0</asp:Label></asp:TableCell>
               </asp:TableRow>
               <asp:TableRow>
                    <asp:TableCell>Footsie</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>1</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
               </asp:TableRow>
               <asp:TableRow>
                    <asp:TableCell>Nikkei</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>1</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
               </asp:TableRow>
               <asp:TableRow>
                    <asp:TableCell>S&P 500</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>0</asp:TableCell>
                    <asp:TableCell>1</asp:TableCell>
               </asp:TableRow>
            </asp:Table>
            </p>
            </ul>
    </div>
</asp:Content>
