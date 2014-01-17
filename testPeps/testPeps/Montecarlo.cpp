#include "montecarlo.h"
#include <math.h>
#include <pnl/pnl_vector.h>
#include <pnl/pnl_matrix.h>
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
  //G: matrice de dimension N*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
  PnlMat *G = pnl_mat_create(TimeSteps, size);
  //grid: vecteur de taille N pour g�n�rer la grille de temps (t_0=0, ..., t_N)
  PnlVect *grid = pnl_vect_create(TimeSteps+1);
  //tirages: vecteur de taille samples_ contenant les valeurs des M payoff
  PnlVect *tirages = pnl_vect_create(samples_);
  //temps: incr�mentation pour chaque date de constation
  double temps = T/TimeSteps;

  //Calcule de chaque date de constatation;
  for (int t=0; t<TimeSteps+1; t++){
	pnl_vect_set(grid, t, temps*t);
  }

  //Ajout du prix spot dans la premi�re colonne de path
  pnl_mat_set_col(path, mod_->get_spot(), 0);
  for (int j=0; j<samples_; j++){
	//G�n�ration de la trajectoire du mod�le de Black Scholes
	mod_->asset(path, T, TimeSteps, rng, G, grid);
	//Ajout du payoff dans tirages
	pnl_vect_set(tirages, j, opt_->payoff(path));
  }
  //Calcul du prix � l'aide de la formule de MC
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
		pnl_vect_set(grid, t, temps*t);
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
	//Cas o� on price � maturit�
	//Toutes les informations sont d�j� d�termin�s � l'aide de past
	//donc on a besoin d'aucune simulation
	//et l'intervalle de confiance est de 0 car on est dans un calcul du prix d�terministe
	if (t == T){
		prix = opt_->payoff(past);
		//Calcul de la variance
		ic = 0;
		return;
	}

	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double r = mod_->get_r();
	//Initialisation de path comme une matrice de dimension d x (N+1)
	PnlMat *path = pnl_mat_create(size, timeStep+1);
	//tirages: vecteur de taille samples_ contenant la valeur des payoff de l'option
	PnlVect *tirages = pnl_vect_create(samples_);
	//temps: incr�mentation pour chaque date de constatation
	double temps = T/timeStep;
	//extract: vecteur de taille size servant � extraire de la matrice past les colonnes pour les ins�rer dans path
	PnlVect *extract = pnl_vect_create(size);
	
	int H = past->n - 1;
	double pastTimeStep = t/H;
	int indice = temps/pastTimeStep;
	int taille = H/indice;
	for (int i = 0; i < taille+1; i++){
		pnl_mat_get_col(extract, past, i*indice);
		pnl_mat_set_col(path, extract, i);
	}

	//G: matrice de dimension (N-taille)*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);
	//Grid: vecteur de taille N-taille+1 pour g�n�rer la grille de temps (t, t_{i+1}, ..., t_{N})
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);

	//Calcul de chaque date de constatation;
	for (int i=0; i<timeStep-taille+1; i++){
		pnl_vect_set(grid, i, temps*(i+taille));
	}


	for (int j=0; j<samples_; j++){
		//Si on travaille � maturit�
		//alors on clone la matrice past dans path
		//sinon on g�n�re l'�volution du sous-jacent par le mod�le de Bs
		if (t==T)
			pnl_mat_clone(path,past);
		else  
			mod_->asset(path, t, timeStep , T, rng, past, taille, G, grid);
		//Ajout dans tirages
		pnl_vect_set(tirages, j, opt_->payoff(path));
	}
	//Calcul du prix
	prix = exp(-r*(T-t))*(1/(double)samples_)*pnl_vect_sum(tirages);
	//Calcul de la variance
	ic = (3.92/sqrt((double)samples_)) * sqrt(exp(-2*r*(T-t))*((1/(double)samples_)*SQR(pnl_vect_norm_two(tirages))-SQR((1/(double)samples_)*pnl_vect_sum(tirages))));

	pnl_mat_free(&path);
	pnl_mat_free(&G);
	pnl_vect_free(&tirages);
	pnl_vect_free(&extract);
	pnl_vect_free(&grid);
}


void MonteCarlo::delta (const PnlMat *past, double t, PnlVect *delta, PnlVect *ic){
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double r = mod_->get_r();
	double T = opt_->get_T();
	double temps1 = 0;
	double temps2 = 0;
	double sum, sum2;
	double facteur;
	double result, resultic;
	//Temps: incr�mentation pour chaque date de constatation
	double temps = T/timeStep;
	//Extract: vecteur de taille size servant � extraire de la matrice past les colonnes pour les ins�rer dans path
	PnlVect *extract = pnl_vect_create(size);
	//On initialise path, _shift_path_plus et _shift_path_moins comme des matrices de dimension d x (N+1)
	PnlMat *path = pnl_mat_create(size, timeStep+1);  
	PnlMat *_shift_path_plus = pnl_mat_create(size, timeStep+1);
	PnlMat *_shift_path_moins = pnl_mat_create(size, timeStep+1);
	PnlVect *tirages = pnl_vect_create(samples_);
	PnlVect *tirages2 =  pnl_vect_create(samples_);

	//Taille: entier servant � d�terminer le nombre de d'�volution du sous jacent (timeStep-taille termes � simuler pour chaque actif)
	//Si t est un pas d'incr�mentation du temps alors s_{t_i} et s_t sont confondus donc l'indice i est �gal � past->n-1
	//Sinon i=past->n-2
	int taille;
	if (fabs(t-temps*(past->n-1))<0.00001)
		taille = past->n-1;
	else
		taille = past->n-2;

	//G: matrice de dimension (N-taille)*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);
	//Grid: vecteur de taille N-taille+1 pour g�n�rer la grille de temps (t, t_{i+1}, ..., t_{N})
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);
	pnl_vect_set(grid, 0, t);
	for (int i=1; i<timeStep-taille+1; i++){
		//On calcule chaque date de constatation;
		pnl_vect_set(grid, i, temps*(i+taille));
	}

	//On met la trajectoire du mod�le dans path
	//On met les prix constat� jusqu'� la date t dans les taille+2 premi�res colonnes (cela correspond en fait au nombre de colonne de past)
	for (int i=0; i<taille+1; i++){
		//Extraction des colonnes de past dans extract pour les ins�rer dans path
		pnl_mat_get_col(extract, past, i);
		pnl_mat_set_col(path, extract, i);
	}

	for (int d=0; d<size; d++){
		//printf("%d/%d\n",d, size-1);
		for (int j=0; j<samples_; j++){
			if (t==T)
				pnl_mat_clone(path,past);
			else {
				mod_->asset(path, t, timeStep, T, rng, past, taille, G, grid);
			}
			// On r�cup�re la trajectoire shift�e
			mod_->shift_asset(_shift_path_plus, path, d, h_, t,timeStep);
			mod_->shift_asset (_shift_path_moins, path, d, -h_, t,timeStep);

			//On calcul la valeur du payoff et on retiens la diff�rence
			temps1 = opt_->payoff(_shift_path_plus);
			temps2 = opt_->payoff(_shift_path_moins);
			pnl_vect_set(tirages, j, temps1-temps2);
			// recuperation des (phi(plus)-pi(moins))�
			pnl_vect_set(tirages2, j, (temps1-temps2)*(temps1-temps2));
		}
		// somme des phi
		sum = pnl_vect_sum(tirages);
		// somme des phi�
		sum2 = pnl_vect_sum(tirages2);

		// calcul de delta
		facteur =  1/(2*(double)h_*(double)samples_*(double)pnl_mat_get(past, d, past->n-1));
		result =  exp(-r*(T-t))* facteur * sum;
		pnl_vect_set(delta, d, result);

		// calcul de l'intervalle de confiance
		sum = (sum*facteur)*(sum*facteur);
		resultic = exp(-r*(T-t))/2 * (facteur*sum2 - sum);
		resultic = 3.92*sqrt(resultic * 1/ (double)samples_);
		pnl_vect_set(ic, d, resultic);
	}

	pnl_mat_free(&G);
	pnl_mat_free(&path);
	pnl_mat_free(&_shift_path_plus);
	pnl_mat_free(&_shift_path_moins);
	pnl_vect_free(&tirages);
	pnl_vect_free(&tirages2);
	pnl_vect_free(&extract);
	pnl_vect_free(&grid);
}

void MonteCarlo::couv(PnlMat *past, double &pl, int H, double T)
{
	//Simulation du mod�le sous la probabilit� historique
	mod_->simul_market(past, H, T, rng);

	double r = mod_->get_r();
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	//temps_tau: pas de discr�tisation du temps avec H comme nombre de dates
	double temps_tau = T/H;
	//mult: coefficient multiplicateur de H et timeStep
	int mult = (int)(H/timeStep);
	//compteur: permet de savoir � quel length correspond les colonnes de past avec H dates et les colonnes dont on a besoin avec N dates
	int compteur = 0;
	int length =0;

	//prix: prix du sous-jacent � l'instant 0
	double prix;
	double ic;
	price(prix, ic);

	//delta1: vecteur contenant le delta � un instant donn�
	PnlVect* delta1 = pnl_vect_create(size);
	PnlVect* ic_vect = pnl_vect_create(size);

	//past_sub: matrice contenant la matrice past jusqu'� un instant donn�
	PnlMat* past_sub = pnl_mat_create(size,1);
	//pnl_mat_extract_subblock(past_sub, past, 0, size, 0, 1);
	MLET(past_sub, 0, 0) = 90;
	MLET(past_sub, 1, 0) = 80;
	MLET(past_sub, 2, 0) = 100;
	MLET(past_sub, 3, 0) = 120;
	MLET(past_sub, 4, 0) = 110;

	//extract: vecteur utilis� pour extraire des colonne de past et les ins�rer dans past_sub
	PnlVect* extract = pnl_vect_create(size);

	//S: vecteur contenant le prix dusous-jacent � un instant donn�
	PnlVect* S = pnl_vect_create(size);
	//result: vecteur contenant le r�sultat de la soustraction entre delta1 et delta2
	PnlVect* result;

	//Calcul � l'instant 0 de l'�volution de l'�volution de la part investie
	delta(past_sub, 0, delta1, ic_vect);
	pnl_mat_get_col(S, past, 0);

	PnlVect* V = pnl_vect_create(H);
	pnl_vect_set(V, 0, prix - pnl_vect_scalar_prod(delta1, S));
	compteur=mult;

	//delta2: vecteur contenant le delta � une date de constation pr�c�dente de delta1
	PnlVect* hist;
	for (int i=1; i<H+1; i++)
	{
		//On met dans delta2 la valeur du delta � l'instant i-1
		PnlVect* delta2 = pnl_vect_copy(delta1);

		//On cherche l'indice k tel que tau{i} < t_{k}�< tau_{i+1}
		//On met dans past_sub les colonne correspondant �
		//past[,j*mult] tel que j = 0..i
		//past_sub est une matrice de dimension size * (i+1)
		if (compteur == mult){
			length++;
			pnl_mat_resize(past_sub, size, length+1);
			compteur=0;
		}
		compteur++;
		for (int j=0; j<length; j++){
			//On extrait la colonne d'length j*mult de past 
			//et on l'ins�re dans la colonne d'length j de past
			pnl_mat_get_col(extract, past, j*mult);
			pnl_mat_set_col(past_sub, extract, j);
		}
		pnl_mat_get_col(extract, past, i);
		pnl_mat_set_col(past_sub, extract, length);

		if (i == H){
			hist = pnl_vect_copy(delta2);
			price(past_sub, temps_tau*i, prix, ic);
		}else{

			//Calcul du delta � l'instant i
			delta(past_sub, temps_tau*i, delta1, ic_vect);
			price(past_sub, temps_tau*i, prix, ic);

			//On met delta1 dans result pour pouvoir faire la soustraction de delta1 avec delta2 dans result car on aura besoin de delta1 dans la boucle suivant
			result = pnl_vect_copy(delta1);
			pnl_vect_minus_vect(result, delta2);

			pnl_mat_get_col(S, past, i);
			pnl_vect_set(V, i, pnl_vect_get(V,i-1) * exp(r*T/H) - pnl_vect_scalar_prod(result , S)); 
			pnl_vect_free(&result);
		}
		pnl_vect_free(&delta2);
	}
	//Calcul � l'instant H du delta et du prix des actifs
	pnl_mat_get_col(S, past, H);

	prix = opt_->payoff(past_sub);

	//Calcul de l'erreur de couverture
	pl = pnl_vect_get(V, H-1) * exp(r*T/H) + pnl_vect_scalar_prod(hist, S) - prix;

	pnl_vect_free(&V);
	pnl_vect_free(&S);
	pnl_vect_free(&hist);
	pnl_vect_free(&extract);
	pnl_mat_free(&past_sub);
	pnl_vect_free(&delta1);
	pnl_vect_free(&ic_vect);
}