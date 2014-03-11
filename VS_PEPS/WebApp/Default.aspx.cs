using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper;
using Parameters;

namespace WebApp
{
	public partial class _Default : System.Web.UI.Page
	{
		protected void Page_Load(object sender, EventArgs e)
		{
		}

		protected void Button1_Click(object sender, EventArgs e)
		{
			double t = double.Parse(TextBox1.Text);
			int H = int.Parse(TextBox2.Text);
			int size = 4;
			double[] spot = new double[] {  100, 100, 100, 100 };
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
			double T = 6;
			int N = 6;
			int M = 50000;

			WrapperClass wc = new WrapperClass();
			double K = 0.0;
			wc.getPrice(t, size, spot, K, sigma, r, coeff, rho, T, N, H, M);

			Label1.Text = Math.Round(wc.getPrice(), 4).ToString();
			Label2.Text = Math.Round(wc.getICP(), 4).ToString();
			Label3.Text = Math.Round(wc.getPriceBS(), 4).ToString();
		}

		protected void Button2_Click(object sender, EventArgs e)
		{
			double t = double.Parse(TextBox3.Text);
			int H = int.Parse(TextBox4.Text);
			int size = 4;
			double[] spot = new double[] {  100, 100, 100, 100 };
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
			double T = 6;
			int N = 6;
			int M = 50000;

			WrapperClass wc = new WrapperClass();
			double K = 0.0;
			wc.getDelta(t, size, spot, K, sigma, r, coeff, rho, T, N, H, M);

			Label4.Text = Math.Round(wc.getDelta(), 4).ToString();
			Label5.Text = Math.Round(wc.getICD(), 4).ToString();
			Label6.Text = Math.Round(wc.getDeltaBS(), 4).ToString();
		}

		protected void Button3_Click(object sender, EventArgs e)
		{
			int samples = int.Parse(TextBox5.Text);
			int size = 4;
			double[] spot = new double[] {  100, 100, 100, 100 };
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
			double T = 6;
			int N = 6;
			int M = 50000;

			WrapperClass wc = new WrapperClass();
			double K = 0.0;
			wc.getPriceSamples(size, spot, K, sigma, r, coeff, rho, T, N, M, samples);

			Label7.Text = Math.Round(wc.getVrP(), 4).ToString();
			Label8.Text = Math.Round(wc.getMxP(), 4).ToString();
		}

		protected void Button4_Click(object sender, EventArgs e)
		{
			int samples = int.Parse(TextBox6.Text);
			int size = 4;
			double[] spot = new double[] {  100, 100, 100, 100 };
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
			double T = 6;
			int N = 6;
			int M = 50000;

			WrapperClass wc = new WrapperClass();
			double K = 0.0;
			wc.getDeltaSamples(size, spot, K, sigma, r, coeff, rho, T, N, M, samples);

			Label9.Text = Math.Round(wc.getVrD(), 4).ToString();
			Label10.Text = Math.Round(wc.getMxD(), 4).ToString();
		}

	}
}
