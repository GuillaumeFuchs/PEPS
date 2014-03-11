#include "stdafx.h"
 
#include "Wrapper.h"
 
using namespace Computations;
namespace Wrapper {
	void WrapperClass::getPrice(double t, int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M){
		double ic, px, pxBS;

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_price(px, ic, pxBS, t, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, H, M);

		this->intConfiancePrix = ic;
		this->prix = px;
		this->prixBS = pxBS;
	}

	void WrapperClass::getDelta(double t, int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M){
		double icd, delt, deltBS;

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_delta(delt, icd, deltBS, t, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, H, M);

		this->intConfianceDelta = icd;
		this->delta = delt;
		this->deltaBS = deltBS;
	}

	void WrapperClass::getPriceSamples(int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int M, int samples){
		double maxP, varP;

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_price_samples(maxP, varP, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, M, samples);

		this->mxP = maxP;
		this->vrP = varP;
	}

	
	void WrapperClass::getDeltaSamples(int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int M, int samples){
		double maxD, varD;

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_delta_samples(maxD, varD, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, M, samples);

		this->mxD = maxD;
		this->vrD = varD;
	}

	void WrapperClass::getCouv(int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M){
		double pal, execTime;
		pin_ptr<double> pSummary = &summary[0];

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_couv(pal, pSummary, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, H, M, execTime);

		this->pl = pal;
		this->plt = 0.;
		this->executionTime = execTime;
	}
}
