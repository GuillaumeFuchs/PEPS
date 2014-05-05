using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.DataVisualization.Charting;
using Wrapper;
using AffichageBD;
using AccesDB;
using Parameters;

namespace WebApp
{
    public partial class WebForm1 : System.Web.UI.Page
    {

        //AJOUTER DES ATTRIBUTS AUX LIEUX DE TOUT RECALCULER
        static WrapperClass wrap = new WrapperClass(4, 60);
        static int day = 0;
        static int past_size = 0;
        static double[] past = new double[61 * 4];
        static int pass = 0;

        protected void Page_Load(object sender, EventArgs e)
        {
            DateTime DateDeb = new DateTime(2010, 4, 29);
            DateTime DateFin = new DateTime(2016, 5, 29);
            DateTime Maturity = new DateTime(2016, 5, 29);
            TimeSpan difference = DateFin.Date - DateDeb.Date;
            DateFin = DateTime.Now;

            double rebalancement = double.Parse(estimate_time.Text.ToString());
            WrapperClass wrap = new WrapperClass(4, 60);
            AccesBD acces = new AccesDB.AccesBD();
            acces.DeleteCompo(new DateTime(2010, 4, 29), new DateTime(2016, 6, 29));
            acces.DeletePeps(DateTime.Now.AddDays(1), new DateTime(2016, 6, 29));
            //acces.getAssetSpot("FTSE", DateDeb, DateDeb);
            AfficheBD affiche = new AffichageBD.AfficheBD();
            double[] spot = new double[4];

            //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
            ComputeParam cp = new ComputeParam();
            cp.param(40, DateDeb);
            double[] sigma = new double[4];
            double[] rho = new double[16];
            for (int i = 0; i < 4; i++)
            {
                sigma[i] = cp.Volatility[i];
                for (int j = 0; j < 4; j++)
                {
                    rho[i * 4 + j] = cp.Corel[i, j];
                }
            }
            double[] coeff = new double[4];
            double[][] past = new double[4][];
            for (int i = 0; i < 4; i++)
            {
                coeff[i] = 0.25;
            }

            //Préparation du calcul des valeurs
            DateTime Datee = DateDeb;
            int cpt = 0;
            DateTime previousDate = DateDeb;

            int pas = (difference.Days) / (int)rebalancement + 1;
            //Traitement du cas où la date de départ est celle de début du produit

            int taille = ((((DateFin.Date - DateDeb.Date).Days) / pas) + 1);

            while (DateFin.CompareTo(DateDeb) > 0)
            {
                past[0] = acces.getAssetSpot("FTSE", DateDeb, Datee);
                past[1] = acces.getAssetSpot("S&P", DateDeb, Datee);
                past[2] = acces.getAssetSpot("NIKKEI", DateDeb, Datee);
                past[3] = acces.getAssetSpot("EUROSTOXX", DateDeb, Datee);
                double[] realPast = new double[past[0].Length * 4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < past[0].Length; j++)
                    {
                        realPast[i * past[0].Length + j] = past[i][j];
                    }
                }
                //Temporaire

                double risk = acces.getCurrentRisk(previousDate);
                double riskfree = acces.getCurrentRiskFree(previousDate);
                double[] tmpDelta = acces.getDelta(previousDate);

                //Traitement du cas où la date de départ est celle de début du produit
                //Changer le Past en tableaux bidimmensionnels !!
                wrap.computePortfolio(past[0].Length, 4, 30, 1000, (int)rebalancement, ((Maturity.Date - Datee.Date).Days) / 365.0, (DateDeb - Datee).Days / 365.0, 0.05, sigma, rho, coeff, realPast);
                acces.Insert(DateDeb, wrap.getPrice(), wrap.getDelta(), wrap.getRiskFree(), wrap.getRisk());
                previousDate = DateDeb;
                DateDeb = DateDeb.AddDays(pas);
                //cpt++;
            }
        }

        //SIMUL FUCHS EVOL PORTEFEUILLE

        protected void Start_Click(object sender, EventArgs e)
        {
            DateTime DateDeb = new DateTime(2010,4,29);
            DateTime DateFin = new DateTime(2016,05,29);
            TimeSpan difference = DateFin.Date - DateDeb.Date;
            DateDeb = DateTime.Now;

            double rebalancement = double.Parse(estimate_time.Text.ToString());
            WrapperClass wrap = new WrapperClass(4, 60);
            AccesBD acces = new AccesDB.AccesBD();
            acces.DeleteCompo(DateTime.Now.AddDays(1), new DateTime(2016, 5, 29));
            //acces.getAssetSpot("FTSE", DateDeb, DateDeb);
            AfficheBD affiche = new AffichageBD.AfficheBD();
            double[] spot = new double[4];

            //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
            ComputeParam cp = new ComputeParam();
            cp.param(40, new DateTime(2010,4,29));
            double[] sigma = new double[4];
            double[] rho = new double[16];
            for (int i = 0; i < 4; i++)
            {
                sigma[i] = cp.Volatility[i];
                for (int j = 0; j < 4; j++)
                {
                    rho[i * 4 + j] = cp.Corel[i, j];
                }
            }
            double[] coeff = new double[4];
            double[][] past = new double[4][];
            for (int i = 0; i < 4; i++)
            {
                coeff[i] = 0.25;
            }

            //Préparation du calcul des valeurs
            DateTime Datee = new DateTime(2010,4,29);
            int cpt = 0;
            DateTime previousDate = DateDeb;

            DateTime LastTimeBD = new DateTime(1, 1, 1);
            spot = acces.getLastSpot(ref LastTimeBD);
            int pas = (difference.Days) / (int)rebalancement + 1;
            int taille = ((((DateFin.Date - DateDeb.Date).Days) / pas) + 1);
            //Calcul des valeurs de marché durant la couverture
            int taille_bis = (DateFin.Date - DateDeb.Date).Days;
            double[] futurSpot = new double[4];
            double[] PathSim = new Double[4 * taille_bis];
            wrap.getSimulMarket(4,taille_bis ,((DateFin.Date - DateDeb.Date).Days) / 365.0, 0.05, spot, sigma, rho, coeff, PathSim);
            for (int k = 0; k < taille_bis; ++k)
            {
                futurSpot[0] = PathSim[k];
                futurSpot[1] = PathSim[k + taille_bis];
                futurSpot[2] = PathSim[k + 2 * taille_bis];
                futurSpot[3] = PathSim[k + 3 * taille_bis];
                //acces.Insert(DateDeb.AddDays((k + 1) * pas), futurSpot);
                acces.Insert(DateDeb.AddDays(k), futurSpot);
            }

            //AJOUT
            Chart1.Titles.Add("Composition du portefeuille de couverture");
            Chart1.Legends.Add(new Legend("Valeur du portefeuille"));
            Chart1.Legends.Add(new Legend("Valeur du produit"));
            Chart1.Series[0].Name = "Valeur du portefeuille";
            Chart1.Series[1].Name = "Valeur du produit";

            past[0] = acces.getAssetSpot("FTSE", DateDeb, Datee);
            past[1] = acces.getAssetSpot("S&P", DateDeb, Datee);
            past[2] = acces.getAssetSpot("NIKKEI", DateDeb, Datee);
            past[3] = acces.getAssetSpot("EUROSTOXX", DateDeb, Datee);
            double[] realPast = new double[past[0].Length * 4];
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < past[0].Length; j++)
                {
                    realPast[i * past[0].Length + j] = past[i][j];
                }
            }
            //Temporaire

            double risk = acces.getCurrentRisk(previousDate);
            double riskfree = acces.getCurrentRiskFree(previousDate);
            double[] tmpDelta = acces.getDelta(previousDate);

            //Traitement du cas où la date de départ est celle de début du produit
            //Changer le Past en tableaux bidimmensionnels !!
            wrap.computePortfolio(past[0].Length, 4, 30, 1000,(int)rebalancement , ((DateFin.Date - Datee.Date).Days) / 365.0, (DateTime.Now-DateDeb).Days / 365.0, 0.05, sigma, rho, coeff, realPast);
            acces.Insert(DateDeb, wrap.getPrice(), wrap.getDelta(), wrap.getRiskFree(), wrap.getRisk());
            previousDate = DateDeb;

            String[,] values = acces.extractData(Datee, DateTime.Now.AddDays(pas));
            for (int i = 0; i < values.Length / 3; ++i)
            {
                Chart1.Series[0].Points.AddXY(DateTime.Parse(values[2,i]),double.Parse(values[1,i]));
                Chart1.Series[1].Points.AddXY(DateTime.Parse(values[2,i]),double.Parse(values[0, i]));
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