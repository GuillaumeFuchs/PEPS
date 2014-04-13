#pragma once
#define DLLEXP __declspec ( dllexport ) 
namespace Computations{
	DLLEXP void compute_price(double &px, double &ic, double t, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M);
	DLLEXP void compute_delta(double &delt, double &icd, double t, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M);
	DLLEXP void compute_couv(double &pl, double *summary, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M, double &execTime);
	DLLEXP void compute_portfolio(int past_size, int size, int N, int M, int H, double T, double t, double r, double* sigma, double *rho, double *coeff, double *past_double, double *delta_ant_double, double &pl, double &risk_portion, double &risk_free_portion);
}