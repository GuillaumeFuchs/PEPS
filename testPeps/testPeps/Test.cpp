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

void Test::compute_price_samples(int samples, bool display, bool output, PnlMat* past){
	double price, ic, price_theo;
	PnlMat* past_extract = pnl_mat_create(0, 0);
	PnlRng* rng = mc_->get_rng();
	ModelAsset *mod = mc_->get_mod();
	double strike = ((Basket *)(mc_->get_opt()))->get_Strike();
	double r = mod->get_r();
	double T = mc_->get_opt()->get_T();
	PnlVect* sigma = mod->get_sigma();

	double t;
	int temp_H;

	if (output) {
		ofstream fichier1("Data/price_simul.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		ofstream fichier2("Data/price_theo.txt", ios::out | ios::trunc);
		ofstream fichier3("Data/time.txt", ios::out | ios::trunc);
		if(fichier1 && fichier2)
		{
			for (int k = 0; k < 1001; k++){
				cout << k << endl;

				t = k/1000.;

				temp_H = (int)(t*1000);
				pnl_mat_resize(past_extract, 1, temp_H+1);

				for (int i = 0; i < temp_H+1; i++){
					MLET(past_extract, 0, i) = MGET(past, 0, i); 
				}

				mc_->price(past_extract, t, price, ic);

				if (t==0)
					price_theo = theo_price(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
				else
					price_theo = theo_price(MGET(past, 0, temp_H), strike, r, T-t, GET(sigma, 0));

				price_theo = (int)(price_theo*1000)/1000.;
				price = (int)(price*1000)/1000.;

				fichier1 << price << endl;
				fichier2 << price_theo << endl;
				fichier3 << t << endl;
			}
			fichier1.close();
			fichier2.close();
		}else
			cerr << "Fail to open files !" << endl;
	}else{
		double sspread, mean = 0, mean_th = 0, maxSpread = 0;
		for (int k = 0; k < 1001; k++){
			
			t = k/1000.;
			temp_H = (int)(t*1000);
			pnl_mat_resize(past_extract, 1, temp_H+1);

			for (int i = 0; i < temp_H+1; i++){
				MLET(past_extract, 0, i) = MGET(past, 0, i); 
			}

			mc_->price(past_extract, t, price, ic);

			if (t==0)
				price_theo = theo_price(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
			else
				price_theo = theo_price(MGET(past, 0, temp_H), strike, r, T-t, GET(sigma, 0));

			price_theo = (int)(price_theo*1000)/1000.;
			price = (int)(price*1000)/1000.;

			sspread = fabs(price_theo-price);
			mean += price;
			mean_th += price_theo;

			if (display)
				printf("%d %f \t%f %f %f\n", k, t, price, price_theo, sspread);

			if (sspread > maxSpread)
				maxSpread = sspread;
		}
		printf("Variation entre le moyenne des price theorique et des price calcules : %f\n", (fabs(mean-mean_th)/mean_th)*100.);	printf("Max %f\n", maxSpread);
	}
}

void Test::compute_delta_samples(int samples, bool display, bool output, PnlMat* past){
	PnlMat* past_extract = pnl_mat_create(0, 0);

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
	int temp_H;

	if (output) {
		ofstream fichier1("Data/delta_simul.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
		ofstream fichier2("Data/delta_theo.txt", ios::out | ios::trunc);
		if(fichier1 && fichier2)
		{
			for (int k = 0; k < 1001; k++){
				cout << k << endl;

				t = k/1000.;
				temp_H = (int)(t*1000);
				pnl_mat_resize(past_extract, 1, temp_H+1);

				for (int i = 0; i < temp_H+1; i++){
					MLET(past_extract, 0, i) = MGET(past, 0, i); 
				}

				mc_->delta(past_extract, t, delta, ic_delta);

				if (t==0)
					delta_th = theo_delta(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
				else
					delta_th = theo_delta(MGET(past, 0, temp_H), strike, r, T-t, GET(sigma, 0));

				delta_th = (int)(delta_th*10000)/10000.;
				LET(delta, 0) = (int)(GET(delta, 0)*10000)/10000.;

				fichier1 << GET(delta, 0) << endl;
				fichier2 << delta_th << endl;
			}
			fichier1.close();
			fichier2.close();
		}else
			cerr << "Fail to open files !" << endl;
	}else{

		for (int k = 0; k < 1001; k++){
			t = k/1000.;
			temp_H = (int)(t*1000);
			pnl_mat_resize(past_extract, 1, temp_H+1);

			for (int i = 0; i < temp_H+1; i++){
				MLET(past_extract, 0, i) = MGET(past, 0, i); 
			}

			mc_->delta(past_extract, t, delta, ic_delta);

			if (t==0)
				delta_th = theo_delta(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
			else
				delta_th = theo_delta(MGET(past, 0, temp_H), strike, r, T-t, GET(sigma, 0));

			delta_th = (int)(delta_th*10000)/10000.;
			LET(delta, 0) = (int)(GET(delta, 0)*10000)/10000.;

			sspread = fabs(delta_th-GET(delta, 0));
			mean += GET(delta, 0);
			mean_th += delta_th;

			if (display)
				printf("k:%d %d t:%f\t%f %f %f\n", k, temp_H, t, GET(delta, 0), delta_th, sspread);

			if (sspread > maxSpread)
				maxSpread = sspread;
		}
		printf("Variation entre le moyenne des deltas theorique et des price calcules : %f\n", (fabs(mean-mean_th)/mean_th)*100.);
		printf("Max %f\n", maxSpread);
	}
}

void Test::compute_price(int H, double t){
	double price, price_theo, ic;

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

	mc_->price(past, t, price, ic);

	/*
	if (t==0)
	price_theo = theo_price(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
	else
	price_theo = theo_price(MGET(past, 0, H), strike, r, T-t, GET(sigma, 0));

	printf("%f %f, %f\n", price_/500, ic_/500, price_theo);
	*/
	printf("%f %f\n", price, ic);
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

	mc_->delta(past, t, delta, ic_delta);

	/*
	if (t==0)
	delta_th = theo_delta(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
	else
	delta_th = theo_delta(MGET(past, 0, H), strike, r, T-t, GET(sigma, 0));

	printf("Simul %f IC %f Theo %f\n", delta_/1000., ic_delta_/1000., delta_th);
	*/
	pnl_vect_print(delta);
	printf("\n");
	pnl_vect_print(ic_delta);
	pnl_mat_free(&past);
}

void Test::compute_couv(int H, bool output){
	double N = mc_->get_opt()->get_timeStep();
	double T = mc_->get_opt()->get_T();
	double pl, plTheorique, price, ic;
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
				PnlMat* summary = pnl_mat_create(H+1, 1+3*size);
				mc_->couv(past, pl, plTheorique, H, T, summary);

				mc_->price(price, ic);
				double price_theo = theo_price(100, 100, .05, 1, .2);

				cout << "P&L simule: " << pl/price << endl;
				pnl_mat_print(summary);
				fichier1 << pl/price << endl;
				fichier2 << plTheorique/price_theo << endl;
			}
			fichier1.close();
			fichier2.close();
		}else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
	}else{
		PnlMat* past = pnl_mat_create(size, H+1);
		PnlMat* summary = pnl_mat_create(H+1, 1+3*size);
		mc_->couv(past, pl, plTheorique, H, T, summary);
		mc_->price(price, ic);
		double price_theo = theo_price(100, 100, .05, 1, .2);

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
