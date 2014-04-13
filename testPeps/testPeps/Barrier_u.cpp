# include "barrier_u.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file barrier_u.cpp
 * \brief Option barrière haute
 * \author Equipe 11
 */

Barrier_u :: Barrier_u() : Option() {
  strike_ = 0;
  Bu_ = pnl_vect_new();
}

Barrier_u::Barrier_u(double strike, double* bu, double T, int timeStep, int size, double r, double* coeff) : Option(T, timeStep, size, r, coeff){
	strike_ = strike;
	Bu_ = pnl_vect_create(size_);
	for (int i = 0; i < size_; i++){
		LET(Bu_, i) = bu[i];
	}
}

Barrier_u :: ~Barrier_u(){
  pnl_vect_free(&Bu_);
}

double Barrier_u :: get_Strike() const{
  return strike_;
}

PnlVect* Barrier_u :: get_Bu() const{
  return Bu_;
}

void Barrier_u :: set_Strike(double Strike) {
  strike_ = Strike;
}

void Barrier_u :: set_Bu(PnlVect *Bu) {
  Bu_ = Bu;
}

double Barrier_u :: payoff (
	double t, 
	const PnlMat* path) const
{
  double sum ;
  //Vecteur utilisé pour effectuer la somme de chaque actif à maturité
  PnlVect* final = pnl_vect_create(size_);

  //On met dans final la dernière colonne de Path correspond à la valeur à maturité des sous-jacents
  pnl_mat_get_col(final, path, timeStep_);
  sum = pnl_vect_scalar_prod(final, Coeff_) - strike_;
  //On vérifie que toutes les valeurs des sous-jacents soient en dessous de la barrière
  //Si on en trouve une alors le prix de l'option est de 0
  for (int i=0; i<timeStep_+1; i++){
	for (int d=0; d<size_; d++){
	  if (MGET(path,d,i) > pnl_vect_get(Bu_,d)){
		pnl_vect_free(&final);
		return 0;
	  }
	}
  }
  return exp(-r_*(T_-t))*MAX(sum, 0);
}
