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
		
	void WrapperClass::computeDelta(
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
		pin_ptr<double> pDelta = &delta[0];
		pin_ptr<double> pCiDelta = &ciDelta[0];

		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];
		pin_ptr<double> pPast = &past[0];
		
		compute_delta(past_size, size, N, M, T, t, r, pSigma, pCoeff, pRho, pPast, pDelta, pCiDelta);
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
		pin_ptr<double> pDeltaAnt = &delta[0];

		compute_portfolio(past_size, size, N, M, H, T, t, r, pSigma, pRho, pCoeff, pPast, pDeltaAnt, price, ci, err, risk, riskFree);

		this->price = price;
		this->ciPrice = ci;
		this->risk = risk;
		this->riskFree = riskFree;
		this->err = err;
	}
	
	void WrapperClass::getHedge(
		int size, 
		int N,
		int M,
		int H,
		double T,
		double r,
		array<double> ^spot, 
		array<double> ^sigma,
		array<double> ^rho,
		array<double> ^coeff)
	{
		double PaL, execTime;
		pin_ptr<double> pSummary = &summary[0];

		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pCoeff = &coeff[0];
		pin_ptr<double> pRho = &rho[0];

		compute_couv(size, N, M, H, T, r, PaL, pSpot, pSigma, pRho, pCoeff, pSummary);

		this->err = PaL;
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
}
