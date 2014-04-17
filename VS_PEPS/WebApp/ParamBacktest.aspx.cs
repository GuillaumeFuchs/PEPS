using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Script.Serialization;
using System.Web.UI.DataVisualization.Charting;
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
            //Initialisation manuelle
            List<HistoricalColumn> list = new List<HistoricalColumn>();
            list.Add(HistoricalColumn.Close);
            List<String> symbol = new List<String>();
            symbol.Add("^FTSE");
            symbol.Add("^GSPC");
            symbol.Add("^N225");
            symbol.Add("^STOXX50E");
            DataActif actif = new DataActif(symbol, list, new DateTime(2010, 04, 29), DateTime.Now);
            actif.ImportData(new ImportYahoo());
            actif.Export(new DBExporter());
            DateTime d = DateTime.Now;
            Console.ReadKey();



            DateTime DateDeb = DateTime.Parse(datepicker.Text.ToString());
            DateTime DateFin = DateTime.Parse(datepicker2.Text.ToString());
            double rebalancement  = double.Parse(estimate_time.Text.ToString());
            WrapperClass wrap = new WrapperClass(4,60);
            AccesBD acces = new AccesDB.AccesBD();
            AfficheBD affiche = new AffichageBD.AfficheBD();
            double[] spot = new double[4];
            //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
            ComputeParam cp = new ComputeParam();
            cp.param(40);
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
            past[0] = acces.getPast("^FTSE", DateDeb, DateFin);
            past[1] = acces.getPast("^GSPC", DateDeb, DateFin);
            past[2] = acces.getPast("^N225", DateDeb, DateFin);
            past[3] = acces.getPast("^STOXX50E", DateDeb, DateFin);
            double risk = acces.getCurrentRisk();
            double riskfree = acces.getCurrentRiskFree();
            double[][] tmpDelta = acces.getDelta();
            double[] Delta = new double[4];
            Delta[0] = tmpDelta[0][0];
            Delta[1] = tmpDelta[1][0];
            Delta[2] = tmpDelta[2][0];
            Delta[3] = tmpDelta[3][0];
            String Date = datepicker.Text.ToString();
           

           //wrap.getHedge(Base64FormattingOptions, spot, 150, sigma, 0.05, coeff, rho, 6, 30, 60, 100);

            //Traitement du cas où la date de départ est celle de début du produit
            //Changer le Past en tableaux bidimmensionnels !!
            //wrap.computePortfolio(past.Length/4, 4, 30, 100, (int)rebalancement, 6, 0, 0.05, risk, riskfree, sigma, rho, coeff, null, Delta); 

            //Affichage du portefeuille
            Chart1.Titles.Add("Composition du portefeuille de couverture");
            for (int p = 0; p < 4; p++)
            {
                Chart1.Legends.Add(new Legend("Delta du " + cp.Assets[p]));
                for (int j = 0; j < wrap.getSummary().Length/13-2 ; ++j)
                {
              //      Chart1.Series[d].Points.AddXY(summary[j * 13], summary[j * 13 + 5 + d]);
                }
                Chart1.Series[p].Name = "Delta du " + cp.Assets[p];
                Affichage.Style.Add(HtmlTextWriterStyle.Display, "inline");
            }
        }
    }
}