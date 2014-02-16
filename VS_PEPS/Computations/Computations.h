#pragma once
#define DLLEXP __declspec ( dllexport ) 
namespace Computations{
	DLLEXP void compute_price_call(double &px, double &ic, double &pxBS, double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);
	DLLEXP void compute_delta_call(double &delt, double &icd, double &deltBS, double t, double S0, double K, double sigma, double r, double T, int N, int H, int M);
	DLLEXP void compute_price_call_samples(double &max, double &var, double S0, double K, double sigma, double r, double T, int N, int M, int samples);
	DLLEXP void compute_delta_call_samples(double &max, double &var, double S0, double K, double sigma, double r, double T, int N, int M, int samples);
	DLLEXP void compute_couv_call(double &pl, double &plt, double **summary, double S0, double K, double sigma, double r, double T, int N, int H, int M, double &temp);
}