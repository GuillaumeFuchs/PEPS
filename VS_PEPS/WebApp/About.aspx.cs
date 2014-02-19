using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Parameters;

namespace WebApp
{
	public partial class About : System.Web.UI.Page
	{
		protected void Page_Load(object sender, EventArgs e)
		{

		}

        protected void Compute_Volat(object sender, EventArgs e)
        {
            int NbDays = int.Parse(TextBox1.Text);
            ComputeParam cp = new ComputeParam();
            cp.param(NbDays);

            Label1.Text = Math.Round(100*(cp.Volatility[0]),2).ToString()+" %";
            Label2.Text = Math.Round(100 * (cp.Volatility[1]), 2).ToString() + " %";
            Label4.Text = Math.Round(100 * (cp.Volatility[2]), 2).ToString() + " %";
            Label5.Text = Math.Round(100 * (cp.Volatility[3]), 2).ToString() + " %";

            Table1.Rows[1].Cells[2].Text = Math.Round((cp.Corel[0, 1]), 2).ToString();
            Table1.Rows[1].Cells[3].Text = Math.Round((cp.Corel[0, 2]), 2).ToString();
            Table1.Rows[1].Cells[4].Text = Math.Round((cp.Corel[0, 3]), 2).ToString();
            Table1.Rows[2].Cells[1].Text = Math.Round((cp.Corel[1, 0]), 2).ToString();
            Table1.Rows[2].Cells[3].Text = Math.Round((cp.Corel[1, 2]), 2).ToString();
            Table1.Rows[2].Cells[4].Text = Math.Round((cp.Corel[1, 3]), 2).ToString();
            Table1.Rows[3].Cells[1].Text = Math.Round((cp.Corel[2, 0]), 2).ToString();
            Table1.Rows[3].Cells[2].Text = Math.Round((cp.Corel[2, 1]), 2).ToString();
            Table1.Rows[3].Cells[4].Text = Math.Round((cp.Corel[2, 3]), 2).ToString();
            Table1.Rows[4].Cells[1].Text = Math.Round((cp.Corel[3, 0]), 2).ToString();
            Table1.Rows[4].Cells[2].Text = Math.Round((cp.Corel[3, 1]), 2).ToString();
            Table1.Rows[4].Cells[3].Text = Math.Round((cp.Corel[3, 2]), 2).ToString();
        }
	}
}
