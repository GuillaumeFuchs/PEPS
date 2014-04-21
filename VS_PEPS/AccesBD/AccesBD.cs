using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Linq.Expressions;

namespace AccesDB
{
    public class AccesBD
    {

         /// <summary>
        /// Database context.
        /// </summary>
        private PepsDBDataContext myDbdc;
        double[][] Delta;

        /// <summary>
        /// properties 
        /// </summary>
        public PepsDBDataContext MyDbdc
        {
            get { return myDbdc; }
            set { myDbdc = value; }
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        public AccesBD()
        {
            // initalizing the database context.
            myDbdc = new PepsDBDataContext();
        }

        /// <summary>
        /// retrieve assets name and puts it the name array of the object AssetsInfo.
        /// </summary>
        /// <param name="myAssetInfo">Object containing an array in which we save the assets name.</param>
        /// <param name="selectedAsset">Object containing the name of the assets selected by the user</param>
        /// //Useful to calculate the volatility and correlations
        public double[] getAssetSpot(String Asset,DateTime EndDate, DateTime DepDate)
        {
            DateTime end  = EndDate;
            string[] val = null;
            if (Asset.Equals("FTSE")){
                val = (from nam in myDbdc.PepsDB
                                where DepDate <= nam.Date && end >= nam.Date
                                select nam.FTSE).ToArray();

            }
            else if (Asset.Equals("S&P"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       select nam.S_P).ToArray();
            }
            else if (Asset.Equals("NIKKEI"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       select nam.NIKKEI).ToArray();
            }
            else if (Asset.Equals("EUROSTOXX"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       select nam.EUROSTOXX).ToArray();
            }

            double[] result = new double[val.Length];
            for (int j = 0; j < val.Length; j++)
            {
                result[j] = double.Parse(val[j]);
            }
            return result;
        }

        //public double[] getPortfolio()
        //{
        //    String[] tmpPortfolio = (from nam in myDbdc.Component
        //                             select nam.ValPortefeuille).ToArray<String>();

        //    double[] Portfolio = new double[tmpPortfolio.Length];
        //    double oute;
        //    for (int i = 0; i < tmpPortfolio.Length; i++)
        //    {
        //        double.TryParse(tmpPortfolio[i], out oute);
        //        Portfolio[i] = oute;
        //    }
        //    return Portfolio;
        //}

        public double getCurrentRisk(DateTime Date)
        {
            String tmpRisk = (from nam in myDbdc.Component
                                    where nam.Date.Equals(Date)
                                     select nam.Valrisk).ToString();

            try
            {
                return double.Parse(tmpRisk);
            }
            catch
            {
                return 0;
            }
        }

        public double getCurrentRiskFree(DateTime Date)
        {
            String tmpRiskfree = (from nam in myDbdc.Component
                                    where nam.Date.Equals(Date)
                                select nam.Valriskfree).ToString();

            try
            {
                return double.Parse(tmpRiskfree);
            }
            catch
            {
                return 0;
            }
        }

        public double[] getDelta(DateTime Date)
        {
            double[] Delta = new double[4];
            //Delat du FTSE
            String tmpDeltaFTSE = (from nam in myDbdc.Component
                                     where nam.Date.Equals(Date)
                                     select nam.DeltaFTSE).ToString();
            try
            {
                Delta[0] = double.Parse(tmpDeltaFTSE);
            }
            catch
            {
                Delta[0] = 0;
            }
            //Delta du S&P
            String tmpDeltaSP = (from nam in myDbdc.Component
                                 where nam.Date.Equals(Date)
                                     select nam.DeltaS_P).ToString();

            try
            {
                Delta[1] = double.Parse(tmpDeltaSP);
            }
            catch
            {
                Delta[1] = 0;
            }
            //Delta du Nikkei
            String tmpDeltaNikkei = (from nam in myDbdc.Component
                                       where nam.Date.Equals(Date)
                                   select nam.DeltaNikkei).ToString();

            try
            {
                Delta[2] = double.Parse(tmpDeltaNikkei);
            }
            catch
            {
                Delta[2] = 0;
            }
            //Delta du Eurostoxx
            String tmpDeltaEuro = (from nam in myDbdc.Component
                                   where nam.Date.Equals(Date)
                                       select nam.DeltaEuro).ToString();
            try
            {
                Delta[3] = double.Parse(tmpDeltaEuro);
            }
            catch
            {
                Delta[3] = 0;
            }
            return Delta;
        }

        public void Insert(DateTime Datee, double ValLiq, double[] delta, double Valriskfree, double Valrisk)
        {
            Backtest ord = new Backtest
            {
                Date = Datee,
                DeltaFTSE = delta[0].ToString(),
                DeltaS_P = delta[1].ToString(),
                DeltaNikkei = delta[2].ToString(),
                DeltaEuro = delta[3].ToString(),
                ValLiquidative = ValLiq.ToString(),
                Valrisk = Valrisk.ToString(),
                Valriskfree = Valriskfree.ToString(),
                ValPortefeuille = (Valrisk + Valriskfree).ToString()
            };
            myDbdc.Backtest.InsertOnSubmit(ord);
            try
            {
                myDbdc.SubmitChanges();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
                
        }
    }
}
