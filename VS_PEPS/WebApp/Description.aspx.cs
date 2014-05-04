using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.Adapters;
using System.Windows.Forms;
using System.Web.Script.Serialization;
using System.Web.UI.DataVisualization.Charting;
using System.Globalization;
using AccesDB;

namespace WebApp
{
    public partial class WebForm6 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            AccesBD BD = new AccesBD();
            Panel1.Controls.Clear();
            Panel1.Controls.Add(new LiteralControl(DateTime.Now.Day.ToString() + "/" + DateTime.Now.Month.ToString() + "/" + DateTime.Now.Year.ToString()));
            String nomPd= null;
            int nbParts = 0, valNom = 0;
            int info = BD.GetInfoProd(ref nomPd, ref nbParts,ref valNom);
            if (info != 0)
            {
                Panel4.Controls.Clear();
                Panel5.Controls.Clear();
                Panel6.Controls.Clear();
                Panel4.Controls.Add(new LiteralControl(nbParts.ToString()));
                Panel5.Controls.Add(new LiteralControl((valNom).ToString() + "€"));
                LiteralControl ok = (LiteralControl)Panel2.Controls[0];
                Panel6.Controls.Add(new LiteralControl(Math.Round((100 * double.Parse(nbParts.ToString()) / double.Parse(ok.Text.ToString())), 2).ToString() + "%"));
            }
        }

        protected void ChangePart(object sender, EventArgs e)
        {
            try
            {
                AccesBD BD = new AccesBD();
                int.Parse(TextBox1.Text);
                Panel4.Controls.Clear();
                Panel5.Controls.Clear();
                Panel6.Controls.Clear();
                String parts = TextBox1.Text;
                Panel4.Controls.Add(new LiteralControl(parts));
                Panel5.Controls.Add(new LiteralControl((double.Parse(parts) * 150).ToString() + "€"));
                LiteralControl ok = (LiteralControl)Panel2.Controls[0];
                Panel6.Controls.Add(new LiteralControl(Math.Round((100*double.Parse(parts)/double.Parse(ok.Text.ToString())),2).ToString()+"%"));
                BD.InsertInfoProd("Playlist 2", int.Parse(parts), int.Parse(parts) * 150);
            }
            catch
            {
                System.Console.Write("error");
            }
        }
    }

}