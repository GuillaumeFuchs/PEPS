#include "Asian.h"
#include "Barrier.h"
#include "Barrier_l.h"
#include "Barrier_u.h"
#include "Basket.h"
#include "Performance.h"
#include "Playlist.h"

/* Computation librairies */
#include "Computations.h"
#include "Montecarlos.h"
#include "Montecarlo.h"
#include "Modelasset.h"
#include "Bs.h"

/* Others librairies */
#include "pnl/pnl_random.h"
#include "pnl/pnl_cdf.h"
#include <cstdio>
#include <ctime>
#include "Test.h"

using namespace std;

void Computations::compute_price(
	int past_size,
	int size,
	int N,
	int M,
	double T,
	double t,
	double r, 
	double &px, 
	double &ic, 
	double *sigma, 
	double *coeff, 
	double *rho,
	double *past_double)
{
	PnlMat* past = pnl_mat_create_from_ptr(size, past_size, past_double);

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	double* spot = (double *)malloc(size*sizeof(double));
	for (int d = 0; d < size; d++){
		spot[d] = past_double[(d+1)*past_size-1];
	}

	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);
	
	mc.price(t, px, ic, past);
	
	pnl_mat_free(&past);
	pnl_rng_free(&rng);
	free(spot);
}

void Computations::compute_delta(
	int past_size,
	int size,
	int N,
	int M,
	double T,
	double t,
	double r, 
	double *sigma, 
	double *coeff, 
	double *rho,
	double *past_double,
	double *delta,
	double *ic_delta)
{
	PnlMat* past = pnl_mat_create_from_ptr(size, past_size, past_double);

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));
	
	double* spot = (double *)malloc(size*sizeof(double));
	for (int d = 0; d < size; d++){
		spot[d] = past_double[(d+1)*past_size-1];
	}

	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);

	PnlVect* deltaPnl = pnl_vect_create(size);
	PnlVect* ic_deltaPnl = pnl_vect_create(size);

	mc.delta(t, deltaPnl, ic_deltaPnl, past);

	pnl_vect_free(&deltaPnl);
	pnl_vect_free(&ic_deltaPnl);
	pnl_rng_free(&rng);
	free(spot);
}

void Computations::compute_portfolio(
	int past_size,
	int size,
	int N,
	int M,
	int H,
	double T,
	double t,
	double r,
	double *sigma,
	double *rho,
	double *coeff,
	double *past_double,
	double *delta_ant_double,
	double &price,
	double &ci,
	double &err,
	double &risk_portion,
	double &risk_free_portion)
{
	PnlMat* past = pnl_mat_create_from_ptr(size, past_size, past_double);

	double* spot = (double *)malloc(size*sizeof(double));
	for (int d = 0; d < size; d++){
		spot[d] = past_double[(d+1)*past_size-1];
	}

	PnlVect* delta_ant = pnl_vect_create_from_ptr(size, delta_ant_double);

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);

	mc.compute_portfolio(H, T, t, risk_free_portion, risk_portion, price, ci, err, delta_ant, past);

	for (int d = 0; d < size; d++)
		delta_ant_double[d]= GET(delta_ant, d);

	pnl_rng_free(&rng);
	pnl_mat_free(&past);
	free(spot);
}

void Computations::compute_simul_market(
	int size,
	int H, 
	double T,
	double r,
	double *spot,
	double *sigma,
	double *rho,
	double *past_double)
{
	PnlMat* past = pnl_mat_create(size, H+1);
	
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	Bs mod(size, r, rho, sigma, spot, NULL);

	mod.simul_market(H, T, past, rng);

	for (int i = 0; i < H+1; i++){
		for (int d = 0; d < size; d++){
			past_double[d*(H+1)+i] = MGET(past, d, i);
		}
	}
}



void Computations::compute_couv(
	int size, 
	int N, 
	int M, 
	int H, 
	double T, 
	double r, 
	double &pl, 
	double *spot, 
	double *sigma, 
	double *rho, 
	double *coeff, 
	double *summary)
{
	double prix;
	double ic;
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);
	PnlMat* past = pnl_mat_create(size, H+1);
	PnlMat* summaryV = pnl_mat_create(H+1, size*3+1);

	pnl_rng_sseed(rng, time(NULL));

	mc.couv(H, T, pl, past, summaryV);

	mc.price(prix, ic);
	pl /= prix;

	for (int i = 0; i<H+1; i++){
		for (int j = 0; j<2*size+5; j++){
			summary[i*(2*size+5)+j] = MGET(summaryV, i, j);
		}
	}
	pnl_rng_free(&rng);
	pnl_mat_free(&past);
	pnl_mat_free(&summaryV);
}