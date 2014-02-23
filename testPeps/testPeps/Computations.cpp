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
	double spot[size] = {100, 80, 100, 120};
	double T = 1;
	double sigma[size] = {0.2, 0.2, 0.2, 0.15};	
	double r = .05;
	double coeff[size] = {.25, .25, .25, .25};
	double rho[size*(size-1)/2] = {0., 0., 0., 0., 0., 0.};
	int N = 10;
	int samples = 50000;
	int H = 25;
	double t = 0.5;

	

	Bs mod(size, r, rho, sigma, spot, NULL); 
	Basket opt(strike, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, samples);
	Test test(&mc);
	float temps;
    clock_t tbegin, tend;
	while(true){
		//tbegin = clock();
		//test.compute_prix_samples(1000, true);
		//test.compute_delta_samples(1000, true);
		//test.compute_prix(0, 0);	
		//test.compute_delta(10, 0.5);
		test.compute_couv(10, false);
		/*tend = clock();
		temps = (float)(tend-tbegin)/CLOCKS_PER_SEC;
		printf("temps = %f\n", temps);*/
	}

	system("pause");

	return 0;
}
