#include "montecarlo.h"
#include <math.h>
#include <pnl/pnl_vector.h>
#include <pnl/pnl_matrix.h>
#include <pnl/pnl_cdf.h>
#include <pnl/pnl_mathtools.h>
#include <cstdio>

MonteCarlo::MonteCarlo(PnlRng * rng){
	(*this).rng = rng;
	h_ = 0.0;
	samples_ = 0;
}

MonteCarlo::MonteCarlo(Bs *mod, Option *opt, PnlRng *rng, double h, int samples){
	(*this).mod_ = mod;
	(*this).opt_ = opt;
	(*this).rng = rng;
	(*this).h_ = h;
	(*this).samples_ = samples;
}

/**
* Accesseurs
*
*/
MonteCarlo::~MonteCarlo(){
}

Bs* MonteCarlo::get_mod() const{
	return mod_;
}

Option* MonteCarlo::get_opt() const{
	return opt_;
}

PnlRng* MonteCarlo::get_rng() const{
	return rng;
}

double MonteCarlo::get_h() const{
	return h_;
}

int MonteCarlo::get_samples() const{
	return samples_;
}

/**
* Mutateurs
*
*/
void MonteCarlo::set_mod(Bs* mod){
	mod_ = mod;
}

void MonteCarlo::set_opt(Option* opt){
	opt_ = opt;
}

void MonteCarlo::set_rng(PnlRng* rng){
	(*this).rng = rng;
}

void MonteCarlo::set_h(double h){
	h_ = h;
}

void MonteCarlo::set_samples(int samples){
	samples_ = samples;
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
  //Initialisation de path comme une matrice de dimension d x (N+1)
  PnlMat *path = pnl_mat_create(size, TimeSteps+1);
  //G: matrice de dimension N*d pour générer une suite iid selon la loi normale centrée réduite
  PnlMat *G = pnl_mat_create(TimeSteps, size);
  //grid: vecteur de taille N pour générer la grille de temps (t_0=0, ..., t_N)
  PnlVect *grid = pnl_vect_create(TimeSteps+1);
  //tirages: vecteur de taille samples_ contenant les valeurs des M payoff
  PnlVect *tirages = pnl_vect_create(samples_);
  //temps: incrémentation pour chaque date de constation
  double temps = T/TimeSteps;

  //Calcule de chaque date de constatation;
  for (int t=0; t<TimeSteps+1; t++){
	LET(grid, t) = temps*t;
  }

  //Ajout du prix spot dans la première colonne de path
  pnl_mat_set_col(path, mod_->get_spot(), 0);

  for (int j=0; j<samples_; j++){
	//Génération de la trajectoire du modèle de Black Scholes
	mod_->asset(path, T, TimeSteps, rng, G, grid);
	//Ajout du payoff dans tirages
	LET(tirages, j) = opt_->payoff(path);
  }

  //Calcul du prix à l'aide de la formule de MC
  prix = exp(-r*T)*(1/(double)samples_)*pnl_vect_sum(tirages);
  //Calcul de la variance de l'estimateur pour avoir l'intervalle de confiance
  ic = (3.92/sqrt((double)samples_) )* sqrt(exp(-2*r*T)*((1/(double)samples_)*SQR(pnl_vect_norm_two(tirages))-SQR((1/(double)samples_)*pnl_vect_sum(tirages))));

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

	//G: matrice de dimension N*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(timeStep, size);
	//grid: vecteur de taille N pour générer la grille de temps (t_0=0, ..., t_N)
	PnlVect *grid = pnl_vect_create(timeStep+1);
	//tirages: vecteur de taille samples_ contenant les valeurs des M payoff
	PnlVect *tirages_1 = pnl_vect_create_from_zero(samples_);
	PnlVect *tirages_2 = pnl_vect_create_from_zero(samples_);
	PnlVect *tirages_6 = pnl_vect_create_from_zero(samples_);
	int compteur_1 = 0;
	int compteur_2 = 0;
	int compteur_6 = 0;

	//temps: incrémentation pour chaque date de constation
	double temps = T/timeStep;

	//Calcule de chaque date de constatation;
	for (int t=0; t<timeStep+1; t++){
		LET(grid, t) = temps*t;
	}

	//Ajout du prix spot dans la première colonne de path
	pnl_mat_set_col(path, mod_->get_spot(), 0);
	for (int j=0; j<samples_; j++){
		//Génération de la trajectoire du modèle de Black Scholes
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
	//Calcul du prix à l'aide de la formule de MC
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
	//Initialisation de path comme une matrice de dimension d x (N+1)
	PnlMat *path = pnl_mat_create(size, timeStep+1);
	//temps: incrémentation pour chaque date de constatation
	double dt = T/timeStep;
	//extractPast: vecteur de taille size servant à extraire de la matrice past les colonnes pour les insérer dans path
	PnlVect *extractPast = pnl_vect_create(size);

	int H = past->n - 1;
	int taille;	

	if (fabs(t) < 0.000001){
		taille = 0;
		pnl_mat_get_col(extractPast, past, 0);
		pnl_mat_set_col(path, extractPast, 0);
	} else {
		double dtPast = t/H;
		int indice = floor(dt*100+0.5)/floor(dtPast*100+0.5);
		taille = floor((double)H/(double)indice);
		int i = 0;
		while (i < taille+1){
			pnl_mat_get_col(extractPast, past, i*indice);
			pnl_mat_set_col(path, extractPast, i);
			i++;
		}
	}

	//Grid: vecteur de taille N-taille+1 pour générer la grille de temps (t, t_{i+1}, ..., t_{N})
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);
	if (fmod(t,dt) != 0){
		pnl_mat_get_col(extractPast, past, H);
		LET(grid, 0) = t;
	} else {
		LET(grid, 0) = dt * taille;
	}
	


	//Cas où on price à maturité
	//Toutes les informations sont déjà déterminés à l'aide de past
	//donc on a besoin d'aucune simulation
	//et l'intervalle de confiance est de 0 car on est dans un calcul du prix déterministe
	if (t == T){
		prix = opt_->payoff(path);
		//Calcul de la variance
		ic = 0;
		pnl_mat_free(&path);
		pnl_vect_free(&extractPast);
		return;
	}

	//tirages: vecteur de taille samples_ contenant la valeur des payoff de l'option
	PnlVect *tirages = pnl_vect_create(samples_);

	//G: matrice de dimension (N-taille)*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);
	
	//Calcul de chaque date de constatation;
	for (int i=1; i<timeStep-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}

	for (int j=0; j<samples_; j++){
		//Génération de l'évolution du sous-jacent par le modèle de Bs
		mod_->asset(path, t, timeStep , T, rng, extractPast, taille, G, grid);
		//Ajout dans tirages
		LET(tirages, j) = opt_->payoff(path);
	}

	//Calcul du prix
	prix = exp(-r*(T-t))*(1/(double)samples_)*pnl_vect_sum(tirages);
	//Calcul de la variance
	ic = (3.92/sqrt((double)samples_)) * sqrt(exp(-2*r*(T-t))*((1/(double)samples_)*SQR(pnl_vect_norm_two(tirages))-SQR((1/(double)samples_)*pnl_vect_sum(tirages))));

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
	//temps: incrémentation pour chaque date de constatation
	double dt = T/timeStep;
	//extractPast: vecteur de taille size servant à extraire de la matrice past les colonnes pour les insérer dans path
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
		int indice = floor(dt*100+0.5)/floor(dtPast*100+0.5);
		taille = floor((double)H/(double)indice);
		int i = 0;
		while (i < taille+1){
			pnl_mat_get_col(extractPast, past, i*indice);
			pnl_mat_set_col(path, extractPast, i);
			i++;
		}
	}

	//Grid: vecteur de taille N-taille+1 pour générer la grille de temps (t, t_{i+1}, ..., t_{N})
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);
	if (fmod(t,dt) != 0){
		pnl_mat_get_col(extractPast, past, H);
		LET(grid, 0) = t;
	} else {
		LET(grid, 0) = dt * taille;
	}

	//G: matrice de dimension (N-taille)*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);
	
	//Calcul de chaque date de constatation;
	for (int i=1; i<timeStep-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}

	for (int d=0; d<size; d++){
		for (int j=0; j<samples_; j++){
			
			mod_->asset(path, t, timeStep, T, rng, extractPast, taille, G, grid);
			// On récupère la trajectoire shiftée
			mod_->shift_asset(_shift_path_plus, path, d, h_, t,timeStep);
			mod_->shift_asset (_shift_path_moins, path, d, -h_, t,timeStep);

			//On calcul la valeur du payoff et on retiens la dtérence
			temps1 = opt_->payoff(_shift_path_plus);
			temps2 = opt_->payoff(_shift_path_moins);
			LET(tirages, j) = temps1-temps2;
			// recuperation des (phi(plus)-pi(moins))²
			LET(tirages2, j) = (temps1-temps2)*(temps1-temps2);
		}
		// somme des phi
		sum = pnl_vect_sum(tirages);
		// somme des phi²
		sum2 = pnl_vect_sum(tirages2);

		// calcul de delta
		facteur =  1/(2*(double)h_*(double)samples_*(double)MGET(past, d, past->n-1));
		result =  exp(-r*(T-t))* facteur * sum;
		LET(delta, d) = result;

		// calcul de l'intervalle de confiance
		sum = (sum*facteur)*(sum*facteur);
		resultic = exp(-r*(T-t))/2 * (facteur*sum2 - sum);
		resultic = 3.92*sqrt(resultic * 1/ (double)samples_);
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

double delta_theoriqu(double sigma, double T, double S, double K, double r){
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
double prix_theoriqu(double S, double K, double r, double T, double sigma){
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
void MonteCarlo::couv(PnlMat *past, double &pl, double &plTheorique, int H, double T)
{
	//Simulation du modèle sous la probabilité historique
	mod_->simul_market(past, H, T, rng);
	double r = mod_->get_r();
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double timeH = T/H;

	double delta_t, delta_t2;
	double prix_t;
	double result_t;

	//prix: prix du sous-jacent à l'instant 0
	double prix;
	double ic;
	price(prix, ic);
	prix_t = prix_theoriqu(100, 100, .05, 1., .2);

	//delta1: vecteur contenant le delta à un instant donné
	PnlVect* delta1 = pnl_vect_create(size);
	PnlVect* ic_vect = pnl_vect_create(size);
	PnlMat* past_sub = pnl_mat_create(size, 1);

	//S: vecteur contenant le prix dusous-jacent à un instant donné
	PnlVect* S = pnl_vect_create(size);
	//result: vecteur contenant le résultat de la soustraction entre delta1 et delta2
	PnlVect* result;
	PnlVect* pF = pnl_vect_create(H+1);
	PnlVect* pFT = pnl_vect_create(H+1);

	//Calcul à l'instant 0 de la composition du portefeuille
	pnl_mat_get_col(S, past, 0);
	pnl_mat_set_col(past_sub, S, 0);

	delta(past_sub, 0, delta1, ic_vect);
	delta_t = delta_theoriqu(.2, 1., 100, 100, .05);
	LET(pF, 0) = prix - pnl_vect_scalar_prod(delta1, S);
	LET(pFT, 0) = prix_t - delta_t*100;
	//delta2: vecteur contenant le delta à une date de constation précédente de delta1
	for (int i=1; i<H+1; i++)
	{
		//On met dans delta2 la valeur du delta à l'instant i-1
		PnlVect* delta2 = pnl_vect_copy(delta1);
		delta_t2 = delta_t;

		//Calcul du delta & du prix à l'instant tau_i
		pnl_mat_resize(past_sub, size, i+1);
		for (int j=0; j<i+1; j++){
			pnl_mat_get_col(S, past, j);
			pnl_mat_set_col(past_sub, S, j);
		}
		delta(past_sub, timeH*i, delta1, ic_vect);
		price(past_sub, timeH*i, prix, ic);
		prix_t = prix_theoriqu(GET(S, 0), 100, .05, 1.- timeH*i, .2);
		delta_t = delta_theoriqu(.2, 1. - timeH*i, GET(S, 0), 100, .05);

		result = pnl_vect_copy(delta1);
		pnl_vect_minus_vect(result, delta2);
		result_t = delta_t - delta_t2;

		LET(pF, i) = GET(pF,i-1) * exp(r*T/H) - pnl_vect_scalar_prod(result , S);
		LET(pFT, i) = GET(pFT, i-1) * exp(r*T/H) - result_t * GET(S, 0);
		
		pnl_vect_free(&delta2);
	}

	//Calcul de l'erreur de couverture
	pl = GET(pF, H) + pnl_vect_scalar_prod(delta1, S) - prix;
	plTheorique = GET(pFT, H) + delta_t*GET(S, 0) - prix_t;

	pnl_vect_free(&pF);
	pnl_vect_free(&S);
	pnl_vect_free(&delta1);
	pnl_vect_free(&ic_vect);
}