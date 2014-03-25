using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApp
{
    public partial class WebForm5 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Enregistrer(object sender, EventArgs e)
        {
            AffichageBD.AfficheBD hello = new AffichageBD.AfficheBD();
            double[] compo = new double[4];
            double compo_SP = double.Parse(TextBox1.Text);
            compo[0] = compo_SP;
            double compo_ftse = double.Parse(TextBox2.Text);
            compo[1] = compo_ftse;
            double compo_euro = double.Parse(TextBox3.Text);
            compo[2] = compo_euro;
            double compo_nikkei = double.Parse(TextBox4.Text);
            compo[3] = compo_nikkei;
            String now = DateTime.Now.ToString("dd/MM/yy");
            hello.setCompo(compo, now);

        }
    }
}