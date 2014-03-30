#pragma once
#include "Computations.h"
using namespace System;
 
namespace Wrapper {
 
	public ref class WrapperClass
	{
	private:
		double intConfiancePrix;
		double prix;

		double intConfianceDelta;
		double delta;

		double mxP;
		double vrP;

		double mxD;
		double vrD;

		double pl;
		double executionTime;
		array<double> ^summary;

	public:
		WrapperClass() {
			intConfiancePrix = prix = intConfianceDelta = delta = mxP = vrP = mxD = vrD = pl = 0;
		};
		
		WrapperClass(int size, int H) {
			intConfiancePrix = prix = intConfianceDelta = delta = mxP = vrP = mxD = vrD = pl = 0;
			summary = gcnew array<double>((2*size+5)*(H+1));
		};

		void getPrice(double t, int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M);
		void getDelta(double t, int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M);

		void getHedge(int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M);

		double getPrice() {return prix;};
		double getICP() {return intConfiancePrix;};

		double getDelta() {return delta;};
		double getICD() {return intConfianceDelta;};

		double getMxP() {return mxP;};
		double getVrP() {return vrP;};

		double getMxD() {return mxD;};
		double getVrD() {return vrD;};

		double getPL() {return pl;};
		double getExecutionTime() {return executionTime;};
		array<double> ^getSummary() {return summary;};
	};
}