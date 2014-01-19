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
#include "pnl/pnl_cdf.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <fstream>
#include <omp.h>
using namespace std;

double delta_theorique(double sigma, double T, double S, double K, double r){
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


int main(){	
	double prix;
	double ic;
	double prix1, prix2;
	double ic1, ic2;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));
	
	int const size = 1;
	double strike = 50;
	double spot[size] = {50};//, 80, 100, 120, 110};
	double T = 1;


	double sigma[size] = {0.3};//, 0.2, 0.2, 0.15, 0.15};
	double r = 0.05;
	//double rho[size*(size-1)/2] = {-0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1};
	double coeff[size] = {1};//, 0.2, 0.2, 0.2, 0.2};
	int timeStep = 100;
	//double bu[size] = {90};//, 60, 85, 50, 45};
	//double bl[size] = {30};//, 30, 45, 20, 10};
	int samples = 50000;
<<<<<<< HEAD

=======
	double t = .4;
	int H = 10;
>>>>>>> 8f528c02a7f8637afd07e138de1882685b005544

	//Bs bs(size, r, NULL, sigma, spot, NULL);
//=======
//	double sigma[size] = {0.2};//, 0.2, 0.2, 0.15, 0.15};
//	double r = .05;
//	double coeff[size] = {1.};// , .2, .2, .2, .2};
//	int N = 5;
//	int samples = 50000;
//	double t = .4;
//
//	int H = 10;
//
//	PnlMat *past = pnl_mat_create(size, H+1);
//	PnlVect *delta = pnl_vect_create(size);
//	PnlVect *ic_delta = pnl_vect_create(size);
//>>>>>>> 9e2618f949ec524e22d60f10ba989848521b76ad

	double N = 1;
	double t = 0;//atof(argv[2]);
	double indice = .0;
	 double h = 0.1;
	
	PnlMat* past = pnl_mat_create(size, 0);
	//bs.simul_market(past, N, T, rng);
	//pnl_mat_print(past);
  //PnlMat* past_sub = pnl_mat_create(size, int(indice)+1);
  //pnl_mat_extract_subblock(past_sub, past, 0, size, 0, int(indice)+1);


	std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); 
	for (int i =0; i<100; i++){

	PnlVect* delta = pnl_vect_create(size);
	PnlVect* intconf= pnl_vect_create(size);
	double prix, ic;
	spot[0] = spot[0] + i*0.2;
	Bs bs(size, r, NULL, sigma, spot, NULL);
<<<<<<< HEAD
	//Asian opt(strike, T, timeStep, size);
	//Barrier opt(strike, coeff, bu, bl, T, timeStep, size);
	//Barrier_l opt(strike, coeff, bl, T, timeStep, size);
	//Barrier_u opt(strike, coeff, bu, T, timeStep, size);
	Basket opt(strike, coeff, T, timeStep, size);
	//Performance opt(coeff, T, timeStep, size);

	//Playlist opt(strike, coeff, T, timeStep, size, r);
	MonteCarlo mc(&bs, &opt, rng, 0.1, samples);
	/*
	double mean_prix=0;
	for (int i = 0; i < 1000; i++){
		mc.price(prix, ic);
		mean_prix+=prix;
		cout << i << endl;
	}
	mean_prix = mean_prix / 1000;
	cout << "Prix: " << mean_prix << endl;
	*/
	/*
	mc.price(prix, ic);
	cout << "Prix: " << prix << " Ic: " << ic << endl;

	mc.price(past,t,prix1, ic1);
	cout << "Prix second: " << prix1 << endl;*/
	
	mc.price(prix, ic);
	cout << "Prix pour un spot de   " << spot[0] +i*0.2 << " : " << prix <<" et de ic : " << ic << endl;
	mc.delta(past, t, delta, intconf);
	cout << "delta associé : " << delta <<"\n" << endl;
	free(&bs);
	free(&opt);
	free(&mc);
	free(&delta);
	free(&intconf);
	}
//=======
//	bs.simul_market(past, H, t, rng);
//	mc.delta(past, t, delta, ic_delta);
//	pnl_vect_print(delta);
//	pnl_vect_print(ic_delta);
//>>>>>>> 9e2618f949ec524e22d60f10ba989848521b76ad
	system("pause");
	return 0;
}

//double delta_theorique(double sigma, double T, double S, double K, double r){
//
//}
=======
	Basket opt(strike, coeff, T, N, size);
	MonteCarlo mc(&bs, &opt, rng, 0.01, samples);

	/*Calcul Prix t*/
	bs.simul_market(past, H, t, rng);
	mc.price(past, t, prix, ic);
	double prix_th = prix_theorique(MGET(past, 0, H), strike, r, T-t, sigma[0]);
	printf("Prix(%f): %f \nIc: %f\nPrix theorique: %f\n\n", t, prix, ic, prix_th);


	/*Calcul Delta*/
	bs.simul_market(past, H, t, rng);
	mc.delta(past, t, delta, ic_delta);
	printf("Delta(%f)\n", t);
	pnl_vect_print(delta);
	pnl_vect_print(ic_delta);
	double delta_th = delta_theorique(sigma[0], T-t, MGET(past, 0, H), strike, r);
	printf("Delta théorique: %f\n", delta_th);


	system("pause");
	return 0;
}
>>>>>>> 8f528c02a7f8637afd07e138de1882685b005544
