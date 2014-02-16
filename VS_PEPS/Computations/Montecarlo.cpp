#include "montecarlo.h"
#include <math.h>
#include <pnl/pnl_vector.h>
#include <pnl/pnl_matrix.h>
#include <pnl/pnl_cdf.h>
#include <pnl/pnl_mathtools.h>
#include <cstdio>
#include "Test.h"

MonteCarlo::MonteCarlo(PnlRng* rng) : MonteCarlos(rng) {
}

MonteCarlo::MonteCarlo(ModelAsset *mod, Option *opt, PnlRng *rng, double h, int samples) : MonteCarlos(mod, opt, rng, h, samples) {
}

MonteCarlo::~MonteCarlo(){
}

/**
* Price
*
*/
void MonteCarlo::price(double &prix, double &ic){
  int size = opt_->get_size();
  int TimeSteps = opt_->get_timeStep();
  double r = mod_->get_r();
  double T = opt_->get_T();
  //path: matrice repr�sentant l'�volution du sous-jacent sur l'ensemble des pas de temps
  PnlMat *path = pnl_mat_create(size, TimeSteps+1);
  //G: matrice de dimension N*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
  PnlMat *G = pnl_mat_create(TimeSteps, size);
  //grid: vecteur de taille N+1 pour g�n�rer la grille de temps (t_0=0, ..., t_N)
  PnlVect *grid = pnl_vect_create(TimeSteps+1);
  //tirages: vecteur de taille samples_ contenant les valeurs des M payoff
  PnlVect *tirages = pnl_vect_create(samples_);
  //temps: incr�mentation pour chaque date de constation
  double temps = T/TimeSteps;

  //Calcule de chaque date de constatation;
  for (int t=0; t<TimeSteps+1; t++){
	LET(grid, t) = temps*t;
  }

  //Ajout du prix spot dans la premi�re colonne de path
  pnl_mat_set_col(path, mod_->get_spot(), 0);

  for (int j=0; j<samples_; j++){
	//G�n�ration de la trajectoire du mod�le de Black Scholes
	mod_->asset(path, T, TimeSteps, rng, G, grid);
	//Ajout du payoff dans tirages
	LET(tirages, j) = opt_->payoff(path);
  }

  //Calcul du prix � l'aide de la formule de MC
  prix = exp(-r*T)*(1./(double)samples_)*pnl_vect_sum(tirages);
  //Calcul de la variance de l'estimateur pour avoir l'intervalle de confiance
  ic = (3.92/sqrt((double)samples_) )* sqrt(exp(-2.*r*T)*((1./(double)samples_)*SQR(pnl_vect_norm_two(tirages))-SQR((1./(double)samples_)*pnl_vect_sum(tirages))));
  
  pnl_vect_free(&grid);
  pnl_vect_free(&tirages);
  pnl_mat_free(&path);
  pnl_mat_free(&G);
}

/*
void MonteCarlo::price(double &prix, double &ic){
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double r = mod_->get_r();
	double T = opt_->get_T();
	//Initialisation de path comme une matrice de dimension d x (N+1)
	PnlMat *path = pnl_mat_create(size, timeStep+1);

	//G: matrice de dimension N*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
	PnlMat *G = pnl_mat_create(timeStep, size);
	//grid: vecteur de taille N pour g�n�rer la grille de temps (t_0=0, ..., t_N)
	PnlVect *grid = pnl_vect_create(timeStep+1);
	//tirages: vecteur de taille samples_ contenant les valeurs des M payoff
	PnlVect *tirages_1 = pnl_vect_create_from_zero(samples_);
	PnlVect *tirages_2 = pnl_vect_create_from_zero(samples_);
	PnlVect *tirages_6 = pnl_vect_create_from_zero(samples_);
	int compteur_1 = 0;
	int compteur_2 = 0;
	int compteur_6 = 0;

	//temps: incr�mentation pour chaque date de constation
	double temps = T/timeStep;

	//Calcule de chaque date de constatation;
	for (int t=0; t<timeStep+1; t++){
		LET(grid, t) = temps*t;
	}

	//Ajout du prix spot dans la premi�re colonne de path
	pnl_mat_set_col(path, mod_->get_spot(), 0);
	for (int j=0; j<samples_; j++){
		//G�n�ration de la trajectoire du mod�le de Black Scholes
		mod_->asset(path, T, timeStep, rng, G, grid);
		//Ajout du payoff dans tirages
		
		if (MGET(path, 0, 2) == -1){
			opt_->set_T(1);
			LET(tirages_1, j) = opt_->payoff(path);
			compteur_1++;
		}
		else{
			if (MGET(path, 0, 3) == -1){
				opt_->set_T(2);
				LET(tirages_2, j) = opt_->payoff(path);
				compteur_2++;
			}
			else{
				LET(tirages_6, j) = opt_->payoff(path);
				compteur_6++;
			}

		}
		opt_->set_T(6);
	}
	//Calcul du prix � l'aide de la formule de MC
	prix = (1/(double)samples_)*(pnl_vect_sum(tirages_1)+pnl_vect_sum(tirages_2)+pnl_vect_sum(tirages_6));
	//Calcul de la variance de l'estimateur pour avoir l'intervalle de confiance
	ic = (3.92/sqrt((double)samples_) )* sqrt(exp(-2*r*T)*((1/(double)samples_)*(SQR(pnl_vect_norm_two(tirages_1))-SQR((1/(double)samples_)*pnl_vect_sum(tirages_1))+SQR(pnl_vect_norm_two(tirages_2))-SQR((1/(double)samples_)*pnl_vect_sum(tirages_2))+SQR(pnl_vect_norm_two(tirages_6))-SQR((1/(double)samples_)*pnl_vect_sum(tirages_6)))));

	pnl_vect_free(&grid);
	pnl_vect_free(&tirages_1);
	pnl_vect_free(&tirages_2);
	pnl_vect_free(&tirages_6);
	pnl_mat_free(&path);
	pnl_mat_free(&G);
}
*/

void MonteCarlo::price(const PnlMat *past, double t, double &prix, double &ic){
	double T = opt_->get_T();
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double r = mod_->get_r();
	//path: matrice repr�sentant l'�volution du sous-jacent sur l'ensemble des pas de temps
	PnlMat *path = pnl_mat_create(size, timeStep+1);
	//dt: pas d'incr�mentation
	double dt = T/timeStep;
	//extractPast: vecteur de taille size servant � extraire de la matrice past les colonnes pour les ins�rer dans path
	PnlVect *extractPast = pnl_vect_create(size);
	//H: nombre de pas d'incr�mentation de past
	int H = past->n - 1;

	//Si t = 0, on met uniquement la premiere colonne de past dans path
	//sinon on ajoute les colonnes de past qui poss�de un pas de temps dans path
	int taille;	
	if (fabs(t) < 0.000001){
		taille = 0;
		pnl_mat_get_col(extractPast, past, 0);
		pnl_mat_set_col(path, extractPast, 0);
	} else {
		double dtPast = t/H;
		int indice = floor(dt*100000000+0.5)/floor(dtPast*100000000+0.5);
		taille = floor((double)H/(double)indice);
		int i = 0;
		while (i < taille+1){
			pnl_mat_get_col(extractPast, past, i*indice);
			pnl_mat_set_col(path, extractPast, i);
			i++;
		}
	}
	if (fmod(t,dt) != 0){
		pnl_mat_get_col(extractPast, past, H);
	}
	//extractPast contient la valeur du sous-jacent en t
	
	//Cas o� on price � maturit�
	//Toutes les informations sont d�j� d�termin�s � l'aide de past
	//donc on a besoin d'aucune simulation
	//et l'intervalle de confiance est de 0 car on est dans un calcul du prix d�terministe
	if (t == T){
		prix = opt_->payoff(path);
		ic = 0;
		pnl_mat_free(&path);
		pnl_vect_free(&extractPast);
		return;
	}
	
	//tirages: vecteur de taille samples_ contenant la valeur des payoff de l'option
	PnlVect *tirages = pnl_vect_create(samples_);
	//G: matrice de dimension (N-taille)*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);
	//grid: vecteur de taille N-taille+1 pour g�n�rer la grille de temps de t � t_N
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);
	LET(grid, 0) = t;
	for (int i=1; i<timeStep-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}
	
	for (int j=0; j<samples_; j++){
		//G�n�ration de l'�volution du sous-jacent par le mod�le de Bs
		mod_->asset(path, t, timeStep , T, rng, extractPast, taille, G, grid);
		//Ajout dans tirages
		LET(tirages, j) = opt_->payoff(path);
	}

	//Calcul du prix
	prix = exp(-r*(T-t))*(1./(double)samples_)*pnl_vect_sum(tirages);
	//Calcul de la variance
	ic = (3.92/sqrt((double)samples_)) * sqrt(exp(-2.*r*(T-t))*((1./(double)samples_)*SQR(pnl_vect_norm_two(tirages))-SQR((1./(double)samples_)*pnl_vect_sum(tirages))));

	pnl_mat_free(&path);
	pnl_mat_free(&G);
	pnl_vect_free(&tirages);
	pnl_vect_free(&extractPast);
	pnl_vect_free(&grid);
}

void MonteCarlo::delta (const PnlMat *past, double t, PnlVect *delta, PnlVect *ic){
	double temps1 = 0;
	double temps2 = 0;
	double sum, sum2;
	double facteur;
	double result, resultic;

	double T = opt_->get_T();
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double r = mod_->get_r();
 
	//Initialisation de path comme une matrice de dimension d x (N+1)
	PnlMat *path = pnl_mat_create(size, timeStep+1);
	//temps: incr�mentation pour chaque date de constatation
	double dt = T/timeStep;
	//extractPast: vecteur de taille size servant � extraire de la matrice past les colonnes pour les ins�rer dans path
	PnlVect *extractPast = pnl_vect_create(size);
	PnlMat *_shift_path_plus = pnl_mat_create(size, timeStep+1);
	PnlMat *_shift_path_moins = pnl_mat_create(size, timeStep+1);
	PnlVect *tirages = pnl_vect_create(samples_);
	PnlVect *tirages2 =  pnl_vect_create(samples_);

	int H = past->n - 1;
	int taille;	

	if (fabs(t) < 0.000001){
		taille = 0;
		pnl_mat_get_col(extractPast, past, 0);
		pnl_mat_set_col(path, extractPast, 0);
	} else {
		double dtPast = t/H;
		int indice = floor(dt*100000000+0.5)/floor(dtPast*100000000+0.5);
		taille = floor((double)H/(double)indice);
		int i = 0;
		while (i < taille+1){
			pnl_mat_get_col(extractPast, past, i*indice);
			pnl_mat_set_col(path, extractPast, i);
			i++;
		}
	}
	if (fmod(t,dt) != 0){
		pnl_mat_get_col(extractPast, past, H);
	}
	//G: matrice de dimension (N-taille)*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);
	//Grid: vecteur de taille N-taille+1 pour g�n�rer la grille de temps (t, t_{i+1}, ..., t_{N})
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);
	LET(grid, 0) = t;
	for (int i=1; i<timeStep-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}

	for (int d=0; d<size; d++){
		for (int j=0; j<samples_; j++){
			
			mod_->asset(path, t, timeStep, T, rng, extractPast, taille, G, grid);
			// On r�cup�re la trajectoire shift�e
			mod_->shift_asset(_shift_path_plus, path, d, h_, t, timeStep);
			mod_->shift_asset (_shift_path_moins, path, d, -h_, t, timeStep);

			//On calcul la valeur du payoff et on retiens la dt�rence
			temps1 = opt_->payoff(_shift_path_plus);
			temps2 = opt_->payoff(_shift_path_moins);
			LET(tirages, j) = temps1-temps2;
			// recuperation des (phi(plus)-pi(moins))�
			LET(tirages2, j) = (temps1-temps2)*(temps1-temps2);
		}
		// somme des phi
		sum = pnl_vect_sum(tirages);
		// somme des phi�
		sum2 = pnl_vect_sum(tirages2);

		// calcul de delta
		facteur =  1./(2.*h_*(double)samples_*MGET(past, d, past->n-1));
		result =  exp(-r*(T-t))* facteur * sum;
		LET(delta, d) = result;

		// calcul de l'intervalle de confiance
		sum = (sum*facteur)*(sum*facteur);
		resultic = exp(-r*(T-t))/2 * (facteur*sum2 - sum);
		resultic = 3.92*sqrt(resultic * 1./(double)samples_);
		LET(ic, d) = resultic;
	}

	pnl_mat_free(&G);
	pnl_mat_free(&path);
	pnl_mat_free(&_shift_path_plus);
	pnl_mat_free(&_shift_path_moins);
	pnl_vect_free(&tirages);
	pnl_vect_free(&tirages2);
	pnl_vect_free(&extractPast);
	pnl_vect_free(&grid);
}

void MonteCarlo::couv(PnlMat *past, double &pl, double &plTheorique, int H, double T, PnlMat *summary)
{
	//Simulation du mod�le sous la probabilit� historique
	mod_->simul_market(past, H, T, rng);
	double r = mod_->get_r();
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double timeH = T/H;

	double delta_th, delta_th2;
	double prix_th;
	double result_t;

	//delta1: vecteur contenant le delta � un instant donn�
	PnlVect* delta1 = pnl_vect_create(size);
	PnlVect* ic_vect = pnl_vect_create(size);
	PnlMat* past_sub = pnl_mat_create(size, 1);
	PnlVect* past_extract = pnl_vect_create(H+1);
	//S: vecteur contenant le prix dusous-jacent � un instant donn�
	PnlVect* S = pnl_vect_create(size);
	//result: vecteur contenant le r�sultat de la soustraction entre delta1 et delta2
	PnlVect* result;
	PnlVect* pF = pnl_vect_create(H+1);
	PnlVect* pFT = pnl_vect_create(H+1);

	//prix: prix du sous-jacent � l'instant 0
	double prix;
	double ic;
	price(prix, ic);
	prix_th = Test::theo_price(100, 100, .05, 1., .2);

	//Ajout du cours de l'action dans summary (colonne 2)
	pnl_mat_get_row(past_extract, past, 0);
	pnl_mat_set_col(summary, past_extract, 1);

	//Calcul � l'instant 0 de la composition du portefeuille
	pnl_mat_get_col(S, past, 0);
	pnl_mat_set_col(past_sub, S, 0);

	delta(past_sub, 0, delta1, ic_vect);
	delta_th = Test::theo_delta(100, 100, .05, 1., .2);
	LET(pF, 0) = prix - pnl_vect_scalar_prod(delta1, S);
	LET(pFT, 0) = prix_th - delta_th*100;
	//Ajout dans summary de la date, du delta & du nombre d'actions � acheter, du delta th�orique & du nombre d'actions th�orique � acheter
	MLET(summary, 0, 0) = 0.;
	MLET(summary, 0, 2) = GET(delta1, 0);
	MLET(summary, 0, 3) = GET(delta1, 0);
	MLET(summary, 0, 4) = delta_th;
	MLET(summary, 0, 5) = delta_th;
	


	/*printf("t=%f\n%f %f\n", 0., prix_th, prix);
	printf("%f ", delta_th); pnl_vect_print(delta1); 
	printf("\n");*/

	//delta2: vecteur contenant le delta � une date de constation pr�c�dente de delta1
	for (int i=1; i<H+1; i++)
	{
		//On met dans delta2 la valeur du delta � l'instant i-1
		PnlVect* delta2 = pnl_vect_copy(delta1);
		delta_th2 = delta_th;

		//Calcul du delta & du prix � l'instant tau_i
		pnl_mat_resize(past_sub, size, i+1);
		for (int j=0; j<i+1; j++){
			pnl_mat_get_col(S, past, j);
			pnl_mat_set_col(past_sub, S, j);
		}
		delta(past_sub, timeH*i, delta1, ic_vect);
		price(past_sub, timeH*i, prix, ic);
		prix_th = Test::theo_price(GET(S, 0), 100, .05, 1.- timeH*(double)i, .2);
		delta_th = Test::theo_delta(GET(S, 0), 100, .05, 1.- timeH*(double)i, .2);
	
		//Ajout des informations dans summary
		MLET(summary, i, 0) = timeH*(double)i;
		MLET(summary, i, 2) = GET(delta1, 0);
		MLET(summary, i, 3) = GET(delta1, 0) - GET(delta2, 0);
		MLET(summary, i, 4) = delta_th;
		MLET(summary, i, 5) = delta_th - delta_th2;

		/*printf("t=%f\n%f %f\n", timeH*i, prix_th, prix);
		printf("%f ", delta_th); pnl_vect_print(delta1); 
		printf("\n");*/

		result = pnl_vect_copy(delta1);
		pnl_vect_minus_vect(result, delta2);
		result_t = delta_th - delta_th2;

		LET(pF, i) = GET(pF,i-1) * exp(r*T/H) - pnl_vect_scalar_prod(result , S);
		LET(pFT, i) = GET(pFT, i-1) * exp(r*T/H) - result_t * GET(S, 0);
		
		pnl_vect_free(&delta2);
	}
	//Calcul de l'erreur de couverture
	pl = GET(pF, H) + pnl_vect_scalar_prod(delta1, S) - prix;
	plTheorique = GET(pFT, H) + delta_th*GET(S, 0) - prix_th;

	PnlMat* final = pnl_mat_create(H+1, 2);
	pnl_mat_set_col(final, pFT, 0);
	pnl_mat_set_col(final, pF, 1);
	
	//pnl_mat_print(final);

	pnl_vect_free(&pF);
	pnl_vect_free(&S);
	pnl_vect_free(&delta1);
	pnl_vect_free(&ic_vect);
	pnl_vect_free(&past_extract);
}