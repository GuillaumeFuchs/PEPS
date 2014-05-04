#pragma once
#define DLLEXP __declspec ( dllexport ) 
namespace Computations{
	DLLEXP void compute_price(int past_size, int size, int N, int M, double T, double t, double r, double &px, double &ic, double *sigma, double *coeff, double *rho, double *past_double);
	
	DLLEXP void compute_delta(int past_size, int size, int N, int M, double T, double t, double r, double *sigma, double *coeff, double *rho, double *past_double, double *delta, double *ic_delta);

	DLLEXP void compute_portfolio(int past_size, int size, int N, int M, int H, double T, double t, double r, double* sigma, double *rho, double *coeff, double *past_double, double *delta_ant_double, double &price, double &ci, double &pl, double &risk_portion, double &risk_free_portion);

	DLLEXP void compute_simul_market(int size, int H, double T, double r, double *spot, double *sigma, double *rho, double *past_double);

	DLLEXP void compute_couv(int size, int N, int M, int H, double T, double r, double &pl, double *spot, double *sigma, double *rho, double *coeff, double *summary);
	

}