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
            ComboBox1.SelectedIndexChanged += new EventHandler(ComboBox1_SelectedIndexChanged);
            if (!Page.IsPostBack)
            {
                ComboBox1.Attributes.Add("onchange", "ajout_param();");
            }
		}
        protected void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        
        protected void AjoutParam(object sender, EventArgs e)
        {
            Console.WriteLine("On arrive dans AjoutParam");
            Console.WriteLine(ComboBox1.SelectedValue.ToString());
            if (ComboBox1.SelectedValue.ToString().Equals("0"))
            {
                
                string script = "<script type=\"text/javascript\">ajout_param();</script>";
                ClientScript.RegisterStartupScript(typeof(Page), "script", script);
            }
        }

        //protected void Button1_Click(object sender, EventArgs e)
        //{
        //    double t = double.Parse(TextBox1.Text);
        //    int H = int.Parse(TextBox2.Text);

        //    WrapperClass wc = new WrapperClass();
        //    wc.getPriceCallEuro(t, 100, 100, .2, .05, 1, 10, H, 50000);

        //    Label1.Text = Math.Round(wc.getPrice(), 4).ToString();
        //    Label2.Text = Math.Round(wc.getICP(), 4).ToString();
        //    Label3.Text = Math.Round(wc.getPriceBS(), 4).ToString();
        //}

        //protected void Button2_Click(object sender, EventArgs e)
        //{
        //    double t = double.Parse(TextBox3.Text);
        //    int H = int.Parse(TextBox4.Text);

        //    WrapperClass wc = new WrapperClass();
        //    wc.getDeltaCallEuro(t, 100, 100, .2, .05, 1, 10, H, 500000);

        //    Label4.Text = Math.Round(wc.getDelta(), 4).ToString();
        //    Label5.Text = Math.Round(wc.getICD(), 4).ToString();
        //    Label6.Text = Math.Round(wc.getDeltaBS(), 4).ToString();
        //}

        //protected void Button3_Click(object sender, EventArgs e)
        //{
        //    int samples = int.Parse(TextBox5.Text);

        //    WrapperClass wc = new WrapperClass();
        //    wc.getPriceCallEuroSamples(100, 100, 0.2, 0.05, 1, 10, 50000, samples);

        //    Label7.Text = Math.Round(wc.getVrP(), 4).ToString();
        //    Label8.Text = Math.Round(wc.getMxP(), 4).ToString();
        //}

        //protected void Button4_Click(object sender, EventArgs e)
        //{
        //    int samples = int.Parse(TextBox6.Text);

        //    WrapperClass wc = new WrapperClass();
        //    wc.getDeltaCallEuroSamples(100, 100, 0.2, 0.05, 1, 10, 50000, samples);

        //    Label9.Text = Math.Round(wc.getVrD(), 4).ToString();
        //    Label10.Text = Math.Round(wc.getMxD(), 4).ToString();
        //}

	}
}
