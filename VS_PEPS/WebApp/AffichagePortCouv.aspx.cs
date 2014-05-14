using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Script.Serialization;
using System.Web.UI.DataVisualization.Charting;
using System.Globalization;
using Wrapper;
using Parameters;
using AffichageBD;
using AccesDB;

namespace WebApp
{
    public partial class AffichagePortCouv : System.Web.UI.Page
    {
		static WrapperClass wrap = new WrapperClass(4, 60);
		static int day = 0;
		static int past_size = 0;
		static double[] past = new double[301*4];
		static Boolean vu = false;

        protected void Page_Load(object sender, EventArgs e)
        {
			if (!vu)
			{
				int H = 300;
				int size = 4;
				double[] spot = new double[] { 100, 100, 100, 100 };
				double[] sigma = new double[] { 0.25, 0.15, 0.3, 0.2 };
				double r = 0.05;
				double T = 6.0;
				double[] coeff = new double[] { .25, .25, .25, .25 };
				double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

				//Calcul des valeurs de marché durant la couverture
				wrap.getSimulMarket(size, H, T, r, spot, sigma, rho, coeff, past);

				//Affichage du portefeuille
				Chart1.Titles.Add("Composition du portefeuille de couverture");
				for (int d = 0; d < 4; d++)
				{
					Chart1.Legends.Add(new Legend("Past " + d.ToString()));
					for (int j = 0; j < H + 1; j++)
					{
						Chart1.Series[d].Points.AddXY(j, past[d * (H + 1) + j]);
					}
					Chart1.Series[d].Name = "Past " + d.ToString();
					Affichage.Style.Add(HtmlTextWriterStyle.Display, "inline");
				}


				Portfolio_value.Text = "0";
				Product_value.Text = "0";
				Err_value.Text = "0";
				Next_day.Visible = false;
				vu = true;
			}
        }

        //SIMUL FUCHS EVOL PORTEFEUILLE

		protected void Start_Click(object sender, EventArgs e)
		{
			int N = 6;
			int H = 300;
			int M = 1000;
			int size = 4;
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double T = 6.0;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

			for (int k = 0; k < H + 1; k++)
			{
				double[] past_extract = new double[size * (day + 1)];
				for (int i = 0; i < day + 1; i++)
				{
					for (int d = 0; d < size; d++)
						past_extract[d * (day + 1) + i] = past[d * (H + 1) + i];
				}

				wrap.computePortfolio(day + 1, size, N, M, H, T, (double)day * (double)N / (double)H, r, sigma, rho, coeff, past_extract);
				
				if (wrap.getPrice() == 0.0)
					break;

				Portfolio_value.Text = (wrap.getRisk() + wrap.getRiskFree()).ToString();
				Product_value.Text = wrap.getPrice().ToString();
				Err_value.Text = wrap.getErr().ToString();

				Label1.Text = wrap.getDelta()[0].ToString();
				Label2.Text = wrap.getDelta()[1].ToString();
				Label3.Text = wrap.getDelta()[2].ToString();
				Label4.Text = wrap.getDelta()[3].ToString();

				Chart2.Series[0].Points.AddXY(day, wrap.getRisk() + wrap.getRiskFree());
				Chart2.Series[1].Points.AddXY(day, wrap.getPrice());

				Chart3.Series[0].Points.AddXY(day, wrap.getErr());
				day++;


			}
			Next_day.Text = "Calcul au jour " + day.ToString();

		}


        //AVANCER D'UNE DATE SIMUL FUCHS

		protected void Next_day_Click(object sender, EventArgs e)
		{
			int N = 6;
			int H = 300;
			int M = 1000;
			int size = 4;
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double T = 6.0;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

			double[] past_extract = new double[size * (day + 1)];
			for (int i = 0; i < day + 1; i++)
			{
				for (int d = 0; d < size; d++)
					past_extract[d * (day + 1) + i] = past[d * (H + 1) + i];
			}

			wrap.computePortfolio(day + 1, size, N, M, H, T, (double)day * (double)N / (double)H, r, sigma, rho, coeff, past_extract);

			Portfolio_value.Text = (wrap.getRisk() + wrap.getRiskFree()).ToString();
			Product_value.Text = wrap.getPrice().ToString();
			Err_value.Text = wrap.getErr().ToString();

			Label1.Text = wrap.getDelta()[0].ToString();
			Label2.Text = wrap.getDelta()[1].ToString();
			Label3.Text = wrap.getDelta()[2].ToString();
			Label4.Text = wrap.getDelta()[3].ToString();

			Chart2.Series[0].Points.AddXY(day, wrap.getRisk() + wrap.getRiskFree());
			Chart2.Series[1].Points.AddXY(day, wrap.getPrice());

			Chart3.Series[0].Points.AddXY(day, wrap.getErr());

			day++;
			Next_day.Text = "Calcul au jour " + day.ToString();

		}
	}
}