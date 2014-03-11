# include "Basket.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file Basket.cpp
 * \brief Option panier
 * \author Equipe 11
 */

Basket :: Basket() : Option() {
  strike_ = 0;
}

Basket::Basket(double strike, double T, int timeStep, int size, double r, double * coeff) : Option(T, timeStep, size, r, coeff){
	strike_ = strike;
}

Basket :: ~Basket(){
}

double Basket :: get_Strike() const{
  return strike_;
}

void Basket :: set_Strike(double strike) {
  strike_ = strike;
}

double Basket :: payoff (const PnlMat *path, double t) const{
  double sum;
  PnlVect* final = pnl_vect_create(path->m);

  //On met dans final la dernière colonne de Path correspond à la valeur à maturité des sous-jacents.
  pnl_mat_get_col(final, path, (path->n-1));
  sum = pnl_vect_scalar_prod(final, Coeff_) - strike_;
  pnl_vect_free(&final);
  //On retourne le max entre le résultat de la somme et 0
  return exp(-r_*(T_-t))*MAX(sum, 0);
}
