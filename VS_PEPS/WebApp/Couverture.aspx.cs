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
using System.Data;

namespace WebApp
{
    public partial class WebForm1 : System.Web.UI.Page
    {

        //AJOUTER DES ATTRIBUTS AUX LIEUX DE TOUT RECALCULER
        static DateTime Maturity = new DateTime(2016, 4, 29);
        static ComputeParam cp = new ComputeParam();
        static double[] sigma = new double[4];
        static double[] rho = new double[16];
        static double rebalancement;
        static double[] coeff = new double[4];
        static double[][] past = new double[4][];
        static WrapperClass wrap;
        static AccesBD acces = new AccesDB.AccesBD();
        static AfficheBD affiche = new AffichageBD.AfficheBD();
        static double[] spot = new double[4];
        static DateTime Datee = new DateTime(2010, 4, 29);
        static int pas;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                //DateTime DateDeb = new DateTime(2010, 4, 29);
                DateTime DateDeb = new DateTime(1, 1, 1);
                acces.getLastCompoDate(ref DateDeb);
                bool att = false;
                if (DateDeb.CompareTo(Datee) < 0)
                {
                    DateDeb = Datee;
                    att = true;
                }

                DateTime DateFin = DateTime.Now;
                TimeSpan difference = Maturity.Date - Datee.Date;

                rebalancement = double.Parse(estimate_time.Text.ToString());
                wrap = new WrapperClass(4, 60);

                //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
                cp.param(600, DateDeb.AddDays(-600));
                for (int i = 0; i < 4; i++)
                {
                    coeff[i] = 0.25;
                    sigma[i] = cp.Volatility[i] + 0.1;
                    for (int j = 0; j < 4; j++)
                    {
                        rho[i * 4 + j] = cp.Corel[i, j];
                    }
                }

                //Préparation du calcul des valeurs
                DateTime previousDate = DateDeb;
                pas = (difference.Days) / (int)rebalancement + 1;

                //Traitement du cas où la date de départ est celle de début du produit
                int taille = ((((DateFin.Date - DateDeb.Date).Days) / pas) + 1);
                if (DateDeb.CompareTo(Datee) >= 0 && !att)
                {
                    DateDeb = DateDeb.AddDays(pas);
                }
                att = false;
                while (DateFin.CompareTo(DateDeb) > 0)
                {
                    past[0] = acces.getAssetSpot("FTSE", DateDeb, Datee, pas);
                    past[1] = acces.getAssetSpot("S&P", DateDeb, Datee, pas);
                    past[2] = acces.getAssetSpot("NIKKEI", DateDeb, Datee, pas);
                    past[3] = acces.getAssetSpot("EUROSTOXX", DateDeb, Datee, pas);
                    double[] realPast = new double[past[0].Length * 4];
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < past[0].Length; j++)
                        {
                            realPast[i * past[0].Length + j] = past[i][j];
                        }
                    }

                    if (DateDeb.CompareTo(Datee) > 0)
                    {
                        Dictionary<string, string> dic = acces.getLastCouv(DateTime.Now);
                        double[] tmpDelta = new double[4];
                        tmpDelta[0] = double.Parse(dic["deltaFTSE"]);
                        tmpDelta[1] = double.Parse(dic["deltaS_P"]);
                        tmpDelta[2] = double.Parse(dic["deltaNIKKEI"]);
                        tmpDelta[3] = double.Parse(dic["deltaEURO"]);
                        double risk = double.Parse(dic["risk"]);
                        double riskfree = double.Parse(dic["riskfree"]);
                        double ValLiq = double.Parse(dic["ValLiq"]);
                        wrap = new WrapperClass(4, 60, ValLiq, tmpDelta, risk, riskfree);
                    }
                    //Traitement du cas où la date de départ est celle de début du produit
                    wrap.computePortfolio(past[0].Length, 4, 30, 1000, (int)rebalancement, ((Maturity.Date - Datee.Date).Days) / 365.0, (DateDeb - Datee).Days / 365.0, 0.05, sigma, rho, coeff, realPast);
                    acces.Insert(DateDeb, wrap.getPrice(), wrap.getDelta(), wrap.getRiskFree(), wrap.getRisk());
                    previousDate = DateDeb;
                    DateDeb = DateDeb.AddDays(pas);
                }

                Start_Click();
            }
            else
            {
                Start_Click();
            }
        }

        protected void Start_Click()
        {
            DateTime DateDeb = DateTime.Now;
            DateTime DateFin = new DateTime(2016,05,29);
            rebalancement = double.Parse(estimate_time.Text.ToString());
            
            Dictionary<string,string> dic  = acces.getLastCouv(DateTime.Now);
            double[] delt = new double[4];
            delt[0] = double.Parse(dic["deltaFTSE"]);
            delt[1] = double.Parse(dic["deltaS_P"]);
            delt[2] = double.Parse(dic["deltaNIKKEI"]);
            delt[3] = double.Parse(dic["deltaEURO"]);
            double riskinit  = double.Parse(dic["risk"]);
            double riskfreeinit  = double.Parse(dic["riskfree"]);
            double ValLiq  = double.Parse(dic["ValLiq"]);
            wrap = new WrapperClass(4, 60, ValLiq, delt, riskinit, riskfreeinit);
            acces.DeleteCompo(DateTime.Now.Date.AddHours(1), new DateTime(2016, 5, 29));

            

            //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment


            //Préparation du calcul des valeurs
            DateTime previousDate = DateDeb;

            DateTime LastTimeBD = new DateTime(1, 1, 1);
            spot = acces.getLastSpot(ref LastTimeBD);
            int taille = ((((DateFin.Date - DateDeb.Date).Days) / pas) + 1);
            //Calcul des valeurs de marché durant la couverture
            int taille_bis = (DateFin.Date - DateDeb.Date).Days;
            double[] futurSpot = new double[4];
            double[] PathSim = new Double[4 * (taille_bis+1)];

            Chart1.Titles.Add("Composition du portefeuille de couverture");
            Chart1.Legends.Add(new Legend("Valeur du portefeuille"));
            Chart1.Legends.Add(new Legend("Valeur du produit"));
            Chart1.Series[0].Name = "Valeur du portefeuille";
            Chart1.Series[1].Name = "Valeur du produit";

            past[0] = acces.getAssetSpot("FTSE", DateDeb, Datee, pas);
            past[1] = acces.getAssetSpot("S&P", DateDeb, Datee, pas);
            past[2] = acces.getAssetSpot("NIKKEI", DateDeb, Datee, pas);
            past[3] = acces.getAssetSpot("EUROSTOXX", DateDeb, Datee,pas);
            double[] realPast = new double[past[0].Length * 4];
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < past[0].Length; j++)
                {
                    realPast[i * past[0].Length + j] = past[i][j];
                }
            }

            double risk = acces.getCurrentRisk(previousDate);
            double riskfree = acces.getCurrentRiskFree(previousDate);
            double[] tmpDelta = acces.getDelta(previousDate);
            DateTime lastDatCouv = new DateTime(1,1,1);
            acces.getLastCompoDate(ref lastDatCouv);
            //Traitement du cas où la date de départ est celle de début du produit
            if (lastDatCouv.AddDays(pas) == DateTime.Now.Date)
            {
               // wrap.computePortfolio(past[0].Length, 4, 30, 1000, (int)rebalancement, ((Maturity.Date - Datee.Date).Days) / 365.0, (DateTime.Now - Datee).Days / 365.0, 0.05, sigma, rho, coeff, realPast);
               // acces.Insert(DateDeb, wrap.getPrice(), wrap.getDelta(), wrap.getRiskFree(), wrap.getRisk());
                previousDate = DateDeb;

                String[,] values = acces.extractData(Datee, DateTime.Now.AddDays(pas));
                for (int i = 0; i < values.Length / 3; ++i)
                {
                    Chart1.Series[0].Points.AddXY(DateTime.Parse(values[2, i]), double.Parse(values[1, i]));
                    Chart1.Series[1].Points.AddXY(DateTime.Parse(values[2, i]), double.Parse(values[0, i]));
                    Chart1.Series[0].Points[i].ToolTip = string.Format("Date = {0}, Valeur Portefeuille = {1}", values[2, i], Math.Round(double.Parse(values[1, i]), 2));
                    Chart1.Series[1].Points[i].ToolTip = string.Format("Date = {0}, Valeur Liquidative = {1}", values[2, i], Math.Round(double.Parse(values[0, i]), 2));
                }
            }
            else
            {
                String[,] values = acces.extractData(Datee, DateTime.Now);
                for (int i = 0; i < values.Length / 3; ++i)
                {
                    Chart1.Series[0].Points.AddXY(DateTime.Parse(values[2, i]), double.Parse(values[1, i]));
                    Chart1.Series[1].Points.AddXY(DateTime.Parse(values[2, i]), double.Parse(values[0, i]));
                    Chart1.Series[0].Points[i].ToolTip = string.Format("Date = {0}, Valeur Portefeuille = {1}", values[2, i], Math.Round(double.Parse(values[1, i]), 2));
                    Chart1.Series[1].Points[i].ToolTip = string.Format("Date = {0}, Valeur Liquidative = {1}", values[2, i], Math.Round(double.Parse(values[0, i]), 2));
                }
            }
            DateTime LastCov = new DateTime(1, 1, 1);
            double[] parts = acces.getLastParts(ref LastCov);
            double[] sp = new double[4];
            sp[0] = acces.getAssetSpot("FTSE", LastCov.AddHours(23), LastCov, 1)[0];
            sp[1] = acces.getAssetSpot("S&P", LastCov.AddHours(23), LastCov, 1)[0];
            sp[2] = acces.getAssetSpot("NIKKEI", LastCov.AddHours(23), LastCov, 1)[0];
            sp[3] = acces.getAssetSpot("EUROSTOXX", LastCov.AddHours(23), LastCov, 1)[0];
            double ValPort = acces.getCurrentRisk(LastCov) + acces.getCurrentRiskFree(LastCov);
            CreateChart(parts,sp);
            BisCreatChart(acces.getAllStackedColumn(pas));

            //Portfolio_value.Text = "0";
            //Product_value.Text = "0";
            //Err_value.Text = "0";
            //Start.Visible = false;
         //   Next_day.Text = "Calcul au jour " + day.ToString();
        }


        private void CreateChart(double[] parts, double[] spot)
        {
            var table = new DataTable();
            table.Columns.Add("Indices", typeof(string));
            table.Columns.Add("Parts", typeof(double));
            table.Columns.Add("Lbl", typeof(string));

            var row = table.NewRow();
            row["Indices"] = "FTSE 100";
            row["Parts"] = Math.Round(parts[0]*spot[0],1) ;
           // row["Lbl"] = (int)parts[0] * spot[0] + "€";
            table.Rows.Add(row);

            row = table.NewRow();
            row["Indices"] = "S&P 500";
            row["Parts"] = Math.Round(parts[1] * spot[1], 1);
           // row["Lbl"] = (int)parts[1] * spot[1] + "€";
            table.Rows.Add(row);

            row = table.NewRow();
            row["Indices"] = "NIKKEI 225";
            row["Parts"] = Math.Round(parts[2] * spot[2], 1);
           // row["Lbl"] = (int)parts[2] * spot[2] + "€";
            table.Rows.Add(row);

            row = table.NewRow();
            row["Indices"] = "EUROSTOXX 50";
            row["Parts"] = Math.Round(parts[3] * spot[3], 1);
           // row["Lbl"] = (int)parts[3] * spot[3] + "€";

            table.Rows.Add(row);
            Chart4.DataSource = table;
            Chart4.DataBind();
        }
        private void BisCreatChart(string[,] info)
        {
            var table = new DataTable();
            table.Columns.Add("Date", typeof(DateTime));
            table.Columns.Add("column1", typeof(double));
            table.Columns.Add("column2", typeof(double));
            table.Columns.Add("column3", typeof(double));
            table.Columns.Add("column4", typeof(double));

            DataRow row = null;
            for (int j = 0; j<info.Length/9; j++){
                row = table.NewRow();
                row["Date"] = DateTime.Parse(info[0,j]);
                row["Column1"] = Math.Abs(double.Parse(info[1,j])*double.Parse(info[5,j]));
                row["Column2"] = Math.Abs(double.Parse(info[2, j]) * double.Parse(info[6, j]));
                row["Column3"] = Math.Abs(double.Parse(info[3, j]) * double.Parse(info[7, j]));
                row["Column4"] = Math.Abs(double.Parse(info[4, j]) * double.Parse(info[8, j]));
                table.Rows.Add(row);
            }
            Chart6.DataSource = table;
            Chart6.DataBind();
        }
    }
}