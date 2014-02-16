#include "stdafx.h"
 
#include "Wrapper.h"
 
using namespace Computations;
namespace Wrapper {
	void WrapperClass::getPriceCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M) {
		double ic, px, pxBS;
		compute_price_call(px, ic, pxBS, t, S0, K, sigma, r, T, N, H, M);
		this->intConfiance = ic;
		this->prix = px;
		this->prixBS = pxBS;
	}
}
