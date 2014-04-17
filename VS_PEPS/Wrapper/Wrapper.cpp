#include "stdafx.h"
#include "Wrapper.h"

using namespace Computations;

namespace Wrapper {

	void WrapperClass::computePrice(
		int past_size,
		int size,
		int N,
		int M,
		double T,
		double t,
		double r,
		array<double> ^sigma, 
		array<double> ^rho, 
		array<double> ^coeff, 
		array<double> ^past)
	{
		double price;
		double ci;

		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pRho = &rho[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pPast = &past[0];

		compute_price(past_size, size, N, M, T, t, r, price, ci, pSigma, pCoeff, pRho, pPast);

		this->price = price;
		this->ciPrice = ci;
	}

	void WrapperClass::computePortfolio(
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
		array<double> ^past)
	{
		double risk = this->risk;
		double riskFree = this->riskFree;
		double price;
		double ci;
		double err;

		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pRho = &rho[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pPast = &past[0];
		pin_ptr<double> pDeltaAnt = &deltaAnt[0];

		compute_portfolio(past_size, size, N, M, H, T, t, r, pSigma, pRho, pCoeff, pPast, pDeltaAnt, price, ci, err, risk, riskFree);

		this->price = price;
		this->ciPrice = ci;
		this->risk = risk;
		this->riskFree = riskFree;
		this->err = err;
	}

	void WrapperClass::getSimulMarket(
		int size, 
		int H, 
		double T, 
		double r, 
		array<double> ^spot, 
		array<double> ^sigma, 
		array<double> ^rho, 
		array<double> ^coeff, 
		array<double> ^past_double)
	{
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pRho = &rho[0];
		pin_ptr<double> pPast = &past_double[0];

		compute_simul_market(size, H, T, r, pSpot, pSigma, pRho, pPast); 
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

		this->err = PaL;
		this->executionTime = execTime;
	}
}
