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

int main(){	
	double prix;
	double ic;
	double pl;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));
	
	int const size = 1;
	double strike = 100;
	double spot[size] = {100};//, 80, 100, 120, 110};
	double T = 1;
	double sigma[size] = {0.2};//, 0.2, 0.2, 0.15, 0.15};
	double r = .05;
	double coeff[size] = {1.};// , .2, .2, .2, .2};
	int N = 5;
	int samples = 50000;
	double t = .8;

	int H = 8;

	PnlMat *past = pnl_mat_create(size, H+1);

	Bs bs(size, r, NULL, sigma, spot, NULL);
	Basket opt(strike, coeff, T, N, size);
	MonteCarlo mc(&bs, &opt, rng, 0.1, samples);

	bs.simul_market(past, H, t, rng);
	pnl_mat_print(past);
	mc.price(past, t, prix, ic);
	cout << "Prix: " << prix << " Ic: " << ic << endl;
	system("pause");
	return 0;
}