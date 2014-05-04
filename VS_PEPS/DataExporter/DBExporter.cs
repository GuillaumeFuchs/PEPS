using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using APIFiMag;
using APIFiMag.Exporter;
using APIFiMag.Datas;

namespace DataExporter
{
    public class DBExporter
    {
        private ExportDataContext db;


        public DBExporter()
        {
            db = new ExportDataContext();
        }

        public void Export(Data d, Data change, DateTime DebParam, DateTime FinParam)
        {
            //Récupération de la dernière date présente dans la base
            var Actuel  = (from x in db.PepsDB
                            select x).ToList();
            DateTime fin;
            if (Actuel.Count > 0)
            {
                fin = Actuel[Actuel.Count - 1].Date;
            }
            else
            {
                fin = DebParam;
            }
            
            var table = (from x in d.Table.Data
                         select x).ToList();
            DateTime start = DebParam;//new DateTime(2010, 04, 29);
            if (fin.CompareTo(start) > 0)
            {
                start = fin.AddDays(1);
            }
            DateTime end = FinParam;//DateTime.Now;
            double CloseFTSE, CloseSP, CloseEURO, CloseNIK;
            double ChangeJPY, ChangeUSD, ChangeGBP;
            double lastFTSE, lastSP, lastEURO, lastNIK;
            double lastJPY, lastUSD, lastGBP;
            lastEURO = 3185.97;
            lastFTSE = 0;
            lastNIK = 10924.79;
            lastSP = 0;
            lastGBP = 0;
            lastJPY = 0;
            lastUSD = 0;
            while(end.CompareTo(start)>=0){
                CloseEURO = 0;
                CloseFTSE = 0;
                CloseNIK = 0;
                CloseSP = 0;
                ChangeGBP = 0;
                ChangeJPY = 0;
                ChangeUSD = 0;
                try
                {
                    var ta = (from x in d.Table.Data
                              where x.Symbol.Equals("^FTSE") && x.Date.Equals(start)
                              select x.Value).ToList();
                     CloseFTSE = double.Parse(ta[0].ToString());
                }
                catch
                {
                    CloseFTSE = lastFTSE;
                }
                try
                {
                    var ta = (from x in d.Table.Data
                              where x.Symbol.Equals("^GSPC") && x.Date.Equals(start)
                              select x.Value).ToList();
                    CloseSP = double.Parse(ta[0].ToString());
                }catch{
                     CloseSP = lastSP;
                }
                try
                {
                    var ta = (from x in d.Table.Data
                              where x.Symbol.Equals("^N225") && x.Date.Equals(start)
                              select x.Value).ToList();
                    CloseNIK = double.Parse(ta[0].ToString());
                }catch{
                    CloseNIK = lastNIK;
                }
                try
                {
                    var ta = (from x in d.Table.Data
                              where x.Symbol.Equals("^STOXX50E") && x.Date.Equals(start)
                              select x.Value).ToList();
                    //A modifier
                    if (double.Parse(ta[0].ToString()) == 0)
                    {
                        CloseEURO = lastEURO;
                    }
                    else
                    {
                        CloseEURO = double.Parse(ta[0].ToString());
                    }
                }catch{
                     CloseEURO = lastEURO;
                }
                try
                {
                    var ta = (from x in change.Table.Data
                              where x.Column.Equals("EUR/JPY") && x.Date.Equals(start)
                              select x.Value).ToList();
                    ChangeJPY = double.Parse(ta[0].ToString());
                }
                catch
                {
                    ChangeJPY = lastJPY;
                }
                try
                {
                    var ta = (from x in change.Table.Data
                              where x.Column.Equals("EUR/USD") && x.Date.Equals(start)
                              select x.Value).ToList();
                    ChangeUSD = double.Parse(ta[0].ToString());
                }
                catch
                {
                    ChangeUSD = lastUSD;
                }
                try
                {
                    var ta = (from x in change.Table.Data
                              where x.Column.Equals("EUR/GBP") && x.Date.Equals(start)
                              select x.Value).ToList();
                    ChangeGBP = double.Parse(ta[0].ToString());
                }
                catch
                {
                    ChangeGBP = lastGBP;
                }
                PepsDB ord = new PepsDB
                {
                    Date = start,
                    FTSE = CloseFTSE.ToString(),
                    S_P = CloseSP.ToString(),
                    NIKKEI = CloseNIK.ToString(),
                    EUROSTOXX = CloseEURO.ToString(),
                    Eur_GBP = ChangeGBP.ToString(),
                    Eur_JPY = ChangeJPY.ToString(),
                    Eur_USD = ChangeUSD.ToString()
                };
                if (CloseSP != lastSP || CloseNIK != lastNIK || CloseFTSE != lastFTSE || CloseEURO != lastEURO)
                {
                    db.PepsDB.InsertOnSubmit(ord);
                }
                lastEURO = CloseEURO;
                lastFTSE = CloseFTSE;
                lastGBP = ChangeGBP;
                lastJPY = ChangeJPY;
                lastNIK = CloseNIK;
                lastSP = CloseSP;
                lastUSD = ChangeUSD;
                start = start.AddDays(1);

            }

            try
            {
                db.SubmitChanges();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }

        public void verifDate()
        {

        }
    }
}