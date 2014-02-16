using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper;

namespace WebApp
{
	public partial class _Default : System.Web.UI.Page
	{
		protected void Page_Load(object sender, EventArgs e)
		{
			TextBox1.Text = "0";
			TextBox2.Text = "100";
			TextBox3.Text = "100";
			TextBox4.Text = "0,2";
			TextBox5.Text = "0,05";
			TextBox6.Text = "1";
			TextBox7.Text = "10";
			TextBox8.Text = "0";
			TextBox9.Text = "10000";


		}

		protected void Button1_Click(object sender, EventArgs e)
		{
			double t = double.Parse(TextBox1.Text);
			double S0 = double.Parse(TextBox2.Text);
			double K = double.Parse(TextBox3.Text);
			double sigma = double.Parse(TextBox4.Text);
			double r = double.Parse(TextBox5.Text);
			double T = double.Parse(TextBox6.Text);
			int N = int.Parse(TextBox7.Text);
			int H = int.Parse(TextBox8.Text);
			int M = int.Parse(TextBox9.Text);

			WrapperClass wc = new WrapperClass();
			wc.getPriceCallEuro(t, S0, K, sigma, r, T, N, H, M);

			Label1.Text = wc.getPrice().ToString();
			Label2.Text = wc.getIC().ToString();
			Label3.Text = wc.getPriceBS().ToString();
		}
	}
}
