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

void Computations::compute_price_call(double &px, double &ic, double &pxBS, double t, double S0, double K, double sigma, double r, double T, int N, int H, int M){
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size = 1;
	double spot[size] = {S0};
	double sigmaV[size] = {sigma};
	double coeff[size] = {1};

	Bs mod(size, r, NULL, sigmaV, spot, NULL);
	Basket opt(K, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);


	if (fmod(T/(double)N, t/(double)H) > 0.0001){
		return;
	}

	PnlMat* past = pnl_mat_create(1, H+1);
	mod.simul_market(past, H, T, rng);
	mc.price(past, t, px, ic);

	if (t==0)
		pxBS = Test::theo_price(MGET(past, 0, 0), K, r, T-t, sigmaV[0]);
	else
		pxBS = Test::theo_price(MGET(past, 0, H), K, r, T-t, sigmaV[0]);
	 
	pnl_mat_free(&past);
	pnl_rng_free(&rng);
}