# include "Option.h"
# include "barrier_u.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file barrier_u.cpp
 * \brief Option barri�re haute
 * \author Equipe 11
 */

Barrier_u :: Barrier_u() : Option() {
  strike_ = 0;
  Coeff_ = pnl_vect_new();
  Bu_ = pnl_vect_new();
}

Barrier_u::Barrier_u(double strike, double* coeff, double* bu, double T, int timeStep, int size) : Option(T, timeStep, size){
	strike_ = strike;
	Coeff_ = pnl_vect_create(size_);
	Bu_ = pnl_vect_create(size_);
	for (int i = 0; i < size_; i++){
		LET(Coeff_, i) = coeff[i];
		LET(Bu_, i) = bu[i];
	}
}

Barrier_u :: ~Barrier_u(){
  pnl_vect_free(&Coeff_);
  pnl_vect_free(&Bu_);
}

double Barrier_u :: get_Strike() const{
  return strike_;
}

PnlVect* Barrier_u :: get_Coeff() const{
  return Coeff_;
}

PnlVect* Barrier_u :: get_Bu() const{
  return Bu_;
}

void Barrier_u :: set_Strike(double Strike) {
  strike_ = Strike;
}

void Barrier_u :: set_Coeff(PnlVect *Coeff) {
  Coeff_ = Coeff;
}

void Barrier_u :: set_Bu(PnlVect *Bu) {
  Bu_ = Bu;
}

double Barrier_u :: payoff (const PnlMat *path) const{
  double sum ;
  //Vecteur utilis� pour effectuer la somme de chaque actif � maturit�
  PnlVect* final = pnl_vect_create(size_);

  //On met dans final la derni�re colonne de Path correspond � la valeur � maturit� des sous-jacents
  pnl_mat_get_col(final, path, timeStep_);
  sum = pnl_vect_scalar_prod(final, Coeff_) - strike_;
  //On v�rifie que toutes les valeurs des sous-jacents soient en dessous de la barri�re
  //Si on en trouve une alors le prix de l'option est de 0
  for (int i=0; i<timeStep_+1; i++){
	for (int d=0; d<size_; d++){
	  if (pnl_mat_get(path,d,i) > pnl_vect_get(Bu_,d)){
		pnl_vect_free(&final);
		return 0;
	  }
	}
  }
  return MAX(sum, 0);
}
