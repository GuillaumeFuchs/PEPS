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
		}

		protected void Button1_Click(object sender, EventArgs e)
		{
			double t = double.Parse(TextBox1.Text);
			int H = int.Parse(TextBox2.Text);

			WrapperClass wc = new WrapperClass();
			wc.getPriceCallEuro(t, 100, 100, .2, .05, 1, 10, H, 50000);

			Label1.Text = Math.Round(wc.getPrice(), 4).ToString();
			Label2.Text = Math.Round(wc.getICP(), 4).ToString();
			Label3.Text = Math.Round(wc.getPriceBS(), 4).ToString();
		}

		protected void Button2_Click(object sender, EventArgs e)
		{
			double t = double.Parse(TextBox3.Text);
			int H = int.Parse(TextBox4.Text);

			WrapperClass wc = new WrapperClass();
			wc.getDeltaCallEuro(t, 100, 100, .2, .05, 1, 10, H, 500000);

			Label4.Text = Math.Round(wc.getDelta(), 4).ToString();
			Label5.Text = Math.Round(wc.getICD(), 4).ToString();
			Label6.Text = Math.Round(wc.getDeltaBS(), 4).ToString();
		}

		protected void Button3_Click(object sender, EventArgs e)
		{
			int samples = int.Parse(TextBox5.Text);

			WrapperClass wc = new WrapperClass();
			wc.getPriceCallEuroSamples(100, 100, 0.2, 0.05, 1, 10, 50000, samples);

			Label7.Text = Math.Round(wc.getVrP(), 4).ToString();
			Label8.Text = Math.Round(wc.getMxP(), 4).ToString();
		}

		protected void Button4_Click(object sender, EventArgs e)
		{
			int samples = int.Parse(TextBox6.Text);

			WrapperClass wc = new WrapperClass();
			wc.getDeltaCallEuroSamples(100, 100, 0.2, 0.05, 1, 10, 50000, samples);

			Label9.Text = Math.Round(wc.getVrD(), 4).ToString();
			Label10.Text = Math.Round(wc.getMxD(), 4).ToString();
		}

		protected void Button5_Click(object sender, EventArgs e)
		{
			WrapperClass wc = new WrapperClass();
			wc.getCouvCallEuro(100, 100, 0.2, 0.05, 1, 10, 50, 50000);

			Label11.Text = Math.Round(wc.getPL(), 4).ToString();
			Label12.Text = Math.Round(wc.getPLT(), 4).ToString();

			//TABLEAU
			TableRow row_title = new TableRow();
			TableCell cell_1 = new TableCell();
			cell_1.Text = "Temps";
			row_title.Cells.Add(cell_1);
			TableCell cell_2 = new TableCell();
			cell_2.Text = "Cours de l'action";
			row_title.Cells.Add(cell_2);
			TableCell cell_3 = new TableCell();
			cell_3.Text = "Delta simulé";
			row_title.Cells.Add(cell_3);
			TableCell cell_4 = new TableCell();
			cell_4.Text = "Actions achetées (selon delta simulé)";
			row_title.Cells.Add(cell_4);
			TableCell cell_5 = new TableCell();
			cell_5.Text = "Delta théorique";
			row_title.Cells.Add(cell_5);
			TableCell cell_6 = new TableCell();
			cell_6.Text = "Actions achetées (selon delta théorique)";
			row_title.Cells.Add(cell_6);
			Table1.Rows.Add(row_title);
			int compteur = 0;
			for (int i = 0; i < 51; i++)
			{
				TableRow row = new TableRow();
				for (int d = 0; d < 6; d++)
				{
					TableCell cell = new TableCell();
					cell.Text = Math.Round(wc.getSummary()[compteur], 4).ToString();
					compteur++;
					row.Cells.Add(cell);
				}
				Table1.Rows.Add(row);
				Chart1.Series[0].Points.AddXY(Math.Round(wc.getSummary()[i*6], 2), Math.Round(wc.getSummary()[i*6+2], 2));
			}
		}
	}
}
