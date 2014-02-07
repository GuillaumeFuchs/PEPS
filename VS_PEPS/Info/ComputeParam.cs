using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AffichageBD;

namespace Parameters
{
    public class ComputeParam
    {

        private AffichageBD.AffichageBD data;

        private string[] assets;

        private double[] mean;

        private double[] volatility;

        private double[,] corel;


        public string[] Assets
        {
            get { return assets; }
            set { assets = value; }
        }

        public double[] Mean
        {
            get { return mean; }
            set { mean = value; }
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
            data = new AffichageBD.AffichageBD();
            Assets = new String[4] { "^STOXX50E", "^FTSE", "^N225", "^GSPC" };
            mean = new double[4];
            volatility = new double[4];
            corel = new double[4, 4];
            //for (int i = 0; i < 4; i++)
            //{
            //    corel[i, i] = 1;
            //}
        }


        //standard deviation calculating with rendement*sqrt(252) nb de cote annuel
        public void calculSpeVolat(int index, int DaysNumber)
        {
            double mean = 0;
            double variance  = 0;
            double[] Spots = data.getAssetSpot(Assets[index], DaysNumber);
            for (int i = 0; i < Spots.Length; i++)
            {
                mean += Spots[i];
            }
            mean /= Spots.Length;
            this.mean[index] = mean;

            for (int i = 0; i < Spots.Length; i++)
            {
                variance += Math.Pow((Spots[i] - mean), 2);
            }
            this.volatility[index] = ((Math.Sqrt((double)(variance / Spots.Length)))/mean)*Math.Sqrt(254/DaysNumber);
        }


        //standard deviation calculating with rendement*sqrt(252) nb de cote annuel
        public void testVolat(int index, int DaysNumber)
        {
            double mean = 0;
            double mean2 = 0;
            double variance = 0;
            double[] Spots = data.getAssetSpot(Assets[index], DaysNumber);
            for (int i = 1; i < Spots.Length; i++)
            {
                mean += (Spots[i] - Spots[i - 1]) / Spots[i - 1];
                mean2 += Spots[i];
            }
            mean /= Spots.Length-1;
            mean2 += Spots[0];
            mean2 /= Spots.Length;
            this.mean[index] = mean2;

            for (int i = 1; i < Spots.Length; i++)
            {
                variance += Math.Pow(((Spots[i] - Spots[i - 1]) / Spots[i - 1] - mean), 2);
            }
            this.volatility[index] = ((Math.Sqrt((double)(variance / (Spots.Length-1))))) * Math.Sqrt(252);
        }

        //test bis
        public void calculVolat(int index, int DaysNumber)
        {
            double mean = 0;
            double mean2 = 0;
            double[] Spots = data.getAssetSpot(Assets[index], DaysNumber);
            for (int i = 1; i < Spots.Length; i++)
            {
                mean += (Spots[i] - Spots[i - 1]) / Spots[i - 1];
                mean2 += ((Spots[i] - Spots[i - 1]) / Spots[i - 1]) * ((Spots[i] - Spots[i - 1]) / Spots[i - 1]);
            }
            mean *= mean;
            mean /= Spots.Length-1;
            mean /= Spots.Length-2;
            mean2 /= Spots.Length - 2;
            this.mean[index] = mean;
            this.volatility[index] = ((Math.Sqrt(mean2-mean) * Math.Sqrt(252)));
        }

        public void calculSpeCorel(int index1, int index2, int DaysNumber)
        {
            double meanUn = this.mean[index1];
            double meanDeux = this.mean[index2]; 
            double[] SpotsUn = data.getAssetSpot(Assets[index1], DaysNumber);
            double[] SpotsDeux = data.getAssetSpot(Assets[index2], DaysNumber);
            double correlNum = 0;
            double correlDenomUn = 0;
            double correlDenomDeux = 0;

            for (int i = 0; i < SpotsUn.Length; i++)
            {
                correlNum += (SpotsUn[i] - meanUn) * (SpotsDeux[i] - meanDeux);
                correlDenomUn += Math.Pow((SpotsUn[i] - meanUn), 2);
                correlDenomDeux += Math.Pow((SpotsDeux[i] - meanDeux), 2);
            }
            correlDenomUn = Math.Sqrt(correlDenomUn);
            correlDenomDeux = Math.Sqrt(correlDenomDeux);

            double corelation = correlNum/(correlDenomUn*correlDenomDeux);
            this.corel[index1, index2] = corelation;
            this.corel[index2, index1] = corelation;
        }

        public void param(int DaysNumber)
        {
            for (int i = 0; i < 4; i++)
            {
               calculVolat(i, DaysNumber);
            }
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (j != k)
                    {
                        calculSpeCorel(j,k, DaysNumber);
                    }
                    else
                    {
                        this.corel[j, j] = 1;
                    }
                }
            }
        }
    }
}
