#include "Modelasset.h"
#include <math.h>
#include <cstdio>
#include "montecarlos.h"
#include <iostream>

using namespace std;
ModelAsset::ModelAsset(){
	size_ = 0;
	r_ = 0.0;
	rho_ = new double();
	sigma_ = pnl_vect_new();
	spot_ = pnl_vect_new();
	trend_ = pnl_vect_new();
	Cho_ = pnl_mat_new();
	Gi_ = pnl_vect_new();
	Ld_ = pnl_vect_new();
}

ModelAsset::ModelAsset(int size, double r, double* rho, double* sigma, double* spot, double* trend){
	(*this).size_ = size;
	(*this).r_ = r;
	(*this).rho_ = rho;
	(*this).sigma_ = pnl_vect_create(size_);
	(*this).spot_ = pnl_vect_create(size_);
	(*this).trend_ = pnl_vect_create(size_);

	(*this).Cho_ = pnl_mat_create_from_double(size_, size_, 1);
	int compteur = -1;

	for (int i = 1; i < size_; i++){
		for (int j = 0 ; j < i; j++){
			MLET(Cho_, i, j) = rho_[++compteur];
			MLET(Cho_, j, i) = rho_[compteur];
		}
	}
	for (int i = 0; i < size_; i++){
		LET(sigma_, i) = sigma[i];
		LET(spot_, i) = spot[i];
		if (trend != NULL)
			LET(trend_, i) = trend[i];
		else
			LET(trend_, i) = r;
		pnl_mat_set_diag(Cho_, 1, i);
	}
	pnl_mat_chol(Cho_);

	Gi_ = pnl_vect_create(size_);
	Ld_ = pnl_vect_create(size_);
}

ModelAsset::~ModelAsset(){
	pnl_vect_free(&sigma_);
	pnl_vect_free(&spot_);
	pnl_vect_free(&trend_);
	pnl_vect_free(&Gi_);
	pnl_vect_free(&Ld_);
	pnl_mat_free(&Cho_);
}

int ModelAsset::get_size() const{
	return size_;
}

double ModelAsset::get_r() const{
	return r_;
}

double* ModelAsset::get_rho() const{
	return rho_;
}

PnlVect * ModelAsset::get_sigma() const{
	return sigma_;
}

PnlVect * ModelAsset::get_spot() const{
	return spot_;
}

PnlVect * ModelAsset::get_trend() const{
	return trend_;
}

PnlMat * ModelAsset::get_cho() const{
	return Cho_;
}

PnlVect * ModelAsset::get_gi() const{
	return Gi_;
}

PnlVect * ModelAsset::get_ld() const{
	return Ld_;
}

void ModelAsset::set_size(int size){
	size_ = size;
}

void ModelAsset::set_r(double r){
	r_ = r;
}

void ModelAsset::set_rho(double* rho){
	rho_ = rho;
}

void ModelAsset::set_sigma(PnlVect *sigma){
	sigma_ = sigma;
}

void ModelAsset::set_spot(PnlVect *spot){
	spot_ = spot;
}

void ModelAsset::set_trend(PnlVect *trend){
	trend_ = trend;
}

void ModelAsset::set_cho(PnlMat *Cho){
	Cho_ = pnl_mat_copy(Cho);
}

void ModelAsset::set_gi(PnlVect *Gi){
	Gi_ = Gi;
}

void ModelAsset::set_ld(PnlVect *Ld){
	Ld_ = Ld;
}
