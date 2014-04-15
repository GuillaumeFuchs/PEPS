using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
        public double[] getAssetSpot(String Asset, int DaysNumber)
        {
            //Erreur de table
            String[] tmpAssetSpot = (from nam in myDbdc.PepsDB
                                     where nam.Actif.Equals(Asset)
                                     select nam.Open).ToArray<String>();

            double[] AssetSpot = new double[DaysNumber];
            double oute;
            for (int i = 0; i < DaysNumber; i++)
            {
                double.TryParse(tmpAssetSpot[i], out oute);
                AssetSpot[i] = oute;
            }
            return AssetSpot;
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

        public double getCurrentRisk()
        {
            String[] tmpRisk = (from nam in myDbdc.Component
                                     select nam.Valrisk).ToArray<String>();

            return double.Parse(tmpRisk[tmpRisk.Length - 1]);
        }

        public double getCurrentRiskFree()
        {
            String[] tmpRiskfree = (from nam in myDbdc.Component
                                select nam.Valriskfree).ToArray<String>();

            return double.Parse(tmpRiskfree[tmpRiskfree.Length - 1]);
        }

        public double[][] getDelta()
        {
            double[][] Delta = new double[4][];
            //Delat du FTSE
            String[] tmpDeltaFTSE = (from nam in myDbdc.Component
                                     select nam.DeltaFTSE).ToArray<String>();

            Delta[0] = new double[tmpDeltaFTSE.Length];
            double oute;
            for (int i = 0; i < tmpDeltaFTSE.Length; i++)
            {
                double.TryParse(tmpDeltaFTSE[i], out oute);
                Delta[0][i] = oute;
            }
            //Delta du S&P
            String[] tmpDeltaSP = (from nam in myDbdc.Component
                                     select nam.DeltaS_P).ToArray<String>();

            Delta[1] = new double[tmpDeltaSP.Length];
            for (int i = 0; i < tmpDeltaSP.Length; i++)
            {
                double.TryParse(tmpDeltaSP[i], out oute);
                Delta[1][i] = oute;
            }
            //Delta du Nikkei
            String[] tmpDeltaNikkei = (from nam in myDbdc.Component
                                   select nam.DeltaNikkei).ToArray<String>();

            Delta[2] = new double[tmpDeltaNikkei.Length];
            for (int i = 0; i < tmpDeltaNikkei.Length; i++)
            {
                double.TryParse(tmpDeltaNikkei[i], out oute);
                Delta[2][i] = oute;
            }
            //Delta du Eurostoxx
            String[] tmpDeltaEuro = (from nam in myDbdc.Component
                                       select nam.DeltaEuro).ToArray<String>();

            Delta[3] = new double[tmpDeltaEuro.Length];
            for (int i = 0; i < tmpDeltaEuro.Length; i++)
            {
                double.TryParse(tmpDeltaEuro[i], out oute);
                Delta[3][i] = oute;
            }
            return Delta;
        }

        public double[] getPast(String Asset, DateTime DateDep, DateTime DateFin)
        {
            //Erreur de table
            String[] tmpAssetSpot = (from nam in myDbdc.PepsDB
                                     where nam.Actif.Equals(Asset) && DateTime.Parse(nam.Date) <= DateFin && DateTime.Parse(nam.Date) >= DateDep
                                     select nam.Open).ToArray<String>();

            double[] AssetSpot = new double[tmpAssetSpot.Length];
            double oute;
            for (int i = 0; i < tmpAssetSpot.Length; i++)
            {
                double.TryParse(tmpAssetSpot[i], out oute);
                AssetSpot[i] = oute;
            }
            return AssetSpot;
        }
    }
}
