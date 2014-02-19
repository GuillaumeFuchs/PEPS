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
        }
	}
}
