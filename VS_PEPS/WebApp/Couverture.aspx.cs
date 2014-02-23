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
			double[] spot = new double[] { 100, 80, 90, 120 };
			double K = 100;
			double[] sigma = new double[] { 0.7, 0.05, 0.2, 0.15 };

			double r = 0.05;
			double[] coeff = new double[] { .25, .25, .25, .25 };

			double[] rho = new double[] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

			double T = 1;
			int N = 10;
			int samples = 50000;

			WrapperClass wc = new WrapperClass(size, H);
			wc.getCouvCallEuro(size, spot, K, sigma, r, coeff, rho, T, N, H, samples);
			
			Label11.Text = Math.Round(wc.getPL(), 4).ToString();
			Label12.Text = Math.Round(wc.getExecutionTime(), 4).ToString();

			//TABLEAU
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
				Chart1.Series[0].Points.AddXY(Math.Round(wc.getSummary()[i * (1+3*size)], 2), Math.Round(wc.getSummary()[i * (1+3*size) + 2], 2));
				Chart1.Series[1].Points.AddXY(Math.Round(wc.getSummary()[i * (1 + 3 * size)], 2), Math.Round(wc.getSummary()[i * (1 + 3 * size) + 5], 2));
				Chart1.Series[2].Points.AddXY(Math.Round(wc.getSummary()[i * (1 + 3 * size)], 2), Math.Round(wc.getSummary()[i * (1 + 3 * size) + 8], 2));
				Chart1.Series[3].Points.AddXY(Math.Round(wc.getSummary()[i * (1 + 3 * size)], 2), Math.Round(wc.getSummary()[i * (1 + 3 * size) + 11], 2));

			}
		}
    }
}