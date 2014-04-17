#pragma once
#include "Computations.h"
using namespace System;
 
namespace Wrapper {
 
	public ref class WrapperClass
	{
	private:
		double ciPrice;
		double price;
		double risk;
		double riskFree;
		double err;
		array<double> ^deltaAnt;


		double intConfianceDelta;
		double delta;

		double mxP;
		double vrP;

		double mxD;
		double vrD;


		double executionTime;
		array<double> ^summary;

	public:
		WrapperClass() {
			ciPrice = price = risk = riskFree = intConfianceDelta = delta = mxP = vrP = mxD = vrD = err = 0;
		};
		
		WrapperClass(int size, int H) {
			ciPrice = price = risk = riskFree = intConfianceDelta = delta = mxP = vrP = mxD = vrD = err = 0;
			deltaAnt = gcnew array<double>(size);

			summary = gcnew array<double>((2*size+5)*(H+1));
		};

		void computePrice(int past_size, int size, int N, int M, double T, double t, double r, array<double> ^sigma, array<double> ^rho, array<double> ^coeff, array<double> ^past);

		void computePortfolio(int past_size, int size, int N, int M, int H, double T, double t, double r, array<double> ^sigma, array<double> ^rho, array<double> ^coeff, array<double> ^past);

		void getDelta(double t, int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M);

		void getHedge(int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M);

		
		void getSimulMarket(int size, int H, double T, double r, array<double> ^spot, array<double> ^sigma, array<double> ^rho, array<double> ^coeff, array<double> ^past_double);

		double getPrice() {return price;};
		double getCIP() {return ciPrice;};
		double getRisk() {return risk;};
		double getRiskFree() {return riskFree;};
		array<double> ^getDeltaAnt() {return deltaAnt;};

		double getDelta() {return delta;};
		double getICD() {return intConfianceDelta;};

		double getMxP() {return mxP;};
		double getVrP() {return vrP;};

		double getMxD() {return mxD;};
		double getVrD() {return vrD;};

		double getErr() {return err;};
		double getExecutionTime() {return executionTime;};
		array<double> ^getSummary() {return summary;};
	};
}