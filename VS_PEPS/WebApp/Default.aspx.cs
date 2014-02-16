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

			TextBox10.Text = "0";
			TextBox11.Text = "100";
			TextBox12.Text = "100";
			TextBox13.Text = "0,2";
			TextBox14.Text = "0,05";
			TextBox15.Text = "1";
			TextBox16.Text = "10";
			TextBox17.Text = "0";
			TextBox18.Text = "10000";

			TextBox19.Text = "100";
			TextBox20.Text = "100";
			TextBox21.Text = "0,2";
			TextBox22.Text = "0,05";
			TextBox23.Text = "1";
			TextBox24.Text = "10";
			TextBox25.Text = "50000";
			TextBox26.Text = "100";

			TextBox27.Text = "100";
			TextBox28.Text = "100";
			TextBox29.Text = "0,2";
			TextBox30.Text = "0,05";
			TextBox31.Text = "1";
			TextBox32.Text = "10";
			TextBox33.Text = "50000";
			TextBox34.Text = "100";

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
			Label2.Text = wc.getICP().ToString();
			Label3.Text = wc.getPriceBS().ToString();
		}

		protected void Button2_Click(object sender, EventArgs e)
		{
			double t = double.Parse(TextBox10.Text);
			double S0 = double.Parse(TextBox11.Text);
			double K = double.Parse(TextBox12.Text);
			double sigma = double.Parse(TextBox13.Text);
			double r = double.Parse(TextBox14.Text);
			double T = double.Parse(TextBox15.Text);
			int N = int.Parse(TextBox16.Text);
			int H = int.Parse(TextBox17.Text);
			int M = int.Parse(TextBox18.Text);

			WrapperClass wc = new WrapperClass();
			wc.getDeltaCallEuro(t, S0, K, sigma, r, T, N, H, M);

			Label4.Text = wc.getDelta().ToString();
			Label5.Text = wc.getICD().ToString();
			Label6.Text = wc.getDeltaBS().ToString();
		}

		protected void Button3_Click(object sender, EventArgs e)
		{
			double S0 = double.Parse(TextBox19.Text);
			double K = double.Parse(TextBox20.Text);
			double sigma = double.Parse(TextBox21.Text);
			double r = double.Parse(TextBox22.Text);
			double T = double.Parse(TextBox23.Text);
			int N = int.Parse(TextBox24.Text);
			int M = int.Parse(TextBox25.Text);
			int samples = int.Parse(TextBox26.Text);

			WrapperClass wc = new WrapperClass();
			wc.getPriceCallEuroSamples(S0, K, sigma, r, T, N, M, samples);

			Label7.Text = wc.getVrP().ToString();
			Label8.Text = wc.getMxP().ToString();
		}

		protected void Button4_Click(object sender, EventArgs e)
		{
			double S0 = double.Parse(TextBox27.Text);
			double K = double.Parse(TextBox28.Text);
			double sigma = double.Parse(TextBox29.Text);
			double r = double.Parse(TextBox30.Text);
			double T = double.Parse(TextBox31.Text);
			int N = int.Parse(TextBox32.Text);
			int M = int.Parse(TextBox33.Text);
			int samples = int.Parse(TextBox34.Text);

			WrapperClass wc = new WrapperClass();
			wc.getDeltaCallEuroSamples(S0, K, sigma, r, T, N, M, samples);

			Label9.Text = wc.getVrD().ToString();
			Label10.Text = wc.getMxD().ToString();
		}

		protected void Button5_Click(object sender, EventArgs e)
		{
			WrapperClass wc = new WrapperClass();
			wc.getCouvCallEuro(100, 100, 0.2, 0.05, 1, 10, 50, 50000);

			Label11.Text = wc.getPL().ToString();
			Label12.Text = wc.getPLT().ToString();
		}

	}
}
