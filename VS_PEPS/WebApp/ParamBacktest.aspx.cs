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
using Wrapper;
using Parameters;
using AccesDB;
using AffichageBD;
using DataExporter;
using APIFiMag.Datas;
using APIFiMag;
using APIFiMag.Importer;

namespace WebApp
{
    public partial class WebForm2 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            ////Initialisation manuelle de la base de données en ajoutant les cours des actifs
            //List<HistoricalColumn> list = new List<HistoricalColumn>();
            //list.Add(HistoricalColumn.Close);
            //List<String> symbol = new List<String>();
            //symbol.Add("^FTSE");
            //symbol.Add("^GSPC");
            //symbol.Add("^N225");
            //symbol.Add("^STOXX50E");
            //DataActif actif = new DataActif(symbol, list, new DateTime(2000, 1, 1), DateTime.Now);
            //actif.ImportData(new ImportYahoo());
            //// actif.Export(new DBExporter());
            ////Initialisation des taux de changes
            //List<Currency> curr = new List<Currency>();
            //curr.Add(Currency.USD);
            //curr.Add(Currency.JPY);
            //curr.Add(Currency.GBP);
            //DateTime init = new DateTime(2000, 1, 1);
            //DBExporter hello = new DBExporter();
            //DataFXTop xchange;
            //while (DateTime.Now.CompareTo(init) > 0)
            //{
            //    if (init.AddYears(1).CompareTo(DateTime.Now) > 0)
            //    {
            //        xchange = new DataFXTop(Currency.EUR, curr, init, DateTime.Now, Frequency.Daily);
            //        xchange.ImportData(new ParserFXTop());
            //        hello.Export(actif, xchange, init, DateTime.Now);
            //        init = DateTime.Now;
            //    }
            //    else
            //    {
            //        xchange = new DataFXTop(Currency.EUR, curr, init, init.AddYears(1), Frequency.Daily);
            //        xchange.ImportData(new ParserFXTop());
            //        hello.Export(actif, xchange, init, init.AddYears(1));
            //        init = init.AddYears(1).AddDays(1);
            //    }
            //}


            //if (!IsPostBack)
            //{
            //    hidden_estimate.Value = "40";
            //}
        }

        protected void Hedge(object sender, EventArgs e)
        {
            //Affichage de la courbe associée au portefeuille

            DateTime DateDeb = DateTime.Parse(datepicker.Text.ToString());
            DateTime DateFin = DateTime.Parse(datepicker2.Text.ToString());
            TimeSpan difference = DateFin.Date - DateDeb.Date ;
            
            double rebalancement  = double.Parse(estimate_time.Text.ToString());
            WrapperClass wrap = new WrapperClass(4,60);
            AccesBD acces = new AccesDB.AccesBD();
            acces.DeleteCompo(new DateTime(2000, 1, 1), new DateTime(2010, 4, 29));
            //acces.getAssetSpot("FTSE", DateDeb, DateDeb);
            AfficheBD affiche = new AffichageBD.AfficheBD();
            double[] spot = new double[4];

            //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
            ComputeParam cp = new ComputeParam();
            cp.param(400,DateDeb);
            double[] sigma = new double[4];
            double[] rho = new double[16];
            for (int i = 0; i<4; i++){
                sigma[i] = cp.Volatility[i];
                for (int j = 0 ; j < 4; j++){
                    rho[i*4+j] = cp.Corel[i,j];
                }
            }
            double[] coeff = new double[4];
            double[][] past = new double[4][];
            for (int i = 0; i<4; i++){
                coeff[i] = 0.25;
            }

            //Préparation du calcul des valeurs
            String Date = datepicker.Text.ToString();
            //DateTime Datee = new DateTime(2010, 4, 29);
            DateTime Datee = DateDeb;
            Chart1.Titles.Add("Composition du portefeuille de couverture");
            Chart1.Legends.Add(new Legend("Valeur du portefeuille"));
            Chart1.Legends.Add(new Legend("Valeur du produit"));
            Chart1.Series[0].Name = "Valeur du portefeuille";
            Chart1.Series[1].Name = "Valeur du produit";
            int cpt = 0;
            DateTime previousDate = DateDeb;

            int pas = (difference.Days) / (int)rebalancement+1;

            //Traitement du cas où la date de départ est celle de début du produit
            //FAUX
            DateTime DateFinBD = new DateTime(1,1,1);
            spot = acces.getLastSpot(ref DateFinBD);
            
            
            //SIMULATION A UTILISER POUR VIE PRODUIT

            //int taille = ((((DateFin.Date - DateTime.Now.Date).Days) / pas) + 1);
            int taille = ((((DateFin.Date - DateDeb.Date).Days) / pas) + 1);
            //double[] futurSpot = new double[4];
            //double[] PathSim = new Double[4 * taille];
            //wrap.getSimulMarket(4, taille-1, ((DateFin.Date - DateDeb.Date).Days) / 365.0, 0.05, spot, sigma, rho, coeff, PathSim);
            //for (int k = 0; k < taille; ++k)
            //{
            //    futurSpot[0] = PathSim[k];
            //    futurSpot[1] = PathSim[k+taille];
            //    futurSpot[2] = PathSim[k+2*taille];
            //    futurSpot[3] = PathSim[k+3*taille];
            //    acces.Insert(DateDeb.AddDays((k + 1) * pas), futurSpot);
            //}
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
                wrap.computePortfolio(past[0].Length, 4, 30, 10000, (int)rebalancement, 6.0, ((double)cpt*6) / rebalancement, 0.05, sigma, rho, coeff, realPast);
                acces.Insert(DateDeb, wrap.getPrice(), wrap.getDelta(), wrap.getRiskFree(), wrap.getRisk());
                //Affichage du portefeuille
                Chart1.Series[0].Points.AddXY(DateDeb, wrap.getRisk()+wrap.getRiskFree());
                Chart1.Series[1].Points.AddXY(DateDeb, wrap.getPrice());
                //Chart1.Series[1].Points.AddXY(DateDeb, risk + riskfree);
                previousDate = DateDeb;
                DateDeb = DateDeb.AddDays(pas);
                cpt++;
            }
            Affichage.Style.Add(HtmlTextWriterStyle.Display, "inline");
        }
    }
}