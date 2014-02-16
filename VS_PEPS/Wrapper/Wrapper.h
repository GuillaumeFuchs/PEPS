#pragma once
#include "Computations.h"
using namespace System;
 
namespace Wrapper {
 
	public ref class WrapperClass
	{
	private:
		double intConfiance;
		double prix;
		double prixBS;
	public:
		WrapperClass() {intConfiance = prix = 0;};
		void getPriceCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);
		double getPrice() {return prix;};
		double getPriceBS() {return prixBS;};
		double getIC() {return intConfiance;};
	};
}