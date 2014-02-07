/* Option librairies */
#include "Asian.h"
#include "Barrier.h"
#include "Barrier_l.h"
#include "Barrier_u.h"
#include "Basket.h"
#include "Performance.h"
#include "Playlist.h"

/* Computation librairies */
#include "Computations.h"
#include "Montecarlo.h"
#include "Bs.h"

/* Others librairies */
#include "pnl/pnl_random.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <omp.h>
using namespace std;

void Moteur::priceOption(double &ic, double &prix, int M, double T, double S0, double K, double sigma, double r, int size, int timeStep)
{
	printf("salut");
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size2 = 1;
	double spot[size2] = {S0};
	double sigma_array[size2]= {sigma};
	double coeff[size2] = {1};

	Bs bs(size2, r, NULL, sigma_array, spot, NULL);
	Basket opt(K, coeff, T, timeStep, size);
	MonteCarlo mc(&bs, &opt, rng, .1, M);
	
	mc.price(prix, ic);
}

void Moteur::couvOption(double &pl, int M, double T, double S0, double K, double sigma, double r, int size, int timeStep)
{
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));
	
	int const size2 = 1;
	double spot[size2] = {S0};
	double sigma_array[size2]= {sigma};
	double coeff[size2] = {1};
	int H = 50;
	PnlMat* past = pnl_mat_create(size2, H+1);

	Bs bs(size2, r, NULL, sigma_array, spot, NULL);
	Basket opt(K, coeff, T, timeStep, size);
	MonteCarlo mc(&bs, &opt, rng, .1, M);

	mc.couv(past, pl, H, T); 
}