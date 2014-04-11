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
	double price, ic, priceTheo;
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
		ofstream file1("Data/price_simul.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du file ouvert
		ofstream file2("Data/priceTheo.txt", ios::out | ios::trunc);
		ofstream file3("Data/time.txt", ios::out | ios::trunc);
		if(file1 && file2)
		{
			for (int k = 0; k < 1001; k++){
				cout << k << endl;

				t = k/1000.;

				temp_H = (int)(t*1000);
				pnl_mat_resize(past_extract, 1, temp_H+1);

				for (int i = 0; i < temp_H+1; i++){
					MLET(past_extract, 0, i) = MGET(past, 0, i); 
				}

				mc_->price(t, price, ic, past_extract);

				if (t==0)
					priceTheo = theo_price(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
				else
					priceTheo = theo_price(MGET(past, 0, temp_H), strike, r, T-t, GET(sigma, 0));

				priceTheo = (int)(priceTheo*1000)/1000.;
				price = (int)(price*1000)/1000.;

				file1 << price << endl;
				file2 << priceTheo << endl;
				file3 << t << endl;
			}
			file1.close();
			file2.close();
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

			mc_->price(t, price, ic, past_extract);

			if (t==0)
				priceTheo = theo_price(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
			else
				priceTheo = theo_price(MGET(past, 0, temp_H), strike, r, T-t, GET(sigma, 0));

			priceTheo = (int)(priceTheo*1000)/1000.;
			price = (int)(price*1000)/1000.;

			sspread = fabs(priceTheo-price);
			mean += price;
			mean_th += priceTheo;

			if (display)
				printf("%d %f \t%f %f %f\n", k, t, price, priceTheo, sspread);

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
		ofstream file1("Data/delta_simul.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du file ouvert
		ofstream file2("Data/delta_theo.txt", ios::out | ios::trunc);
		if(file1 && file2)
		{
			for (int k = 0; k < 1001; k++){
				cout << k << endl;

				t = k/1000.;
				temp_H = (int)(t*1000);
				pnl_mat_resize(past_extract, 1, temp_H+1);

				for (int i = 0; i < temp_H+1; i++){
					MLET(past_extract, 0, i) = MGET(past, 0, i); 
				}

				mc_->delta(t, delta, ic_delta, past_extract);

				if (t==0)
					delta_th = theo_delta(MGET(past, 0, 0), strike, r, T-t, GET(sigma, 0));
				else
					delta_th = theo_delta(MGET(past, 0, temp_H), strike, r, T-t, GET(sigma, 0));

				delta_th = (int)(delta_th*10000)/10000.;
				LET(delta, 0) = (int)(GET(delta, 0)*10000)/10000.;

				file1 << GET(delta, 0) << endl;
				file2 << delta_th << endl;
			}
			file1.close();
			file2.close();
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

			mc_->delta(t, delta, ic_delta, past_extract);

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
	double price, priceTheo, ic;

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
	PnlMat* past_sub = pnl_mat_create(size, 1);
	PnlVect* V = pnl_vect_create(size);

	mod->simul_market(H, t, past, rng);
	pnl_mat_print(past); 

	mc_->price(t, price, ic, past);
	printf("%f\n", price);

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

	PnlMat* past = pnl_mat_create(size, H+1);
	PnlMat* past_sub = pnl_mat_create(size, 1);
	PnlVect* V = pnl_vect_create(size);

	mod->simul_market(H, T, past, rng);
	pnl_mat_print(past);
	mc_->delta(0, delta, ic_delta, past);
	pnl_vect_print(delta);

	pnl_mat_free(&past);
}

void Test::compute_couv(int H, bool output){
	double N = mc_->get_opt()->get_timeStep();
	double T = mc_->get_opt()->get_T();
	double pl, price, ic;
	int size = mc_->get_opt()->get_size();

	if (fmod((double)H, (double)N) > 0.0001){
		printf("Erreur: H non adapte \n");
		system("pause");
		return;
	}


	PnlMat* past = pnl_mat_create(size, H+1);
	PnlMat* summarySimul = pnl_mat_create(H+1, size*2+5);

	if (output) {
		ofstream file1("../Data/s1.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du file ouvert
		ofstream file2("../Data/s2.txt", ios::out | ios::trunc);
		ofstream file3("../Data/s3.txt", ios::out | ios::trunc);
		ofstream file4("../Data/s4.txt", ios::out | ios::trunc);
		ofstream file5("../Data/d1.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du file ouvert
		ofstream file6("../Data/d2.txt", ios::out | ios::trunc);
		ofstream file7("../Data/d3.txt", ios::out | ios::trunc);
		ofstream file8("../Data/d4.txt", ios::out | ios::trunc);
		ofstream file9("../Data/price.txt", ios::out | ios::trunc);
		ofstream file10("../Data/risk.txt", ios::out | ios::trunc);
		ofstream file11("../Data/risk_free.txt", ios::out | ios::trunc);
		ofstream file12("../Data/total.txt", ios::out | ios::trunc);

		if(file1 && file2 && file3 && file4)
		{
			mc_->couv(H, T, pl, past, summarySimul);
			mc_->price(price, ic);
			
			cout << "P&L simule: " << pl/price << endl;
			
			for (int i = 0; i < H+1; i++){
				file1 << MGET(summarySimul, i, 1) << endl;
				file2 << MGET(summarySimul, i, 2) << endl;
				file3 << MGET(summarySimul, i, 3) << endl;
				file4 << MGET(summarySimul, i, 4) << endl;
				file5 << MGET(summarySimul, i, 5) << endl;
				file6 << MGET(summarySimul, i, 6) << endl;
				file7 << MGET(summarySimul, i, 7) << endl;
				file8 << MGET(summarySimul, i, 8) << endl;
				file9 << MGET(summarySimul, i, 9) << endl;
				file10 << MGET(summarySimul, i, 10) << endl;
				file11 << MGET(summarySimul, i, 11) << endl;
				file12 << MGET(summarySimul, i, 12) << endl;
			}

			file1.close();
			file2.close();
			file3.close();
			file4.close();
		}else
			cerr << "Impossible d'ouvrir le file !" << endl;
	}else{
		mc_->couv(H, T, pl, past, summarySimul);
		pnl_mat_print(summarySimul);

		cout << "P&L simule: " << pl/MGET(summarySimul, H, 9) << endl;
	}
}

void Test::compute_hedge(
	int H)
{
	double N = mc_->get_opt()->get_timeStep();
	double T = mc_->get_opt()->get_T();
	double pl, price, ic;
	int size = mc_->get_opt()->get_size();

	if (fmod((double)H, (double)N) > 0.0001){
		printf("Erreur: H non adapte \n");
		system("pause");
		return;
	}

	PnlMat* past = pnl_mat_create(size, H+1);
	PnlMat* past_sub = pnl_mat_create(size, 1);
	PnlVect* extract = pnl_vect_create(size);
	PnlVect* delta_ant = pnl_vect_create_from_double(size, 0.);
	PnlRng* rng = mc_->get_rng();
	double risk_free_portion = 0.0;
	double risk_portion = 0.0;

	mc_->get_mod()->simul_market(H, T, past, rng);
	pnl_mat_print(past);

	for (int i = 0; i < H+1; i++){
		printf("\n%d\n", i);

		pnl_mat_resize(past_sub, size, i+1);
		for (int j = 0; j<i+1; j++){
			pnl_mat_get_col(extract, past, j);
			pnl_mat_set_col(past_sub, extract, j);
		}
		mc_->compute_portfolio(H, T, (double)(i*T)/(double)H, risk_free_portion, risk_portion, delta_ant, past_sub);

		printf("%f %f %f\n", risk_free_portion, risk_portion, risk_free_portion+risk_portion);
	}
	double prix;
	mc_->price(6., prix, ic, past);
	printf("%f %f\n", prix, (risk_free_portion+risk_portion-prix)/prix);
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