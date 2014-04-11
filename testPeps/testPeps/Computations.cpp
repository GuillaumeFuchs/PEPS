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

#include <iostream>
#include <fstream>

#include "Test.h"


using namespace std;

int main(){	
	double prix = 0; 
	double ic = 0;
	double pl;
	double plTheorique;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	/*
	int const size = 1;
	double strike = 100;
	double spot[size] = {100};
	double T = 6;
	double sigma[size] = {0.2};	
	double r = .05;
	double coeff[size] = {1.};
	*/
	
	int const size = 4;
	double strike = 100;
	double spot[size] = {100, 100, 100, 100};
	double T = 6;
	double sigma[size] = {0.2, 0.2, 0.2, 0.2};	
	double r = .05;
	double coeff[size] = {0.25, 0.25, 0.25, 0.25};
	double rho[size*(size+1)/2] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	
	int N = 6;
	int samples = 50000;

	Bs mod(size, r, rho, sigma, spot, NULL); 
	//Basket opt(strike, T, N, size, r, coeff); 
	Playlist opt(T, N, size, r, coeff);
	MonteCarlo mc(&mod, &opt, rng, 0.01, samples);
	Test test(&mc);
	
	float temps;
	clock_t tbegin, tend;
	//tbegin = clock();
	//PnlMat* past = pnl_mat_create(1, 1001);
	//mod.simul_market(past, 1000, T, rng);
	//
	//ofstream fichier("Data/past.txt", ios::out | ios::trunc);
	//for (int i = 0; i < 1001; i++){
	//	fichier << MGET(past, 0, i) << endl;
	//}
	//fichier.close();

	//test.compute_price_samples(10000, true, true, past);
	//test.compute_delta_samples(10000, true, true, past);
	//test.compute_price(3 , 1.5);	
	//test.compute_delta(0, 0.);
	//test.compute_couv(6, false);
	test.compute_hedge(6);

	/*tend = clock();
	temps = (float)(tend-tbegin)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);*/
	//pnl_mat_free(&past);
	system("pause"); 

	return 0;
}
