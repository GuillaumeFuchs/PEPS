#include "Montecarlos.h"
#include <math.h>
#include <pnl/pnl_vector.h>
#include <pnl/pnl_matrix.h>
#include <pnl/pnl_cdf.h>
#include <pnl/pnl_mathtools.h>
#include <cstdio>

MonteCarlos::MonteCarlos(PnlRng * rng){
	(*this).rng = rng;
	h_ = 0.0;
	samples_ = 0;
}

MonteCarlos::MonteCarlos(ModelAsset *mod, Option *opt, PnlRng *rng, double h, int samples){
	(*this).mod_ = mod;
	(*this).opt_ = opt;
	(*this).rng = rng;
	(*this).h_ = h;
	(*this).samples_ = samples;
}

/**
* Accesseurs
*
*/
MonteCarlos::~MonteCarlos(){
}

ModelAsset* MonteCarlos::get_mod() const{
	return mod_;
}

Option* MonteCarlos::get_opt() const{
	return opt_;
}

PnlRng* MonteCarlos::get_rng() const{
	return rng;
}

double MonteCarlos::get_h() const{
	return h_;
}

int MonteCarlos::get_samples() const{
	return samples_;
}

/**
* Mutateurs
*
*/
void MonteCarlos::set_mod(ModelAsset* mod){
	mod_ = mod;
}

void MonteCarlos::set_opt(Option* opt){
	opt_ = opt;
}

void MonteCarlos::set_rng(PnlRng* rng){
	(*this).rng = rng;
}

void MonteCarlos::set_h(double h){
	h_ = h;
}

void MonteCarlos::set_samples(int samples){
	samples_ = samples;
}