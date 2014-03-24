using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;
using System.Runtime.InteropServices;

namespace AffichageBD
{
    public class AfficheBD
    {
          /// <summary>
        /// Database context.
        /// </summary>
        private PepsDBDataContext myDbdc;

        private String[] Assets;
        private DateTime[][] Date;
        private double[][] Spots;

        /// <summary>
        /// properties 
        /// </summary>
        public PepsDBDataContext MyDbdc
        {
            get { return myDbdc; }
            set { myDbdc = value; }
        }


        public String[] Asset
        {
            get { return Assets; }
            set { Assets = value; }
        }

        public DateTime[][] Dates
        {
            get { return Date; }
            set { Date = value; }
        }

        public double[][] Spot
        {
            get { return Spots; }
            set { Spots = value; }
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        public AfficheBD()
        {
            // initalizing the database context.
            myDbdc = new PepsDBDataContext();
            Assets = new String[4] { "^STOXX50E", "^FTSE", "^N225", "^GSPC" };
            Date = new DateTime[4][];
            Spots = new double[4][];
            for (int i = 0; i <= 3; ++i)
            {
                String[] Dates = (from nam in myDbdc.PepsDB
                                  where nam.Actif.Equals(this.Assets[i])
                                  select nam.Date).ToArray<String>();
                Date[i] = new DateTime[Dates.Length];
                Spots[i] = new double[Dates.Length];
                DateTime oute;
                for (int j = 0; j < Dates.Length; j++)
                {
                    DateTime.TryParse(Dates[j], out oute);
                    Date[i][j] = oute;
                }
                //getAssetSpot(Assets[i]);
                String[] tmpAssetSpot = (from nam in myDbdc.PepsDB
                                         where nam.Actif.Equals(this.Assets[i])
                                         select nam.Open).ToArray<String>();
                double outer;
                for (int k = 0; k < Date[i].Length; k++)
                {
                    double.TryParse(tmpAssetSpot[k], out outer);
                    Spots[i][k] = outer;
                }
            }
        }



        /// <summary>
        /// retrieve assets name and puts it the name array of the object AssetsInfo.
        /// </summary>
        /// <param name="myAssetInfo">Object containing an array in which we save the assets name.</param>
        /// <param name="selectedAsset">Object containing the name of the assets selected by the user</param>
        /// //Useful to calculate the volatility and correlations
        public void getAssetSpot(String Asset)
        {
            //Erreur de table
            String[] tmpAssetSpot = (from nam in myDbdc.PepsDB
                                     where nam.Actif.Equals(Asset)
                                     select nam.Open).ToArray<String>();
            int indice = 100;
            if (Asset == Assets[0]){indice = 0;}
            else if (Asset == Assets[1]){indice = 1;}
            else if (Asset == Assets[2]){indice = 2;}
            else{indice = 3;}
            double oute;
            for (int i = 0; i < Date[indice].Length; i++)
            {
                double.TryParse(tmpAssetSpot[i], out oute);
                this.Spots[indice][i] = oute;
            }
        }

        public void setCompo(double[] compo, String now)
        {
            Component compon = new Component();
            {
                compon.PartS_P = compo[0].ToString();
                compon.PartFTSE = compo[1].ToString();
                compon.PartEuro = compo[2].ToString();
                compon.PartNikkei = compo[3].ToString();
                compon.Date = now;
            };

            // Add the new object to the Orders collection.
            myDbdc.Component.InsertOnSubmit(compon);

            // Submit the change to the database. 
                myDbdc.SubmitChanges();
        }
    }
}
