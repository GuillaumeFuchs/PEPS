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
		array<double> ^summary;

	public:
		WrapperClass() {
			intConfiancePrix = prix = prixBS = intConfianceDelta = delta = deltaBS = mxP = vrP = mxD = vrD = pl = plt = 0;
			summary = gcnew array<double>(51 * 6);
		};
		void getPriceCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);
		void getDeltaCallEuro(double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);

		void getPriceCallEuroSamples(double S0, double K, double sigma, double r, double T, int N, int M, int samples);
		void getDeltaCallEuroSamples(double S0, double K, double sigma, double r, double T, int N, int M, int samples);
		void getCouvCallEuro(double S0, double K, double sigma, double r, double T, int N, int H, int M);

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
		array<double> ^getSummary() {return summary;};

	};
}