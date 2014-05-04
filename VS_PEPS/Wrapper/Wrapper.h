#pragma once
#include "Computations.h"
using namespace System;
 
namespace Wrapper {
 
	public ref class WrapperClass
	{
	private:
		double ciPrice;
		double price;
		array<double> ^delta;
		array<double> ^ciDelta;
		double risk;
		double riskFree;
		double err;
		array<double> ^summary;

	public:
		WrapperClass() {
			ciPrice = price = risk = riskFree = err = 0;
		};
		
		WrapperClass(int size, int H) {
			ciPrice = price = risk = riskFree= err = 0;
			delta = gcnew array<double>(size);
			ciDelta = gcnew array<double>(size);

			summary = gcnew array<double>((2*size+5)*(H+1));
		};

		void computePrice(int past_size, int size, int N, int M, double T, double t, double r, array<double> ^sigma, array<double> ^rho, array<double> ^coeff, array<double> ^past);
		
		void computeDelta(int past_size, int size, int N, int M, double T, double t, double r, array<double> ^sigma, array<double> ^rho, array<double> ^coeff, array<double> ^past);

		void computePortfolio(int past_size, int size, int N, int M, int H, double T, double t, double r, array<double> ^sigma, array<double> ^rho, array<double> ^coeff, array<double> ^past);
		
		void getHedge(int size, int N, int M, int H, double T, double r, array<double> ^spot, array<double> ^sigma, array<double> ^rho, array<double> ^coeff);
		
		void getSimulMarket(int size, int H, double T, double r, array<double> ^spot, array<double> ^sigma, array<double> ^rho, array<double> ^coeff, array<double> ^past_double);

		
		double getPrice() {return price;};
		double getCiPrce() {return ciPrice;};
		array<double> ^getDelta() {return delta;};
		array<double> ^getCiDelta() {return ciDelta;};
		double getRisk() {return risk;};
		double getRiskFree() {return riskFree;};
		double getErr() {return err;};
		array<double> ^getSummary() {return summary;};
	};
}