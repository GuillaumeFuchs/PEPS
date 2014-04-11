#include "stdafx.h"
#include "Wrapper.h"

using namespace Computations;

namespace Wrapper {
	void WrapperClass::getPrice(double t, int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M){
		double ic;
		double px;

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_price(px, ic, t, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, H, M);

		this->intConfiancePrix = ic;
		this->prix = px;
	}

	void WrapperClass::getDelta(double t, int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M){
		double delt;
		double icD;

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_delta(delt, icD, t, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, H, M);

		this->intConfianceDelta = icD;
		this->delta = delt;
	}

	void WrapperClass::getHedge(int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M){
		double PaL, execTime;
		pin_ptr<double> pSummary = &summary[0];

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_couv(PaL, pSummary, size, pSpot, K, pSigma, r, pCoeff, pRho, T, N, H, M, execTime);

		this->pl = PaL;
		this->executionTime = execTime;
	}

	void WrapperClass::getPortfolio(
		int past_size, 
		int size, 
		int N, 
		int M,
		int H,
		double T, 
		double t, 
		double r, 
		array<double> ^sigma, 
		array<double> ^rho, 
		array<double> ^coeff, 
		array<double> ^past, 
		array<double> ^delta_ant){

			double pl;
			double risk;
			double risk_free;

			pin_ptr<double> pSigma = &sigma[0];
			pin_ptr<double> pRho = &rho[0];
			pin_ptr<double> pCoeff = &coeff[0];
			pin_ptr<double> pPast = &past[0];
			pin_ptr<double> pDeltaAnt = &delta_ant[0];

			compute_portfolio(past_size, size, N, M, H, T, t, r, pSigma, pRho, pCoeff, pPast, pDeltaAnt, pl, risk, risk_free);

			this->pl = pl;
			this->risk = risk;
			this->risk_free = risk_free;
	}


}
