using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;
using System.Runtime.InteropServices;

namespace DBPrinting
{
    public class Printing
    {
        /// <summary>
        /// Database context.
        /// </summary>
        private PepsDBDataContext myDbdc;

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
        public Printing()
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
                                     where nam.Date.Equals(Asset)
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




    }
}
