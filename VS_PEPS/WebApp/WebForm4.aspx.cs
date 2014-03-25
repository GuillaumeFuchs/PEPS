using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using System.Windows.Forms.DataVisualization.Charting;

namespace WebApp
{
    public partial class WebForm4 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Simulate(object sender, EventArgs e)
        {

                AffichageBD.AfficheBD hello = new AffichageBD.AfficheBD();
                for (int d = 0; d < 4; d++)
                {
                    if (d == 0)
                    {
                        Chart1.Titles.Add("Evolution du cours de l'Eurostoxx");
                        for (int j = 0; j < hello.Dates[d].Length; ++j)
                        {
                            Chart1.Series[0].Points.AddXY(hello.Dates[d][j], hello.Spot[d][j]);
                           

                        }
                        double perf = Math.Round(100.0 * (hello.Spot[d][0] - hello.Spot[d][hello.Spot[d].Length - 1]) / hello.Spot[d][hello.Spot[d].Length - 1], 2);
                        Perf_Euro.Text = perf.ToString() + "%";
                        Stoxx.Style.Add(HtmlTextWriterStyle.Display, "inline");
                    }else if (d==1){
                        Chart2.Titles.Add("Evolution du cours du Footsie");
                        for (int j = 0; j < hello.Dates[d].Length; ++j)
                        {
                            Chart2.Series[0].Points.AddXY(hello.Dates[d][j], hello.Spot[d][j]);
                        }
                        double perf = Math.Round(100.0 * (hello.Spot[d][0] - hello.Spot[d][hello.Spot[d].Length - 1]) / hello.Spot[d][hello.Spot[d].Length - 1],2);
                        Perf_Footsie.Text = perf.ToString() + "%";
                        Ftse.Style.Add(HtmlTextWriterStyle.Display, "inline");
                    }else if (d==2){
                        Chart3.Titles.Add("Evolution du cours du Nikkei");
                        for (int j = 0; j < hello.Dates[d].Length; ++j)
                        {
                            Chart3.Series[0].Points.AddXY(hello.Dates[d][j], hello.Spot[d][j]);
                            
                        }
                        double perf = Math.Round(100.0 * (hello.Spot[d][0] - hello.Spot[d][hello.Spot[d].Length - 1]) / hello.Spot[d][hello.Spot[d].Length - 1],2);
                        Perf_Nikkei.Text = perf.ToString() + "%";
                        N225.Style.Add(HtmlTextWriterStyle.Display, "inline");
                    }
                    else if (d == 3)
                    {
                        Chart4.Titles.Add("Evolution du cours du S&P 500");
                        for (int j = 0; j < hello.Dates[d].Length; ++j)
                        {
                            Chart4.Series[0].Points.AddXY(hello.Dates[d][j], hello.Spot[d][j]);
                            
                        }
                        double perf = Math.Round(100.0 * (hello.Spot[d][0] - hello.Spot[d][hello.Spot[d].Length - 1]) / hello.Spot[d][hello.Spot[d].Length - 1],2);
                        Perf_SP.Text = perf.ToString() + "%";
                        SP.Style.Add(HtmlTextWriterStyle.Display, "inline");
                    }
                }
                simulation.Style.Add(HtmlTextWriterStyle.Display, "none");
            }
        }
    }