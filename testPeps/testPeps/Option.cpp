# include "Option.h"

Option :: Option(){
  T_ = 0;
  timeStep_ = 0;
  size_ = 0;
  Coeff_ = pnl_vect_new();
}

Option::Option(double T, int timeStep, int size, double *coeff){
	T_ = T;
	timeStep_ = timeStep;
	size_ = size;
	Coeff_ = pnl_vect_create(size_);
	for (int i = 0; i < size_; i++){
		LET(Coeff_, i) = coeff[i];
	}
}

Option :: ~Option(){
  pnl_vect_free(&Coeff_);
}

double Option :: get_T() const{
  return T_;
}

int Option :: get_timeStep() const{
  return timeStep_;
}

int Option :: get_size() const{
  return size_;
}

PnlVect * Option :: get_Coeff() const{
  return Coeff_;
}

void Option :: set_T(double T){
  T_ = T;
}

void Option :: set_timeStep(int timeStep){
  timeStep_ = timeStep;
}

void Option :: set_size(int size){
  size_ = size;
}

void Option :: set_Coeff(PnlVect *Coeff) {
  Coeff_ = Coeff;
}