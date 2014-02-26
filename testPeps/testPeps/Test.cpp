#include "Test.h"
#include "Modelasset.h"
#include "Basket.h"
#include <pnl/pnl_matrix.h>
#include <pnl/pnl_random.h>
#include <pnl/pnl_cdf.h>
#include <iostream>
#include <fstream>

using namespace std;

Test::Test(){

}

Test::Test(MonteCarlos *mc){
	(*this).mc_ = mc;
}

Test::~Test(){
}

MonteCarlos* Test::get_mc() const{
	return mc_;
}

void Test::compute_prix_samples(int samples, bool affiche){
	double prix, ic, prix_th;
	PnlMat* past = pnl_mat_create(0, 0);
	PnlRng* rng = mc_->get_rng();
	ModelAsset *mod = mc_->get_mod();
	double strike = ((Basket *)(mc_->get_opt()))->get_Strike();
	double r = mod->get_r();
	double T = mc_->get_opt()->get_T();
	PnlVect* sigma = mod->get_sigma();

	double sspread, t, mean = 0, mean_th = 0, maxSpread = 0;
	int H;

	for (int k = 0; k < samples; k++){
		t = pnl_rng_uni(rng);
		t = (int)(t*100)/100.;
		H = (int)(t*100);
		pnl_mat_resize(past, 1, H+1);

		mod->simul_market(past, H, t, rng);
		mc_->price(past, t, prix, ic);

		if (t==0)
			prix_th = theo_price(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
		else
			prix_th = theo_price(MGET(past, 0, H), strike, r, T-t, GET(sigma, 0));

		prix_th = (int)(prix_th*1000)/1000.;
		prix = (int)(prix*1000)/1000.;

		sspread = fabs(prix_th-prix);
		mean += prix;
		mean_th += prix_th;

		if (affiche)
			printf("%d %f\t%f %f %f\n", k, t, prix, prix_th, sspread);

		if (sspread > maxSpread)
			maxSpread = sspread;
	}
	printf("Variation entre le moyenne des prix theorique et des prix calcules : %f\n", (fabs(mean-mean_th)/mean_th)*100.);	printf("Max %f\n", maxSpread);
	pnl_mat_free(&past);
}

void Test::compute_delta_samples(int samples, bool affiche){
	PnlMat* past = pnl_mat_create(0, 0);
	PnlRng* rng = mc_->get_rng();
	ModelAsset *mod = mc_->get_mod();
	double strike = ((Basket *)(mc_->get_opt()))->get_Strike();
	double r = mod->get_r();
	double T = mc_->get_opt()->get_T();
	PnlVect* sigma = mod->get_sigma();
	PnlVect* delta = pnl_vect_create(mod->get_size());
	PnlVect* ic_delta = pnl_vect_create(mod->get_size());
	double delta_th;

	double sspread, t, mean = 0, mean_th = 0, maxSpread = 0;
	int H;

	for (int k = 0; k < samples; k++){
		t = pnl_rng_uni(rng);
		t = (int)(t*100)/100.;
		H = (int)(t*100);
		pnl_mat_resize(past, 1, H+1);

		mod->simul_market(past, H, t, rng);
		mc_->delta(past, t, delta, ic_delta);

		if (t==0)
			delta_th = theo_delta(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
		else
			delta_th = theo_delta(MGET(past, 0, H), strike, r, T-t, GET(sigma, 0));

		delta_th = (int)(delta_th*10000)/10000.;
		LET(delta, 0) = (int)(GET(delta, 0)*10000)/10000.;

		sspread = fabs(delta_th-GET(delta, 0));
		mean += GET(delta, 0);
		mean_th += delta_th;

		if (affiche)
			printf("k:%d t:%f\t%f %f %f\n", k, t, GET(delta, 0), delta_th, sspread);

		if (sspread > maxSpread)
			maxSpread = sspread;
	}
	printf("Variation entre le moyenne des deltas theorique et des prix calcules : %f\n", (fabs(mean-mean_th)/mean_th)*100.);
	printf("Max %f\n", maxSpread);
	pnl_mat_free(&past);
}

void Test::compute_prix(int H, double t){
	double prix, prix_th, ic;

	double N = mc_->get_opt()->get_timeStep();
	double T = mc_->get_opt()->get_T();
	PnlRng* rng = mc_->get_rng();
	ModelAsset *mod = mc_->get_mod();
	double r = mod->get_r();
	double strike = ((Basket *)(mc_->get_opt()))->get_Strike();
	PnlVect* sigma = mod->get_sigma();
	int size = mod->get_size();

	if (fmod(T/(double)N, t/(double)H) > 0.0001){
		printf("Erreur: H non adapte \n");
		system("pause");
		return;
	}
	PnlMat* past = pnl_mat_create(size, H+1);
	mod->simul_market(past, H, T, rng);
	mc_->price(past, t, prix, ic);

	if (t==0)
		prix_th = theo_price(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
	else
		prix_th = theo_price(MGET(past, 0, H), strike, r, T-t, GET(sigma, 0));

	printf("%f %f\n", prix, prix_th);

	pnl_mat_free(&past);
}

void Test::compute_delta(int H, double t){
	double delta_th;
	double N = mc_->get_opt()->get_timeStep();
	double T = mc_->get_opt()->get_T();
	PnlRng* rng = mc_->get_rng();
	ModelAsset *mod = mc_->get_mod();
	double r = mod->get_r();
	double strike = ((Basket *)(mc_->get_opt()))->get_Strike();
	PnlVect* sigma = mod->get_sigma();
	PnlVect* delta = pnl_vect_create(mod->get_size());
	PnlVect* ic_delta = pnl_vect_create(mod->get_size());
	int size = mod->get_size();

	if (fmod(T/(double)N, t/(double)H) > 0.0001){
		printf("Erreur: H non adapte \n");
		system("pause");
		return;
	}
	PnlMat* past = pnl_mat_create(size, H+1);
	mod->simul_market(past, H, T, rng);
	pnl_mat_print(past);
	mc_->delta(past, t, delta, ic_delta);
	
	/*
	if (t==0)
		delta_th = theo_delta(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
	else
		delta_th = theo_delta(MGET(past, 0, H), strike, r, T-t, GET(sigma, 0));
	printf("Theo %f\n", delta_th);
	*/
	printf("%f \n", MGET(past, 0, 10)*0.25 + MGET(past, 1, 10)*0.25 + MGET(past, 2, 10)*0.25 + MGET(past, 3, 10)*0.25);
	pnl_vect_print(delta);
	pnl_mat_free(&past);
}

void Test::compute_couv(int H, bool output){
	double N = mc_->get_opt()->get_timeStep();
	double T = mc_->get_opt()->get_T();
	double pl, plTheorique, prix, ic;
	int size = mc_->get_opt()->get_size();

	if (fmod((double)H, (double)N) > 0.0001){
		printf("Erreur: H non adapte \n");
		system("pause");
		return;
	}
	if (output) {
		ofstream fichier1("couv_simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		ofstream fichier2("couv_theorique.txt", ios::out | ios::trunc);
		if(fichier1 && fichier2)
		{
			for (int i = 0; i < 500; i++){
				cout << i << endl;
				PnlMat* past = pnl_mat_create(size, H+1);
				PnlMat* summary = pnl_mat_create(H+1, 6);
				mc_->couv(past, pl, plTheorique, H, T, summary);

				mc_->price(prix, ic);
				double prix_th = theo_price(100, 100, .05, 1, .2);

				cout << "P&L simule: " << pl/prix << endl;
				cout << "P&L calcule: "<< plTheorique/prix_th << endl;
				cout << "  Date" << "     Cours" << "     Delta" << "   Act buy" << "  Delta th" << " Act buy th" << endl;
				pnl_mat_print(summary);
				fichier1 << pl/prix << endl;
				fichier2 << plTheorique/prix_th << endl;
			}
			fichier1.close();
			fichier2.close();
		}else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}else{
		PnlMat* past = pnl_mat_create(size, H+1);
		PnlMat* summary = pnl_mat_create(H+1, 1+3*size+2);
		mc_->couv(past, pl, plTheorique, H, T, summary);
		mc_->price(prix, ic);
		double prix_th = theo_price(100, 100, .05, 1, .2);

		cout << "P&L simulé: " << pl/prix << endl;
		cout << "P&L calculé: "<< plTheorique/prix_th << endl;
		cout << "  Date" << "     Cours" << "     Delta" << "   Act buy" << "  Delta th" << " Act buy th" << endl;
		pnl_mat_print(summary);
	}
}
double Test::theo_price(double S, double K, double r, double T, double sigma){
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

double Test::theo_delta(double S, double K, double r, double T, double sigma){
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
