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
#include <omp.h>
#include <fstream>

#include <vector>
#include <algorithm>


using namespace std;

double delta_theorique(double S, double K, double r, double T, double sigma){
	double q, bound;
	int status;
	int which = 1;
	double p;
	double mean = 0.;
	double sd = 1.;
	double d = 1./(sigma * sqrt(T)) * (log(S/K) + (r + sigma * sigma /2)*T);

	pnl_cdf_nor(&which, &p, &q, &d, &mean, &sd, &status, &bound);
	return p;
}

double prix_theorique(double S, double K, double r, double T, double sigma){
	double q, bound;
	int status;
	int which = 1;
	double p1, p2;
	double mean = 0.;
	double sd = 1.;
	double d1 = 1./(sigma * sqrt(T)) * (log(S/K) + (r + sigma * sigma /2)*T);
	double d2 = d1 - sigma * sqrt(T);

	pnl_cdf_nor(&which, &p1, &q, &d1, &mean, &sd, &status, &bound);
	pnl_cdf_nor(&which, &p2, &q, &d2, &mean, &sd, &status, &bound);

	return S*p1 - K*exp(-r*T)*p2;
}

int compute_prix(double prix, double ic, MonteCarlos *mc, ModelAsset *mod, PnlMat *past, int H, double t, double *spot, double strike, double r, double T, double* sigma, PnlRng *rng, vector<double> *v){
	mod->simul_market(past, H, t, rng);
	mc->price(past, t, prix, ic);
	double prix_th;
	if (t==0)
		prix_th = prix_theorique(spot[0], strike, r, T-t, sigma[0]);
	else
		prix_th = prix_theorique(MGET(past, 0, H), strike, r, T-t, sigma[0]);
	
	printf("%f\t%f %f\n\n", t, prix, prix_th);
	if (fabs(prix-prix_th) > 0.5){
		v->push_back(t);
		return 1;
	}
	return 0;
}
double compute_delta(PnlVect *delta, PnlVect* ic_delta, MonteCarlos *mc, ModelAsset *mod, PnlMat* past, int H, double t, double strike ,double r, double T, double *sigma, PnlRng *rng, vector<double> *v){
	mod->simul_market(past, H, t, rng);
	mc->delta(past, t, delta, ic_delta);
	double delta_th;
	if (t==0)
		delta_th = delta_theorique(MGET(past, 0, 0), strike, r, T-t, sigma[0]);
	else
		delta_th = delta_theorique(MGET(past, 0, H), strike, r, T-t, sigma[0]);
	
	printf("Delta(%f)\n", t);
	pnl_vect_print(delta);
	printf("Delta théorique: %f\n\n", delta_th);

	if (fabs(GET(delta, 0) - delta_th) > 0.5){
		v->push_back(t);
		return 1;
	}
	return 0;
}

int main(){	
	double prix = 0; 
	double ic = 0;
	double pl;
	double plTheorique;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size = 1;
	double strike = 100;
	double spot[size] = {100};//, 80, 100, 120, 110};
	double T = 1;
	double sigma[size] = {0.2};//, 0.2, 0.2, 0.15, 0.15};	
	double r = .05;
	double coeff[size] = {1.};// , .2, .2, .2, .2};
	int N = 10;
	int samples = 20000;
	int H = 45;

	//PnlMat *past = pnl_mat_create(size, H+1);    
	PnlVect *delta = pnl_vect_create(size);
	PnlVect *ic_delta = pnl_vect_create(size);
	Bs mod(size, r, NULL, sigma, spot, NULL);
	Basket opt(strike, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, samples);
	
	vector<double> v;
	int rejet = 0;
	double t;
	for (int k = 0; k < 1000; k++){
		t = pnl_rng_uni(rng);
		PnlMat* past = pnl_mat_create(1, (int)(t*100)+1);
		//rejet += compute_prix(prix, ic, &mc, &mod, past, (int)(t*100), (int)(t*100)/100., spot, strike, r, T, sigma, rng, &v);
		rejet += compute_delta(delta, ic_delta, &mc, &mod, past, (int)(t*100), (int)(t*100)/100. , strike, r, T, sigma, rng, &v);
		pnl_mat_free(&past);
	}
	printf("Taux de prix dont l'écart avec prix_th est superieur a 0,5: %f \n", (double)rejet*100./1000.); 
	sort(v.begin(), v.end());
	for (vector<double>::iterator it=v.begin(); it!=v.end(); ++it)
		cout << *it << endl;

	/*Couverture
	ofstream fichier1(c"ouv_simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
	ofstream fichier2("couv_theorique.txt", ios::out | ios::trunc);
	if(fichier1 && fichier2)
	{
	for (int i = 0; i < 500; i++){
	mc.couv(past, pl, plTheorique, H, T);
	/*mc.price(prix, ic);
	double prix_th = prix_theorique(100., 100., .05, 1., .2);
	cout << endl;
	cout << pl/prix << endl;
	cout << plTheorique/prix_th << endl;
	/*
	fichier1 << pl/prix << endl;
	fichier2 << plTheorique/prix_th << endl;
	}
	fichier1.close();
	fichier2.close();
	}else
	cerr << "Impossible d'ouvrir le fichier !" << endl;
	*/

	system("pause");

	return 0;
}
