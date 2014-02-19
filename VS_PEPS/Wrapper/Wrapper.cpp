#include "stdafx.h"
 
#include "Wrapper.h"
 
using namespace Computations;
namespace Wrapper {
	void WrapperClass::getPriceCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M) {
		double ic, px, pxBS;
		compute_price_call(px, ic, pxBS, t, S0, K, sigma, r, T, N, H, M);
		this->intConfiancePrix = ic;
		this->prix = px;
		this->prixBS = pxBS;
	}

	void WrapperClass::getDeltaCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M) {
		double icd, delt, deltBS;
		compute_delta_call(delt, icd, deltBS, t, S0, K, sigma, r, T, N, H, M);
		this->intConfianceDelta = icd;
		this->delta = delt;
		this->deltaBS = deltBS;
	}

	void WrapperClass::getPriceCallEuroSamples(double S0, double K, double sigma, double r, double T, int N, int M, int samples){
		double maxP, varP;
		compute_price_call_samples(maxP, varP, S0, K, sigma, r, T, N, M, samples);
		this->mxP = maxP;
		this->vrP = varP;
	}

	void WrapperClass::getDeltaCallEuroSamples(double S0, double K, double sigma, double r, double T, int N, int M, int samples){
		double maxD, varD;
		compute_delta_call_samples(maxD, varD, S0, K, sigma, r, T, N, M, samples);
		this->mxD = maxD;
		this->vrD = varD;
	}

	void WrapperClass::getCouvCallEuro(double S0, double K, double sigma, double r, double T, int N, int H, int M){
		double pal, palt;
		pin_ptr<double> pdouble = &summary[0];
		compute_couv_call(pal, palt, pdouble, S0, K, sigma, r, T, N, H, M);
		this->pl = pal;
		this->plt = palt;
	}
}
