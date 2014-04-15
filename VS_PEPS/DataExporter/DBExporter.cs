using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using APIFiMag;
using APIFiMag.Exporter;
using APIFiMag.Datas;

namespace DataExporter
{
    public class DBExporter : Export
    {
        private ExportDataContext db;


        public DBExporter()
        {
            db = new ExportDataContext();
        }

        public void Export(Data d)
        {
            var table = (from x in d.Table.Data
                         select x).ToList();

            // Create a new Order object.
            //Order ord = new Order
            //{
            //    OrderID = 12000,
            //    ShipCity = "Seattle",
            //    OrderDate = DateTime.Now
            //    // …
            //};

            //// Add the new object to the Orders collection.
            //db.Orders.InsertOnSubmit(ord);
            foreach (var item in table)
            {
                DateTime date = (from x in d.Table.Data
                                 where x.Date.CompareTo(item.Date) == 0
                                 select x.Date).First();
                if (date != null)
                {
                    Console.WriteLine("works");
                }

            }
        }

        public void verifDate()
        {

        }
    }
}