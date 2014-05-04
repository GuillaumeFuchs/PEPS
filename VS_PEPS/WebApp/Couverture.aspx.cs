using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper;

namespace WebApp
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

		protected void Button5_Click(object sender, EventArgs e)
		{
			int H = int.Parse(TextBox7.Text);

			int size = 4;
			double[] spot = new double[] { 100, 100, 100, 100 };
			double[] sigma = new double[] { 0.2, 0.2, 0.2, 0.2 };
			double r = 0.05;
			double[] coeff = new double[] { .25, .25, .25, .25 };
			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

			//int size = 1;
			//double[] spot = new double[] { 100 };
			//double K = 100;
			//double[] sigma = new double[] { 0.2 };
			//double r = 0.05;
			//double[] coeff = new double[] { 1 };
			//double[] rho = new double[] { 0.0 };

			double T = 6;
			int N = 6;
			int samples = 50000;

			WrapperClass wc = new WrapperClass(size, H);
			double K = 0.0;
			wc.getHedge(size, spot, K, sigma, r, coeff, rho, T, N, H, samples);
			
			Label11.Text = Math.Round(wc.getErr(), 4).ToString();
			Label12.Text = Math.Round(wc.getExecutionTime(), 4).ToString();

			//Array
			TableRow row_title = new TableRow();
			TableCell cell_1 = new TableCell();
			cell_1.Text = "Temps";
			row_title.Cells.Add(cell_1);
			for (int i = 0; i < size; i++)
			{
				TableCell cell_2 = new TableCell();
				cell_2.Text = "Cours de l'action " + i;
				row_title.Cells.Add(cell_2);
				TableCell cell_3 = new TableCell();
				cell_3.Text = "Delta simulé " + i;
				row_title.Cells.Add(cell_3);
				TableCell cell_4 = new TableCell();
				cell_4.Text = "Actions achetées " + i;
				row_title.Cells.Add(cell_4);
			}
			Table1.Rows.Add(row_title);

			//Chart
			int compteur = 0;
			for (int i = 0; i < H + 1; i++)
			{
				TableRow row = new TableRow();
				for (int d = 0; d < (3*size+1); d++)
				{
					TableCell cell = new TableCell();
					cell.Text = Math.Round(wc.getSummary()[compteur], 4).ToString();
					compteur++;
					row.Cells.Add(cell);
				}
				Table1.Rows.Add(row);

				for (int d = 0; d < size; d++)
				{
					Chart1.Series[d].Points.AddXY(Math.Round(wc.getSummary()[i * (1 + 3 * size)], 2), Math.Round(wc.getSummary()[i * (1 + 3 * size) + 2+3*d], 2));
					Chart2.Series[d].Points.AddXY(Math.Round(wc.getSummary()[i * (1 + 3 * size)], 2), Math.Round(wc.getSummary()[i * (1 + 3 * size) + 1+3*d], 2));
				}
			}
		}
    }
}