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

void Computations::compute_price(double &px, double &ic, double t, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M){
	if (fmod(T/(double)N, t/(double)H) > 0.0001)
		return;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);
	PnlMat* past = pnl_mat_create(size, H+1);

	pnl_rng_sseed(rng, time(NULL));
	
	mod.simul_market(H, T, past, rng);
	mc.price(t, px, ic, past);

	pnl_mat_free(&past);
	pnl_rng_free(&rng);
}

void Computations::compute_delta(double &delt, double &icd, double t, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M){
	if (fmod(T/(double)N, t/(double)H) > 0.0001)
		return;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);
	PnlVect* delta = pnl_vect_create(size);
	PnlVect* ic_delta = pnl_vect_create(size);
	PnlMat* past = pnl_mat_create(size, H+1);

	pnl_rng_sseed(rng, time(NULL));

	mod.simul_market(H, T, past, rng);
	mc.delta(t, delta, ic_delta, past);

	pnl_vect_free(&delta);
	pnl_vect_free(&ic_delta);
	pnl_mat_free(&past);
	pnl_rng_free(&rng);
}

void Computations::compute_couv(double &pl, double *summary, int size, double *spot, double K, double *sigma, double r, double *coeff, double *rho, double T, int N, int H, int M, double &execTime){
	if (fmod((double)H, (double)N) > 0.0001){
		return;
	}
	double prix;
	double ic;
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);
	PnlMat* past = pnl_mat_create(size, H+1);
	PnlMat* summaryV = pnl_mat_create(H+1, size*3+1);
    clock_t tbegin, tend;

	pnl_rng_sseed(rng, time(NULL));

	tbegin = clock();
	mc.couv(H, T, pl, past, summaryV);
	tend = clock();
	execTime = (float)(tend-tbegin)/CLOCKS_PER_SEC;

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
	double &pl,
	double &risk_portion,
	double &risk_free_portion
	)
{
	PnlMat* past = pnl_mat_create_from_ptr(size, past_size, past_double);

	double* spot = new double(size*sizeof(double));
	for (int d = 0; d < size; d++)
		spot[d] = past_double[(d+1)*past_size-1];

	PnlVect* delta_ant = pnl_vect_create_from_ptr(size, delta_ant_double);

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	Bs mod(size, r, rho, sigma, spot, NULL);
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);

	mc.compute_portfolio(H, T, t, risk_free_portion, risk_portion, pl, delta_ant, past);

	pnl_rng_free(&rng);
	pnl_mat_free(&past);
	free(spot);
}