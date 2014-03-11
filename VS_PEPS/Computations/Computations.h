#pragma once
#define DLLEXP __declspec ( dllexport ) 
namespace Computations{
	DLLEXP void compute_price(double &px, double &ic, double &pxBS, double t, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M);
	DLLEXP void compute_delta(double &delt, double &icd, double &deltBS, double t, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M);
	DLLEXP void compute_price_samples(double &max, double &var, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int M, int samples);
	DLLEXP void compute_delta_samples(double &max, double &var, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int M, int samples);
	DLLEXP void compute_couv(double &pl, double *summary, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M, double &execTime);
}