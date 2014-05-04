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
            //for (int d = 0; d < 4; d++)
            //{
            Button tmp = (Button)sender;
            int d;
            double lastSpot =0.0;
            double firstSpot = 0.0;
            int ind = hello.searchDate(DateTime.Now);
                if (tmp.ID.Equals("first"))
                {
                    d = 0;
                    Chart1.Titles.Add("Evolution du cours du Footsie");
                    for (int j = 0; j < ind; ++j)
                    {
                        if (hello.Spot[d][j] != 0)
                        {
                            Chart1.Series[0].Points.AddXY(hello.Dates[j], hello.Spot[d][j]);
                            lastSpot = hello.Spot[d][j];
                            if (firstSpot == 0)
                            {
                                firstSpot = hello.Spot[d][j];
                            }
                        }


                    }
                    double perf = Math.Round(100.0 * (lastSpot -  firstSpot) / firstSpot, 2);
                    Perf_Asset.Text = perf.ToString() + "%";
                    Asset.Style.Add(HtmlTextWriterStyle.Display, "inline");
                }
                else if (tmp.ID.Equals("second"))
                {
                    d = 1;
                    Chart1.Titles.Add("Evolution du cours du S&P 500");
                    for (int j = 0; j < ind; ++j)
                    {
                        if (hello.Spot[d][j] != 0)
                        {
                            Chart1.Series[0].Points.AddXY(hello.Dates[j], hello.Spot[d][j]);
                            lastSpot = hello.Spot[d][j];
                            if (firstSpot == 0)
                            {
                                firstSpot = hello.Spot[d][j];
                            }
                        }
                    }
                    double perf = Math.Round(100.0 * (lastSpot - firstSpot) / firstSpot, 2);
                    Perf_Asset.Text = perf.ToString() + "%";
                    Asset.Style.Add(HtmlTextWriterStyle.Display, "inline");
                }
                else if (tmp.ID.Equals("third"))
                {
                    d = 2;
                    Chart1.Titles.Add("Evolution du cours du Nikkei");
                    for (int j = 0; j < ind; ++j)
                    {
                        if (hello.Spot[d][j] != 0)
                        {
                            Chart1.Series[0].Points.AddXY(hello.Dates[j], hello.Spot[d][j]);
                            lastSpot = hello.Spot[d][j];
                            if (firstSpot == 0)
                            {
                                firstSpot = hello.Spot[d][j];
                            }
                        }

                    }
                    double perf = Math.Round(100.0 * (lastSpot - firstSpot) / firstSpot, 2);
                    Perf_Asset.Text = perf.ToString() + "%";
                    Asset.Style.Add(HtmlTextWriterStyle.Display, "inline");
                }
                else if (tmp.ID.Equals("fourth"))
                {
                    d = 3;
                    Chart1.Titles.Add("Evolution du cours du Eurostoxx");
                    for (int j = 0; j < ind; ++j)
                    {
                        if (hello.Spot[d][j] != 0)
                        {
                            Chart1.Series[0].Points.AddXY(hello.Dates[j], hello.Spot[d][j]);
                            lastSpot = hello.Spot[d][j];
                            if (firstSpot == 0)
                            {
                                firstSpot = hello.Spot[d][j];
                            }
                        }

                    }
                    double perf = Math.Round(100.0 * (lastSpot - firstSpot) / firstSpot, 2);
                    Perf_Asset.Text = perf.ToString() + "%";
                    Asset.Style.Add(HtmlTextWriterStyle.Display, "inline");
                }
            //}
            //simulation.Style.Add(HtmlTextWriterStyle.Display, "none");
            }
        }
    }