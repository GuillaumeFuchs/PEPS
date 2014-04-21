using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Script.Serialization;
using System.Web.UI.DataVisualization.Charting;
using System.Globalization;
using Wrapper;
using Parameters;

namespace WebApp
{
    public partial class AffichagePortCouv : System.Web.UI.Page
    {
        

        protected void Hedge(object sender, EventArgs e)
        {

            DateTime deb = new DateTime(2010, 04, 29);
            WrapperClass wrap = new WrapperClass(4,60);
            AffichageBD.AfficheBD hello = new AffichageBD.AfficheBD();
            double[] spot = new double[4];
            //On fait l'approximation que tout les spots commençent à la même date et on ne tient pas compte des paramètres pour le moment
            //L'ordre des spots à t il une importance ?
            for (int i = 0; i<4; i++){
                //Grosse approximation
                spot[i] = hello.Spot[i][0];
            }
            ComputeParam cp = new ComputeParam();
            cp.param(40,deb);
            double[] sigma = new double[4];
            double[] rho = new double[16];
            for (int i = 0; i<4; i++){
                sigma[i] = cp.Volatility[i];
                for (int j = 0 ; j < 4; j++){
                    rho[i*4+j] = cp.Corel[i,j];
                }
            }
            double[] coeff = new double[4];
            for (int i = 0; i<4; i++){
                coeff[i] = 0.25;
            }
            //On fait appelle à la méthode de fuchs avec les paramètres choisit
            wrap.getHedge(4, spot, 150, sigma, 0.05, coeff, rho, 6, 30, 60, 100);

            double[] summary = new double[wrap.getSummary().Length];
            summary = wrap.getSummary();

            //Affichage du portefeuille
            Chart1.Titles.Add("Composition du portefeuille de couverture");
            for (int d = 0; d < 4; d++)
            {
                Chart1.Legends.Add(new Legend("Delta du " + cp.Assets[d]));
                for (int j = 0; j < wrap.getSummary().Length/13-2 ; ++j)
                {
                    Chart1.Series[d].Points.AddXY(summary[j * 13], summary[j * 13 + 5 + d]);
                }
                Chart1.Series[d].Name = "Delta du " + cp.Assets[d];
                Affichage.Style.Add(HtmlTextWriterStyle.Display, "inline");
            }
        }
    }
}