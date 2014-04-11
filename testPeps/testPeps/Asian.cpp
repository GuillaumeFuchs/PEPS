# include "asian.h"
# include <pnl/pnl_mathtools.h>
#include <pnl/pnl_vector.h>

/*!
 * \file asian.cpp
 * \brief Implémentation de la classe fille d'Option: Asian 
 * \author equipe 11
 */

Asian :: Asian() : Option() {
  strike_ = 0; 
}

Asian::Asian(double strike, double T, int timeStep, int size, double r, double* coeff) : Option(T, timeStep, size, r, coeff){
	strike_ = strike;
}

Asian :: ~Asian(){
}

double Asian :: get_Strike() const{
  return strike_;
}

void Asian :: set_Strike(double Strike){
  strike_=Strike;
}

double Asian :: payoff (
	double t, 
	const PnlMat* path) const
{
  double sum;
  //Vecteur pour mette les valeurs des S_{ti}
  //Dimension D=1 donc path ne contient qu'une seule ligne (indice 0)
  PnlVect* final = pnl_vect_create(timeStep_+1);
  pnl_mat_get_row(final ,path, 0);
  //Calcul d'une option asiatique discrète
  sum = (1/(double)(timeStep_))*pnl_vect_sum(final) - strike_;
  pnl_vect_free(&final);
  return exp(-r_*(T_-t))*MAX(sum, 0);
}
