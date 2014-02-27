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

int main(){	
	double prix = 0; 
	double ic = 0;
	double pl;
	double plTheorique;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size = 4;
	double strike = 100;
	double spot[size] = {100, 100, 100, 100};
	double T = 6;
	double sigma[size] = {0.2, 0.2, 0.2, 0.2};	
	double r = .05;
	double coeff[size] = {.25, .25, .25, .25};
	double rho[size*(size-1)/2] = {0., 0., 0., 0., 0., 0.};

	//int const size = 1;
	//double strike = 100;
	//double spot[size] = {100 };
	//double T = 1;
	//double sigma[size] = {0.2};	
	//double r = .05;
	//double coeff[size] = {1.};

	int N = 6;
	int samples = 50000;

	Bs mod(size, r, rho, sigma, spot, NULL); 
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, samples);
	Test test(&mc);
	
	float temps;
	clock_t tbegin, tend;
	//tbegin = clock();
	//test.compute_prix_samples(1000, true);
	//test.compute_delta_samples(1000, true);
	//test.compute_prix(0 , 0.);	
	//test.compute_delta(0, 0.);
	test.compute_couv(18, false);
	/*tend = clock();
	temps = (float)(tend-tbegin)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);*/

	system("pause");

	return 0;
}
