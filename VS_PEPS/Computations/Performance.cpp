# include "Performance.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file performance.cpp
 * \brief option performance 
 * \author equipe 11
 */

Performance :: Performance() : Option() {
}

Performance :: Performance(double T, int timeStep, int size, double r, double* coeff) : Option(T, timeStep, size, r, coeff){
}
 
Performance :: ~Performance(){
}

double Performance :: payoff (double t, 
	const PnlMat* path) const
{
  double sum = 0.0;
  double temp_num;
  double temp_deno;

  //Numerateur: vecteur contenant la somme des d actifs au temps t_i
  //Denominateur: vecteur contenant la somme des d actifs au temps t_{i-1}
  PnlVect* numerateur = pnl_vect_create(size_);
  PnlVect* denominateur = pnl_vect_create(size_);

  for (int i=1; i<timeStep_+1; i++){
	//On met les d actif au temps t_i dans numerateur
	//et ceux au temps t_{i-1} dans denominateur
	pnl_mat_get_col(numerateur, path, i);
	pnl_mat_get_col(denominateur, path, i-1);
	temp_num = pnl_vect_scalar_prod(numerateur, Coeff_);
	temp_deno = pnl_vect_scalar_prod(denominateur, Coeff_);
	sum = sum + temp_num/temp_deno;
  }
  sum = sum/(double)(timeStep_) - 1;
  pnl_vect_free(&numerateur);
  pnl_vect_free(&denominateur);
  return exp(-r_*(T_-t))*(1+MIN(MAX(sum,0), 0.1));
}
