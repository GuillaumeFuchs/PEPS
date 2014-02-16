#pragma once
#define DLLEXP __declspec ( dllexport ) 
namespace Computations{
	DLLEXP void compute_price_call(double &px, double &ic, double &pxBS, double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);
}