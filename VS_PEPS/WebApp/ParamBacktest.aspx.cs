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
            if (!IsPostBack)
            {
                hidden_estimate.Value = "40";
            }
        }

        protected void Hedge(object sender, EventArgs e)
        {
            //Initialisation manuelle de la base de données en ajoutant les cours des actifs
            List<HistoricalColumn> list = new List<HistoricalColumn>();
            list.Add(HistoricalColumn.Close);
            List<String> symbol = new List<String>();
            symbol.Add("^FTSE");
            symbol.Add("^GSPC");
            symbol.Add("^N225");
            symbol.Add("^STOXX50E");
            DataActif actif = new DataActif(symbol, list, new DateTime(2010, 04, 29), DateTime.Now);
            actif.ImportData(new ImportYahoo());
           // actif.Export(new DBExporter());
            //Initialisation des taux de changes
            List<Currency> curr = new List<Currency>();
            curr.Add(Currency.USD);
            curr.Add(Currency.JPY);
            curr.Add(Currency.GBP);
            DateTime init = new DateTime(2010, 4, 29);
            DBExporter hello = new DBExporter();
            DataFXTop xchange;
            while (DateTime.Now.CompareTo(init) > 0)
            {
                if (init.AddYears(1).CompareTo(DateTime.Now)>0)
                {
                    xchange = new DataFXTop(Currency.EUR, curr, init, DateTime.Now, Frequency.Daily);
                    xchange.ImportData(new ParserFXTop());
                    hello.Export(actif, xchange,init, DateTime.Now);
                    init = DateTime.Now;
                }
                else
                {
                    xchange = new DataFXTop(Currency.EUR, curr, init, init.AddYears(1), Frequency.Daily);
                    xchange.ImportData(new ParserFXTop());
                    hello.Export(actif, xchange, init, init.AddYears(1));
                    init = init.AddYears(1).AddDays(1);
                }
            }


            //Affichage de la courbe associée au portefeuille

            //inutile
            DateTime DateDeb = DateTime.Parse(datepicker.Text.ToString());
            //inutile
            DateTime DateFin = DateTime.Parse(datepicker2.Text.ToString());
            double rebalancement  = double.Parse(estimate_time.Text.ToString());
            WrapperClass wrap = new WrapperClass(4,60);
            AccesBD acces = new AccesDB.AccesBD();
            acces.getAssetSpot("FTSE", DateDeb, DateDeb);
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
            DateTime Datee = new DateTime(2010, 4, 29);
            Chart1.Titles.Add("Composition du portefeuille de couverture");
            Chart1.Legends.Add(new Legend("Valeur du portefeuille"));
            Chart1.Legends.Add(new Legend("Valeur du produit"));
            Chart1.Series[0].Name = "Valeur du portefeuille";
            Chart1.Series[1].Name = "Valeur du produit";
            DateTime test = new DateTime(2011, 05, 12);
            int cpt = 0;


            while (test.CompareTo(DateDeb) > 0)
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

                double risk = acces.getCurrentRisk(DateDeb);
                double riskfree = acces.getCurrentRiskFree(DateDeb);
                double[] tmpDelta = acces.getDelta(DateDeb);

                //Traitement du cas où la date de départ est celle de début du produit
                //Changer le Past en tableaux bidimmensionnels !!
                wrap.getPortfolio(past[0].Length, 4, 30, 100, (int)rebalancement, 6.0, ((double)cpt*6) / rebalancement, 0.05, sigma, rho, coeff, realPast);
                acces.Insert(DateDeb, wrap.getPrice(), wrap.getDeltaAnt(), wrap.getRiskFree(), wrap.getRisk());
                //Affichage du portefeuille
                Chart1.Series[0].Points.AddXY(DateDeb, wrap.getRisk()+wrap.getRiskFree());
                //Chart1.Series[1].Points.AddXY(DateDeb, risk + riskfree);
                DateDeb = DateDeb.AddDays(7);
                cpt++;
            }
            Affichage.Style.Add(HtmlTextWriterStyle.Display, "inline");
        }
    }
}