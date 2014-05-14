using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AccesDB;

namespace Parameters
{
    public class ComputeParam
    {

        private AccesDB.AccesBD data;

        private string[] assets;

        private string[] assetsChange;

        private double[] mean;

        private double[] meanChange;

        private double[] volatility;

        private double[] volatilityChange;

        private double[,] corel;

        private double[,] corelChange;


        public string[] Assets
        {
            get { return assets; }
            set { assets = value; }
        }

        public string[] AssetsChange
        {
            get { return assetsChange; }
            set { assetsChange = value; }
        }

        public double[] VolatilityChange
        {
            get { return volatilityChange; }
            set { volatilityChange = value; }
        }

        public double[,] CorelChange
        {
            get { return corelChange; }
            set { corelChange = value; }
        }

        public double[] Mean
        {
            get { return mean; }
            set { mean = value; }
        }

        public double[] MeanChange
        {
            get { return meanChange; }
            set { meanChange = value; }
        }

        public double[] Volatility
        {
            get { return volatility; }
            set { volatility = value; }
        }

        public double[,] Corel
        {
            get { return corel; }
            set { corel = value; }
        }

        public ComputeParam()
        {
            data = new AccesDB.AccesBD();
            Assets = new String[4] { "FTSE", "S&P", "NIKKEI", "EUROSTOXX"};
            AssetsChange = new String[3] { "Eur/JPY", "Eur/USD", "Eur/GBP" }; 
            mean = new double[4];
            meanChange = new double[3];
            Volatility = new double[4];
            VolatilityChange = new double[3];
            corel = new double[4, 4];
            CorelChange = new double[3, 3];
        }

        //test bis
        public void calculVolat(int index, int DaysNumber, DateTime DepDate)
        {
            double mean = 0;
            double mean2 = 0;
            double[] Spots = data.getAssetSpot(Assets[index], DepDate.AddDays(DaysNumber), DepDate,1);
            double newe, old;
            int cpt = 0;
            int ind = 0;
            for (int i = 1; i < Spots.Length; i++)
            {
                ind = i;
                cpt++;
                //Gestion naive des erreurs, attention si il manque plus de cotations
                newe = Spots[i];
                old = Spots[i - 1];
                while (Spots[ind] == 0 && ind < Spots.Length - 1)
                {
                    newe = Spots[ind + 1];
                    ind++;
                }
                ind = i;
                while (Spots[ind - 1] == 0 && ind > 1)
                {
                    old = Spots[ind - 2];
                    ind--;
                }
                if (newe != 0 && old != 0)
                {
                    mean += (newe - old) / old;
                    mean2 += ((newe - old) / old) * ((newe - old) / old);
                }
            }
            
            mean /= cpt;
            this.mean[index] = mean;
            mean *= mean;
            mean /= cpt-1;
            mean2 /= cpt - 1;
            this.volatility[index] = ((Math.Sqrt(mean2-mean) * Math.Sqrt(252)));
        }

        public void calculVolatChange(int index, int DaysNumber, DateTime DepDate)
        {
            double mean = 0;
            double mean2 = 0;
            double[] Spots = data.getAssetSpot(AssetsChange[index], DepDate.AddDays(DaysNumber), DepDate,1);
            double newe, old;
            int cpt = 0;
            int ind = 0;
            for (int i = 1; i < Spots.Length; i++)
            {
                ind = i;
                cpt++;
                //Gestion naive des erreurs, attention si il manque plus de cotations
                newe = Spots[i];
                old = Spots[i - 1];
                while (Spots[ind] == 0 && ind < Spots.Length - 1)
                {
                    newe = Spots[ind + 1];
                    ind++;
                }
                ind = i;
                while (Spots[ind - 1] == 0 && ind > 1)
                {
                    old = Spots[ind - 2];
                    ind--;
                }
                if (newe != 0 && old != 0)
                {
                    mean += (newe - old) / old;
                    mean2 += ((newe - old) / old) * ((newe - old) / old);
                }
            }

            mean /= cpt;
            this.meanChange[index] = mean;
            mean *= mean;
            mean /= cpt - 1;
            mean2 /= cpt - 1;
            this.volatilityChange[index] = ((Math.Sqrt(mean2 - mean) * Math.Sqrt(252)));
        }

        public void calculSpeCorel(int index1, int index2, int DaysNumber, DateTime DepDate)
        {
            double meanUn = this.mean[index1];
            double meanDeux = this.mean[index2]; 
            double[] SpotsUn = data.getAssetSpot(Assets[index1], DepDate.AddDays(DaysNumber), DepDate,1);
            double[] SpotsDeux = data.getAssetSpot(Assets[index2], DepDate.AddDays(DaysNumber), DepDate,1);
            double correlNum = 0;
            double correlDenomUn = 0;
            double correlDenomDeux = 0;
            double rend1 = 0;
            double rend2 = 0;
            double newe1,newe2, old1, old2;
            int cpt = 0;
            int ind;
            for (int i = 1; i < SpotsUn.Length; i++)
            {
                ind = i;
                cpt++;
                newe1 = SpotsUn[i];
                newe2 = SpotsDeux[i];
                old1 = SpotsUn[i - 1];
                old2 = SpotsDeux[i - 1];
                while (SpotsUn[ind] == 0 && ind < SpotsUn.Length - 1)
                {
                    newe1 = SpotsUn[ind + 1];
                    ind++;
                }
                ind = i;
                while (SpotsDeux[ind] == 0 && ind < SpotsDeux.Length - 1)
                {
                    newe2 = SpotsDeux[ind + 1];
                    ind++;
                }
                ind = i;
                while (SpotsUn[ind - 1] == 0 && ind > 1)
                {
                    old1 = SpotsUn[ind - 2];
                    ind--;
                }
                ind = i;
                while (SpotsDeux[ind - 1] == 0 && ind > 1)
                {
                    old2 = SpotsDeux[ind - 2];
                    ind--;
                }
                if (newe1 == 0 || old1 == 0)
                {
                    rend1 = 0;
                }
                else
                {
                    rend1 = ((newe1 - old1) / old1) - meanUn;
                }
                if (newe2 == 0 || old2 == 0)
                {
                    rend2 = 0;
                }
                else
                {
                    rend2 = ((newe2 - old2) / old2) - meanDeux;
                }
                correlNum += (rend1* rend2);
                correlDenomUn += Math.Pow(rend1, 2);
                correlDenomDeux += Math.Pow(rend2, 2);
            }
            correlNum /= cpt;
            correlDenomUn = Math.Sqrt(correlDenomUn/cpt);
            correlDenomDeux = Math.Sqrt(correlDenomDeux/cpt);

            double corelation = correlNum/(correlDenomUn*correlDenomDeux);
            this.corel[index1, index2] = corelation;
            this.corel[index2, index1] = corelation;
        }

        public void calculSpeCorelChange(int index1, int index2, int DaysNumber, DateTime DepDate)
        {
            double meanUn = this.mean[index1];
            double meanDeux = this.mean[index2];
            double[] SpotsUn = data.getAssetSpot(AssetsChange[index1], DepDate.AddDays(DaysNumber), DepDate,1);
            double[] SpotsDeux = data.getAssetSpot(AssetsChange[index2], DepDate.AddDays(DaysNumber), DepDate,1);
            double correlNum = 0;
            double correlDenomUn = 0;
            double correlDenomDeux = 0;
            double rend1 = 0;
            double rend2 = 0;
            double newe1, newe2, old1, old2;
            int cpt = 0;
            int ind;
            for (int i = 1; i < SpotsUn.Length; i++)
            {
                ind = i;
                cpt++;
                newe1 = SpotsUn[i];
                newe2 = SpotsDeux[i];
                old1 = SpotsUn[i - 1];
                old2 = SpotsDeux[i - 1];
                while (SpotsUn[ind] == 0 && ind < SpotsUn.Length - 1)
                {
                    newe1 = SpotsUn[ind + 1];
                    ind++;
                }
                ind = i;
                while (SpotsDeux[ind] == 0 && ind < SpotsDeux.Length - 1)
                {
                    newe2 = SpotsDeux[ind + 1];
                    ind++;
                }
                ind = i;
                while (SpotsUn[ind - 1] == 0 && ind > 1)
                {
                    old1 = SpotsUn[ind - 2];
                    ind--;
                }
                ind = i;
                while (SpotsDeux[ind - 1] == 0 && ind > 1)
                {
                    old2 = SpotsDeux[ind - 2];
                    ind--;
                }
                if (newe1 == 0 || old1 == 0)
                {
                    rend1 = 0;
                }
                else
                {
                    rend1 = ((newe1 - old1) / old1) - meanUn;
                }
                if (newe2 == 0 || old2 == 0)
                {
                    rend2 = 0;
                }
                else
                {
                    rend2 = ((newe2 - old2) / old2) - meanDeux;
                }
                correlNum += (rend1 * rend2);
                correlDenomUn += Math.Pow(rend1, 2);
                correlDenomDeux += Math.Pow(rend2, 2);
            }
            correlNum /= cpt;
            correlDenomUn = Math.Sqrt(correlDenomUn / cpt);
            correlDenomDeux = Math.Sqrt(correlDenomDeux / cpt);

            double corelation = correlNum / (correlDenomUn * correlDenomDeux);
            this.corelChange[index1, index2] = corelation;
            this.corelChange[index2, index1] = corelation;
        }

        public void param(int DaysNumber, DateTime DepDate)
        {
            for (int i = 0; i < 4; i++)
            {
               calculVolat(i, DaysNumber, DepDate);
               if (i < 3)
               {
                   calculVolatChange(i, DaysNumber, DepDate);
               }
            }
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (j != k)
                    {
                        calculSpeCorel(j,k, DaysNumber, DepDate);
                        if (j < 3 && k < 3)
                        {
                            calculSpeCorelChange(j, k, DaysNumber, DepDate);
                        }
                    }
                    else
                    {
                        this.corel[j, j] = 1;
                        if (j < 3)
                        {
                            this.corelChange[j, j] = 1;
                        }
                    }
                }
            }
        }
    }
}
