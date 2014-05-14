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
        public double[] getAssetSpot(String Asset,DateTime EndDate, DateTime DepDate, int pas)
        {
            DateTime end  = EndDate;
            string[] val = null;
            if (Asset.Equals("FTSE")){
                val = (from nam in myDbdc.PepsDB
                                where DepDate <= nam.Date && end >= nam.Date
                                orderby nam.Date
                                select nam.FTSE).ToArray();

            }
            else if (Asset.Equals("S&P"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       orderby nam.Date
                       select nam.S_P).ToArray();
            }
            else if (Asset.Equals("NIKKEI"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       orderby nam.Date
                       select nam.NIKKEI).ToArray();
            }
            else if (Asset.Equals("EUROSTOXX"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       orderby nam.Date
                       select nam.EUROSTOXX).ToArray();
            }
            else if (Asset.Equals("Eur/JPY"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       orderby nam.Date
                       select nam.Eur_JPY).ToArray();
            }
            else if (Asset.Equals("Eur/USD"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       orderby nam.Date
                       select nam.Eur_USD).ToArray();
            }
            else if (Asset.Equals("Eur/GBP"))
            {
                val = (from nam in myDbdc.PepsDB
                       where DepDate <= nam.Date && end >= nam.Date
                       orderby nam.Date
                       select nam.Eur_GBP).ToArray();
            }
            int borne;
            if (pas == 1)
            {
                borne = val.Length;
            }
            else
            {
                borne = 1 + val.Length / pas;
            }
            double[] result = new double[borne];
            for (int j = 0; j < borne; j++)
            {
                //result[j] = double.Parse(val[j]);
                result[j] = double.Parse(val[j * pas]);
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
            string[] tmpRisk = (from nam in myDbdc.Component
                                where nam.Date >= Date.AddDays(-10) && nam.Date <= DateTime.Now
                                    orderby nam.Date
                                     select nam.Valrisk).ToArray();

            try
            {
                return double.Parse(tmpRisk[tmpRisk.Length-1]);
            }
            catch
            {
                return 0;
            }
        }

        public double getCurrentValLiq(DateTime Date)
        {
            string[] tmpRisk = (from nam in myDbdc.Component
                                where nam.Date >= Date.AddDays(-10) && nam.Date <= Date
                                orderby nam.Date
                                select nam.ValLiquidative).ToArray();

            try
            {
                return double.Parse(tmpRisk[tmpRisk.Length - 1]);
            }
            catch
            {
                return 0;
            }
        }

        public double getCurrentRiskFree(DateTime Datee)
        {
            string[] tmpRiskfree = (from nam in myDbdc.Component
                                    where nam.Date >= Datee.AddDays(-10) && nam.Date <= DateTime.Now
                                    orderby nam.Date
                                select nam.Valriskfree).ToArray();

            try
            {
                return double.Parse(tmpRiskfree[tmpRiskfree.Length-1]);
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
            String[] tmpDeltaFTSE = (from nam in myDbdc.Component
                                     where nam.Date >= Date.AddDays(-10) && nam.Date <= DateTime.Now
                                     orderby nam.Date
                                     select nam.DeltaFTSE).ToArray();
            try
            {
                Delta[0] = double.Parse(tmpDeltaFTSE[tmpDeltaFTSE.Length-1]);
            }
            catch
            {
                Delta[0] = 0;
            }
            //Delta du S&P
            String[] tmpDeltaSP = (from nam in myDbdc.Component
                                   where nam.Date >= Date.AddDays(-10) && nam.Date <= DateTime.Now
                                   orderby nam.Date
                                     select nam.DeltaS_P).ToArray();

            try
            {
                Delta[1] = double.Parse(tmpDeltaSP[tmpDeltaSP.Length - 1]);
            }
            catch
            {
                Delta[1] = 0;
            }
            //Delta du Nikkei
            String[] tmpDeltaNikkei = (from nam in myDbdc.Component
                                       where nam.Date >= Date.AddDays(-10) && nam.Date <= DateTime.Now
                                       orderby nam.Date
                                   select nam.DeltaNikkei).ToArray();

            try
            {
                Delta[2] = double.Parse(tmpDeltaNikkei[tmpDeltaNikkei.Length - 1]);
            }
            catch
            {
                Delta[2] = 0;
            }
            //Delta du Eurostoxx
            String[] tmpDeltaEuro = (from nam in myDbdc.Component
                                     where nam.Date >= Date.AddDays(-10) && nam.Date <= DateTime.Now
                                     orderby nam.Date
                                       select nam.DeltaEuro).ToArray();
            try
            {
                Delta[3] = double.Parse(tmpDeltaEuro[tmpDeltaEuro.Length - 1]);
            }
            catch
            {
                Delta[3] = 0;
            }
            return Delta;
        }

        public void Insert(DateTime Datee, double[] spot)
        {
            PepsDB ord = new PepsDB
            {
                Date = Datee,
                FTSE = spot[0].ToString(),
                S_P = spot[1].ToString(),
                NIKKEI = spot[2].ToString(),
                EUROSTOXX = spot[3].ToString(),
            };
            myDbdc.PepsDB.InsertOnSubmit(ord);
            try
            {
                myDbdc.SubmitChanges();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }


        public void Insert(DateTime Datee, double ValLiq, double[] delta, double Valriskfree, double Valrisk)
        {
            DateTime tmp = Datee;
            var val = (from nam in myDbdc.InfoProd select nam).ToArray();
            if (val.Length == 0)
            {
                //Afficher une popup
            }
            else
            {
                Component ord = new Component
                {
                    Date = tmp,
                    DeltaFTSE = delta[0].ToString(),
                    DeltaS_P = delta[1].ToString(),
                    DeltaNikkei = delta[2].ToString(),
                    DeltaEuro = delta[3].ToString(),
                    PartFTSE = (delta[0]*int.Parse(val[0].NbPartAchetes)).ToString(),
                    PartS_P = (delta[1]*int.Parse(val[0].NbPartAchetes)).ToString(),
                    PartNikkei = (delta[2]*int.Parse(val[0].NbPartAchetes)).ToString(),
                    PartEuro = (delta[3]*int.Parse(val[0].NbPartAchetes)).ToString(),
                    ValLiquidative = ValLiq.ToString(),
                    Valrisk = Valrisk.ToString(),
                    Valriskfree = Valriskfree.ToString(),
                    ValPortefeuille = (Valrisk + Valriskfree).ToString()
                };
                myDbdc.Component.InsertOnSubmit(ord);
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

        public double[] getLastSpot(ref DateTime DateFinBD)
        {
            double[] spot = new double[4];
            var val = (from nam in myDbdc.PepsDB
                       where nam.Date > DateTime.Now.AddDays(-10)
                       orderby nam.Date
                       select new { nam.FTSE, nam.S_P, nam.NIKKEI, nam.EUROSTOXX, nam.Date }).ToArray();
            spot[0] = double.Parse(val[val.Length - 1].FTSE);
            spot[1] = double.Parse(val[val.Length - 1].S_P);
            spot[2] = double.Parse(val[val.Length - 1].NIKKEI);
            spot[3] = double.Parse(val[val.Length - 1].EUROSTOXX);
            DateFinBD = val[val.Length - 1].Date;
            return spot;

        }

        public void InsertInfoProd(String NomProduit, int NBPart, int ValNom)
        {
            var val = (from nam in myDbdc.InfoProd select nam).ToArray();
            if (val.Length == 0)
            {
                InfoProd inf = new InfoProd
                {
                    NomProd = NomProduit,
                    NbPartAchetes = NBPart.ToString(),
                    ValNominale = ValNom.ToString()
                };
                myDbdc.InfoProd.InsertOnSubmit(inf);
            }
            else
            {
                foreach (InfoProd inf in val)
                {
                    inf.NomProd = NomProduit;
                    inf.NbPartAchetes = NBPart.ToString();
                    inf.ValNominale = ValNom.ToString();
                }
            }
            try
            {
                myDbdc.SubmitChanges();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                // Provide for exceptions.
            }
        }

        public int GetInfoProd(ref String NomProduit, ref int NBPart, ref int ValNom)
        {
            var val = (from nam in myDbdc.InfoProd select nam).ToArray();
            if (val.Length == 0)
            {
                return 0;
            }
            else
            {
                foreach (InfoProd inf in val)
                {
                    NomProduit = inf.NomProd;
                    NBPart = int.Parse(inf.NbPartAchetes);
                    ValNom = int.Parse(inf.ValNominale);
                }
                return 1;
            }
        }

        public int DeleteCompo(DateTime Dep, DateTime Fin)
        {
            var val = (from nam in myDbdc.Component
                       where Dep <= nam.Date && Fin >= nam.Date
                       select nam).ToArray();
            if (val.Length != 0)
            {
                foreach (Component comp in val)
                {
                    myDbdc.Component.DeleteOnSubmit(comp);
                }
                try
                {
                    myDbdc.SubmitChanges();
                    return 0;
                }
                catch
                {
                    return 1;
                }
            }
            else
            {
                return 2;
            }

        }

        public int DeletePeps(DateTime Dep, DateTime Fin)
        {
            var val = (from nam in myDbdc.PepsDB
                       where Dep <= nam.Date && Fin >= nam.Date
                       select nam).ToArray();
            if (val.Length != 0)
            {
                foreach (PepsDB comp in val)
                {
                    myDbdc.PepsDB.DeleteOnSubmit(comp);
                }
                try
                {
                    myDbdc.SubmitChanges();
                    return 0;
                }
                catch
                {
                    return 1;
                }
            }
            else
            {
                return 2;
            }

        }

        public String[,] extractData(DateTime Deb, DateTime Fin)
        {
            var val = (from nam in myDbdc.Component where nam.Date>=Deb && nam.Date<=Fin orderby nam.Date select nam).ToArray();
            string[,] values = new String[3,val.Length];
            int cpt = 0;
            foreach (Component comp in val)
            {
                values[0, cpt] = comp.ValLiquidative;
                values[1, cpt] = comp.ValPortefeuille;
                values[2, cpt] = comp.Date.ToString();
                cpt++;
            }
            return values;

        }

        public Dictionary<string,string> getLastCouv(DateTime Dat)
        {
            var val = (from nam in myDbdc.Component orderby nam.Date select nam).ToArray();
            Dictionary<string,string> dic  = new Dictionary<string,string>(14);
            if (val.Length != 0)
            {
                dic["ValLiq"] = val[val.Length - 1].ValLiquidative;
                dic["risk"] = val[val.Length - 1].Valrisk;
                dic["riskfree"] = val[val.Length - 1].Valriskfree;
                dic["deltaFTSE"] = val[val.Length - 1].DeltaFTSE;
                dic["deltaS_P"] = val[val.Length - 1].DeltaS_P;
                dic["deltaNIKKEI"] = val[val.Length - 1].DeltaNikkei;
                dic["deltaEURO"] = val[val.Length - 1].DeltaEuro;
            }
            return dic;
        }

        public double[] getLastParts(ref DateTime dat)
        {
            var val = (from nam in myDbdc.Component orderby nam.Date select nam).ToArray();
            if (val.Length != 0)
            {
                double[] parts = new double[4];
                parts[0] = double.Parse(val[val.Length - 1].PartFTSE);
                parts[1] = double.Parse(val[val.Length - 1].PartS_P);
                parts[2] = double.Parse(val[val.Length - 1].PartNikkei);
                parts[3] = double.Parse(val[val.Length - 1].PartEuro);
                dat = val[val.Length - 1].Date;
                return parts;
            }
            return null;
        }

        public string[,] getAllStackedColumn(int pas)
        {
            DateTime dat = new DateTime(2010, 4, 29);
            var val = (from nam in myDbdc.Component where nam.Date >= dat orderby nam.Date select nam).ToArray();
            var val2 = (from nam in myDbdc.PepsDB where nam.Date >= dat orderby nam.Date select nam).ToArray();
            int taille  = val.Length;
            if (taille != 0)
            {
                String[,] dic  = new String[9,taille];
                int cpt = 0;
                foreach (Component comp in val)
                {
                    dic[0, cpt] = comp.Date.Date.ToString();
                    dic[1, cpt] = comp.PartFTSE;
                    dic[2, cpt] = comp.PartS_P;
                    dic[3, cpt] = comp.PartNikkei;
                    dic[4, cpt] = comp.PartEuro;
                    cpt++;
                }
                for (int i = 0; i < val2.Length/pas+1; i++)
                {
                    if (i == 184)
                    {
                        int a;
                    }

                    dic[5, i] = val2[i * pas].FTSE;
                    dic[6, i] = val2[i * pas].S_P;
                    dic[7, i] = val2[i * pas].NIKKEI;
                    dic[8, i] = val2[i * pas].EUROSTOXX;
                }
                return dic;
            }
            return null;
        }

        public void getLastCompoDate(ref DateTime dat)
        {
            var val = (from nam in myDbdc.Component orderby nam.Date select nam.Date).ToArray();
            dat = val[val.Length - 1].Date;
        }

        public void getLastPepDate(ref DateTime LastDat)
        {
            try
            {
                var val = (from nam in myDbdc.PepsDB orderby nam.Date select nam.Date).ToArray();
                if (val.Length != 0)
                {
                    LastDat = val[val.Length - 1].AddDays(-7).Date;
                }
                else
                {
                    LastDat = new DateTime(1999, 1, 4);
                }
            }
            catch
            {
                LastDat = new DateTime(1999, 1, 4);
            }
        }
    }
}
