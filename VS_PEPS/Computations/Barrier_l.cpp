# include "barrier_l.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file barrier_l.cpp
 * \brief Option barrière basse
 * \author Equipe 11
 */

Barrier_l :: Barrier_l() : Option() {
  strike_ = 0;
  Bl_ = pnl_vect_new();
}

Barrier_l::Barrier_l(double strike, double *bl, double T, int timeStep, int size, double r, double* coeff) : Option(T, timeStep, size, r, coeff){
	strike_ = strike;
	Bl_ = pnl_vect_create(size_);
	for (int i = 0; i < size_; i++){
		LET(Bl_, i) = bl[i];
	}
}

Barrier_l :: ~Barrier_l(){
  pnl_vect_free(&Bl_);
}

double Barrier_l :: get_Strike() const{
  return strike_;
}

PnlVect* Barrier_l :: get_Bl() const{
  return Bl_;
}

void Barrier_l :: set_Strike(double Strike) {
  strike_ = Strike;
}

void Barrier_l :: set_Bl(PnlVect *Bl) {
  Bl_ = Bl;
}

double Barrier_l :: payoff (double t, 
	const PnlMat* path) const
{
  double sum ;
  PnlVect* final = pnl_vect_create(size_);

  //On met dans final la dernière colonne de Path correspond à la valeur à maturité des sous-jacents.
  pnl_mat_get_col(final, path, timeStep_);
  sum = pnl_vect_scalar_prod(final, Coeff_) - strike_;
  //On vérifie que toutes les valeurs des sous-jacents soient au dessus de la barrière
  //Si on en trouve une alors le prix de l'option est de 0
  for (int i=0; i<timeStep_+1; i++){
	for (int d=0; d<size_; d++){
	  if (MGET(path,d,i) < GET(Bl_,d)){
		pnl_vect_free(&final);
		return 0;
	  }
	}
  }
  return exp(-r_*(T_-t))*MAX(sum, 0);
}
