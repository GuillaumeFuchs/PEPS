#pragma once
#include "Computations.h"
using namespace System;
 
namespace Wrapper {
 
	public ref class WrapperClass
	{
	private:
		double intConfiancePrix;
		double prix;
		double prixBS;

		double intConfianceDelta;
		double delta;
		double deltaBS;

		double mxP;
		double vrP;

		double mxD;
		double vrD;

		double pl;
		double plt;
		double executionTime;
		array<double> ^summary;

	public:
		WrapperClass() {
			intConfiancePrix = prix = prixBS = intConfianceDelta = delta = deltaBS = mxP = vrP = mxD = vrD = pl = plt = 0;
		};
		
		WrapperClass(int size, int H) {
			intConfiancePrix = prix = prixBS = intConfianceDelta = delta = deltaBS = mxP = vrP = mxD = vrD = pl = plt = 0;
			summary = gcnew array<double>((3*size+1)*(H+1));
		};

		void getPriceCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);
		void getDeltaCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);

		void getPriceCallEuroSamples(double S0, double K, double sigma, double r, double T, int N, int M, int samples);
		void getDeltaCallEuroSamples(double S0, double K, double sigma, double r, double T, int N, int M, int samples);
		void getCouvCallEuro(int size, array<double> ^spot, double K, array<double> ^sigma, double r, array<double> ^coeff, array<double> ^rho, double T, int N, int H, int M);

		double getPrice() {return prix;};
		double getPriceBS() {return prixBS;};
		double getICP() {return intConfiancePrix;};

		double getDelta() {return delta;};
		double getDeltaBS() {return deltaBS;};
		double getICD() {return intConfianceDelta;};

		double getMxP() {return mxP;};
		double getVrP() {return vrP;};

		double getMxD() {return mxD;};
		double getVrD() {return vrD;};

		double getPL() {return pl;};
		double getPLT() {return plt;};
		double getExecutionTime() {return executionTime;};
		array<double> ^getSummary() {return summary;};
	};
}