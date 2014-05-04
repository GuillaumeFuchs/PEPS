<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="~/ParamBacktest.aspx.cs" Inherits="WebApp.WebForm2" %>
<%@ Register TagPrefix="ajaxToolkit" Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" %>
<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35"
	Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>
<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
<script type="text/javascript" src="//code.jquery.com/jquery-1.10.2.js"></script>
<script type="text/javascript" src="//code.jquery.com/ui/1.10.4/jquery-ui.js"></script>
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
	<h2 style="text-align:center"> Paramétrage du Backtest </h2>
	
    <div id="div_parameters" runat="server">
    <div id="backtest_div" style="-moz-box-sizing: border-box;width:70%;border:1px solid grey;border-radius:5px;margin-top:10px;margin-bottom:20px;margin-left:15%;">
            <div id="backtest_label">Backtest Parameters</div>
            <div id="parameters" style="padding:10px 10px 10px 10px;margin-bottom:10px">
                <div style="height: 40px;width:49%;float:left;">
                    <div style="float:left;width:40%;font-weight:bold;position:relative;top:11px;">Start Date:</div>
                    <asp:TextBox ID="datepicker" Text="02/01/2004" runat="server" ></asp:TextBox>
                </div>
                <div style="height: 40px;width:49%;float:right">
                    <div style="float:left;width:25%;font-weight:bold;position:relative;top:11px;">End Date:</div>
                    <asp:TextBox ID="datepicker2" Text="02/01/2010" ViewStateMode="Enabled" runat="server"></asp:TextBox>
                </div>
                <div style="clear:both"></div>
                <div style="height: 30px">
                    <div style="float:left;width:20%;font-weight:bold">Nombre de rebalancement:</div>
                    <div id="slider1" style="float:left;width:70%;position:relative;top:5px"></div>
                    <asp:HiddenField ID="hidden_estimate" runat="server" />
                    <asp:TextBox ID="estimate_time" style="float:left;width: 35px;border:0; color: #f6931f; font-weight: bold; margin-left:5px;" runat="server">40</asp:TextBox>
                </div>
            </div>
            <div id="simulation" style="float:right;margin-right:300px;" runat="server">
                <asp:Button ID="Button1" CssClass="run" runat="server" Text="Affiche" OnClick="Hedge"   />
            </div>
       </div>
        </div>
        <div id="Affichage"  runat="server" Height="1000px" Width="1200px" style="display:none;">
	    <asp:Chart ID="Chart1" runat="server" Height="800px" Width="1000px" style="margin-left:20%;">
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
	    </div>

        <script type="text/javascript">
            function isPostBack() {
                return "<%= Page.IsPostBack.ToString().ToLower() %>" == "true";
            }
            $(function () {
                var dateMin = new Date();
                var weekDays = AddWeekDays(3);

                dateMin.setDate(dateMin.getDate() + weekDays);

                var natDays = [
          [1, 1, 'uk'],
          [12, 25, 'uk'],
          [12, 26, 'uk']
        ];

                function noWeekendsOrHolidays(date) {
                    var noWeekend = $.datepicker.noWeekends(date);
                    if (noWeekend[0]) {
                        return nationalDays(date);
                    } else {
                        return noWeekend;
                    }
                }
                function nationalDays(date) {
                    for (i = 0; i < natDays.length; i++) {
                        if (date.getMonth() == natDays[i][0] - 1 && date.getDate() == natDays[i][1]) {
                            return [false, natDays[i][2] + '_day'];
                        }
                    }
                    return [true, ''];
                }
                function AddWeekDays(weekDaysToAdd) {
                    var daysToAdd = 0
                    var mydate = new Date()
                    var day = mydate.getDay()
                    weekDaysToAdd = weekDaysToAdd - (5 - day)
                    if ((5 - day) < weekDaysToAdd || weekDaysToAdd == 1) {
                        daysToAdd = (5 - day) + 2 + daysToAdd
                    } else { // (5-day) >= weekDaysToAdd
                        daysToAdd = (5 - day) + daysToAdd
                    }
                    while (weekDaysToAdd != 0) {
                        var week = weekDaysToAdd - 5
                        if (week > 0) {
                            daysToAdd = 7 + daysToAdd
                            weekDaysToAdd = weekDaysToAdd - 5
                        } else { // week < 0
                            daysToAdd = (5 + week) + daysToAdd
                            weekDaysToAdd = weekDaysToAdd - (5 + week)
                        }
                    }

                    return daysToAdd;
                }

//                $("#parameters_button").click(function () {
//                    $("#<%=div_parameters.ClientID%>").slideToggle("slow");
//                });
                
                $("#<%= datepicker.ClientID %>").datepicker({
                           
                           dateFormat: "dd/mm/yy",
                           maxDate: new Date(2004,03,29),
                           minDate: new Date(2000,00,01),
                           changeMonth: true,
                           changeYear: true,
                           beforeShowDay: noWeekendsOrHolidays,
                           buttonImage: "Images/calendar.png",
                           showOn: "both",
                           buttonImageOnly: true,
                           //showAnim: "slideDown",
                           onSelect: function (selectedDate) {
                               var an = parseInt(selectedDate[6]+selectedDate[7]+selectedDate[8]+selectedDate[9]);
                               var mois = parseInt(selectedDate[3]+selectedDate[4]);
                               var jour =  parseInt(selectedDate[0]+selectedDate[1]);
                               var date = new Date(an+6,mois-1,jour);
                              // alert(an+6);
                               $("#<%= datepicker2.ClientID %>").datepicker("option", "minDate", date);
                               $("#<%= datepicker2.ClientID %>").datepicker("option", "maxDate", date);
                           }
                       });

                      $("#<%= datepicker2.ClientID %>").datepicker({
                           dateFormat: "dd/mm/yy",
                           maxDate: new Date(2010,03,29),
                           minDate: new Date(2006,00,01),
                           changeMonth: true,
                           changeYear: true,
                           beforeShowDay: noWeekendsOrHolidays,
                           buttonImage: "Images/calendar.png",
                           showOn: "both",
                           buttonImageOnly: true,
                           //showAnim: "slideDown",
                           onSelect: function (selectedDate) {
                               var an = parseInt(selectedDate[6] + selectedDate[7] + selectedDate[8] + selectedDate[9]);
                               var mois = parseInt(selectedDate[3] + selectedDate[4]);
                               var jour = parseInt(selectedDate[0] + selectedDate[1]);
                               var date = new Date(an - 6, mois - 1, jour);
                               $("#<%= datepicker.ClientID %>").datepicker("option", "minDate", date);
                               $("#<%= datepicker.ClientID %>").datepicker("option", "maxDate", date);
                           }
                       });
                       $("#<%= datepicker.ClientID %>, #<%= datepicker2.ClientID %>").keypress(function (e) {
                           e.preventDefault();
                       });
                     



            });
       </script>
    
</asp:Content>

