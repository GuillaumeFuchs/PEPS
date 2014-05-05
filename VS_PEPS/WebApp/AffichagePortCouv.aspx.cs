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
		static double[] past = new double[61*4];

        protected void Page_Load(object sender, EventArgs e)
        {
            //DateTime DateDeb = new DateTime(2010,4,29);
            //DateTime DateFin = DateTime.Now;
            //TimeSpan difference = DateFin.Date - DateDeb.Date;

            //double rebalancement = double.Parse(estimate_time.Text.ToString());
            //WrapperClass wrap = new WrapperClass(4, 60);
            //AccesBD acces = new AccesDB.AccesBD();
            //acces.DeleteCompo(new DateTime(2000, 1, 1), new DateTime(2010, 4, 29));
            ////acces.getAssetSpot("FTSE", DateDeb, DateDeb);
            //AfficheBD affiche = new AffichageBD.AfficheBD();
            //double[] spot = new double[4];

            ////On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
            //ComputeParam cp = new ComputeParam();
            //cp.param(40, DateDeb);
            //double[] sigma = new double[4];
            //double[] rho = new double[16];
            //for (int i = 0; i < 4; i++)
            //{
            //    sigma[i] = cp.Volatility[i];
            //    for (int j = 0; j < 4; j++)
            //    {
            //        rho[i * 4 + j] = cp.Corel[i, j];
            //    }
            //}
            //double[] coeff = new double[4];
            //double[][] past = new double[4][];
            //for (int i = 0; i < 4; i++)
            //{
            //    coeff[i] = 0.25;
            //}

            ////Préparation du calcul des valeurs
            //DateTime Datee = DateDeb;
            //int cpt = 0;
            //DateTime previousDate = DateDeb;

            //int pas = (difference.Days) / (int)rebalancement + 1;

            ////Traitement du cas où la date de départ est celle de début du produit
            ////FAUX
            //DateTime DateFinBD = new DateTime(1, 1, 1);
            //spot = acces.getLastSpot(ref DateFinBD);
            //int taille = ((((DateFin.Date - DateDeb.Date).Days) / pas) + 1);
            //while (DateFin.CompareTo(DateDeb) > 0)
            //{
            //    past[0] = acces.getAssetSpot("FTSE", DateDeb, Datee);
            //    past[1] = acces.getAssetSpot("S&P", DateDeb, Datee);
            //    past[2] = acces.getAssetSpot("NIKKEI", DateDeb, Datee);
            //    past[3] = acces.getAssetSpot("EUROSTOXX", DateDeb, Datee);
            //    double[] realPast = new double[past[0].Length * 4];
            //    for (int i = 0; i < 4; i++)
            //    {
            //        for (int j = 0; j < past[0].Length; j++)
            //        {
            //            realPast[i * past[0].Length + j] = past[i][j];
            //        }
            //    }
            //    //Temporaire

            //    double risk = acces.getCurrentRisk(previousDate);
            //    double riskfree = acces.getCurrentRiskFree(previousDate);
            //    double[] tmpDelta = acces.getDelta(previousDate);

            //    //Traitement du cas où la date de départ est celle de début du produit
            //    //Changer le Past en tableaux bidimmensionnels !!
            //    wrap.computePortfolio(past[0].Length, 4, 30, 100, (int)rebalancement, 6.0, ((double)cpt*6) / rebalancement, 0.05, sigma, rho, coeff, realPast);
            //    acces.Insert(DateDeb, wrap.getPrice(), wrap.getDelta(), wrap.getRiskFree(), wrap.getRisk());
            //    previousDate = DateDeb;
            //    DateDeb = DateDeb.AddDays(pas);
            //    cpt++;
            //}
        }

        //FIRST IMPLEM

        //protected void Hedge(object sender, EventArgs e)
        //{

        //    DateTime deb = new DateTime(2010, 04, 29);

        //    WrapperClass wrap = new WrapperClass(4,60);
        //    AffichageBD.AfficheBD hello = new AffichageBD.AfficheBD();
        //    double[] spot = new double[4];
        //    //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
        //    //L'ordre des spots à t il une importance ?
        //    for (int i = 0; i<4; i++){
        //        //Grosse approximation
        //        spot[i] = hello.Spot[i][0];
        //    }
        //    ComputeParam cp = new ComputeParam();
        //    cp.param(40,deb);
        //    double[] sigma = new double[4];
        //    double[] rho = new double[16];
        //    for (int i = 0; i<4; i++){
        //        sigma[i] = cp.Volatility[i];
        //        for (int j = 0 ; j < 4; j++){
        //            rho[i*4+j] = cp.Corel[i,j];
        //        }
        //    }
        //    double[] coeff = new double[4];
        //    for (int i = 0; i<4; i++){
        //        coeff[i] = 0.25;
        //    }
        //    //On fait appelle à la méthode de fuchs avec les paramètres choisit
        //    wrap.getHedge(4, spot, 150, sigma, 0.05, coeff, rho, 6, 30, 60, 100);

        //    double[] summary = new double[wrap.getSummary().Length];
        //    summary = wrap.getSummary();

        //    //Affichage du portefeuille
        //    Chart1.Titles.Add("Composition du portefeuille de couverture");
        //    for (int d = 0; d < 4; d++)
        //    {
        //        Chart1.Legends.Add(new Legend("Delta du " + cp.Assets[d]));
        //        for (int j = 0; j < wrap.getSummary().Length/13-2 ; ++j)
        //        {
        //            Chart1.Series[d].Points.AddXY(summary[j * 13], summary[j * 13 + 5 + d]);
        //        }
        //        Chart1.Series[d].Name = "Delta du " + cp.Assets[d];
        //        Affichage.Style.Add(HtmlTextWriterStyle.Display, "inline");
        //    }
			
        //}


        //SIMUL FUCHS EVOL PORTEFEUILLE

		protected void Start_Click(object sender, EventArgs e)
		{
			int H = 60;
			int size = 4;
			double[] spot = new double[] { 100, 100, 100, 100 };
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
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
			Start.Visible = false;
			Next_day.Visible = true;
			Next_day.Text = "Calcul au jour " + day.ToString();
		}


        //AVANCER D'UNE DATE SIMUL FUCHS

		protected void Next_day_Click(object sender, EventArgs e)
		{
			int N = 6;
			int H = 60;
			int M = 50000;
			int size = 4;
			double[] past_extract = new double[size * (day + 1)];
			for (int i = 0; i < day + 1; i++)
			{
				for (int d = 0; d < size; d++)
					past_extract[d * (day + 1) + i] = past[d * (H + 1) + i];
			}
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double T = 6.0;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

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