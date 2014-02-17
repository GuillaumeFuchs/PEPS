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

void Computations::compute_delta_call(double &delt, double &icd, double &deltBS, double t, double S0, double K, double sigma, double r, double T, int N, int H, int M){
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size = 1;
	double spot[size] = {S0};
	double sigmaV[size] = {sigma};
	double coeff[size] = {1};

	Bs mod(size, r, NULL, sigmaV, spot, NULL);
	Basket opt(K, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);

	PnlVect* delta = pnl_vect_create(size);
	PnlVect* ic_delta = pnl_vect_create(size);

	if (fmod(T/(double)N, t/(double)H) > 0.0001){
		return;
	}

	PnlMat* past = pnl_mat_create(1, H+1);
	mod.simul_market(past, H, T, rng);
	mc.delta(past, t, delta, ic_delta);

	if (t==0)
		deltBS = Test::theo_delta(MGET(past, 0, 0), K, r, T-t, sigmaV[0]);
	else
		deltBS = Test::theo_delta(MGET(past, 0, H), K, r, T-t, sigmaV[0]);
	 
	delt = GET(delta, 0);
	icd = GET(ic_delta, 0);

	pnl_vect_free(&delta);
	pnl_vect_free(&ic_delta);
	pnl_mat_free(&past);
	pnl_rng_free(&rng);
}

void Computations::compute_price_call_samples(double &max, double &var, double S0, double K, double sigma, double r, double T, int N, int M, int samples){
	max = 0;
	double prix, ic, prix_th;
	
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size = 1;
	double spot[size] = {S0};
	double sigmaV[size] = {sigma};
	double coeff[size] = {1};

	Bs mod(size, r, NULL, sigmaV, spot, NULL);
	Basket opt(K, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);

	double sspread, t, mean = 0, mean_th = 0;
	int H;

	PnlMat* past = pnl_mat_create(0, 0);
	for (int k = 0; k < samples; k++){
		t = pnl_rng_uni(rng);
		t = (int)(t*100)/100.;
		H = (int)(t*100);
		pnl_mat_resize(past, 1, H+1);

		mod.simul_market(past, H, t, rng);
		mc.price(past, t, prix, ic);

		if (t==0)
			prix_th = Test::theo_price(MGET(past, 0, 0), K, r, T-t, sigmaV[0]);
		else
			prix_th = Test::theo_price(MGET(past, 0, H), K, r, T-t, sigmaV[0]);

		prix_th = (int)(prix_th*1000)/1000.;
		prix = (int)(prix*1000)/1000.;

		sspread = fabs(prix_th-prix);
		mean += prix;
		mean_th += prix_th;


		if (sspread > max)
			max = sspread;
	}
	var = fabs(mean-mean_th)/mean_th*100.;
	pnl_mat_free(&past);
}

void Computations::compute_delta_call_samples(double &max, double &var, double S0, double K, double sigma, double r, double T, int N, int M, int samples){
	max = 0;
	
	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size = 1;
	double spot[size] = {S0};
	double sigmaV[size] = {sigma};
	double coeff[size] = {1};
	PnlVect* delta = pnl_vect_create(size);
	PnlVect* ic_delta = pnl_vect_create(size);
	double delta_th;

	Bs mod(size, r, NULL, sigmaV, spot, NULL);
	Basket opt(K, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);

	double sspread, t, mean = 0, mean_th = 0;
	int H;

	PnlMat* past = pnl_mat_create(0, 0);
	for (int k = 0; k < samples; k++){
		t = pnl_rng_uni(rng);
		t = (int)(t*100)/100.;
		H = (int)(t*100);
		pnl_mat_resize(past, 1, H+1);

		mod.simul_market(past, H, t, rng);
		mc.delta(past, t, delta, ic_delta);

		if (t==0)
			delta_th = Test::theo_delta(MGET(past, 0, 0), K, r, T-t, sigmaV[0]);
		else
			delta_th = Test::theo_delta(MGET(past, 0, H), K, r, T-t, sigmaV[0]);

		delta_th = (int)(delta_th*1000)/1000.;
		LET(delta, 0) = (int)(GET(delta, 0)*1000)/1000.;

		sspread = fabs(delta_th-GET(delta, 0));
		mean += GET(delta, 0);
		mean_th += delta_th;


		if (sspread > max)
			max = sspread;
	}
	var = fabs(mean-mean_th)/mean_th*100.;
	pnl_mat_free(&past);
}

void Computations::compute_couv_call(double &pl, double &plt, double *summary, double S0, double K, double sigma, double r, double T, int N, int H, int M){
	if (fmod((double)H, (double)N) > 0.0001){
		return;
	}
	pl = 0.;
	plt = 0.;
	
	double prix, ic;

	int const size = 1;
	double spot[size] = {S0};
	double sigmaV[size] = {sigma};
	double coeff[size] = {1};

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));
	Bs mod(size, r, NULL, sigmaV, spot, NULL);
	Basket opt(K, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, M);

	PnlMat* past = pnl_mat_create(1, H+1);
	PnlMat* summaryV = pnl_mat_create(H+1, 6);
	mc.couv(past, pl, plt, H, T, summaryV);

	mc.price(prix, ic);
	double prix_th = Test::theo_price(100, 100, .05, 1, .2);

	pl /= prix;
	plt /= prix_th;

	int compteur = -1;
	for (int i = 0; i<H+1; i++){
		for (int d = 0; d<6; d++){
			summary[++compteur] = MGET(summaryV, i, d);
		}
	}
}