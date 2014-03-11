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
	//path: matrice représentant l'évolution du sous-jacent sur l'ensemble des pas de temps
	PnlMat *path = pnl_mat_create(size, TimeSteps+1);
	//G: matrice de dimension N*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(TimeSteps, size);
	//grid: vecteur de taille N+1 pour générer la grille de temps (t_0=0, ..., t_N)
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
		LET(tirages, j) = opt_->payoff(path, 0.);
	}

	//Calcul du prix à l'aide de la formule de MC
	prix = (1./(double)samples_)*pnl_vect_sum(tirages);
	//Calcul de la variance de l'estimateur pour avoir l'intervalle de confiance
	ic = (3.92/sqrt((double)samples_) )* sqrt(exp(-2.*r*T)*((1./(double)samples_)*SQR(pnl_vect_norm_two(tirages))-SQR((1./(double)samples_)*pnl_vect_sum(tirages))));

	pnl_vect_free(&grid);
	pnl_vect_free(&tirages);
	pnl_mat_free(&path);
	pnl_mat_free(&G);
}

void MonteCarlo::price(const PnlMat *past, double t, double &prix, double &ic){
	double T = opt_->get_T();
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double r = mod_->get_r();
	//path: matrice représentant l'évolution du sous-jacent sur l'ensemble des pas de temps
	PnlMat *path = pnl_mat_create(size, timeStep+1);
	//dt: pas d'incrémentation
	double dt = T/timeStep;
	//extractPast: vecteur de taille size servant à extraire de la matrice past les colonnes pour les insérer dans path
	PnlVect *extractPast = pnl_vect_create(size);
	//H: nombre de pas d'incrémentation de past
	int H = past->n - 1;

	//Si t = 0, on met uniquement la premiere colonne de past dans path
	//sinon on ajoute les colonnes de past qui possède un pas de temps dans path
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

	//Cas où on price à maturité
	//Toutes les informations sont déjà déterminés à l'aide de past
	//donc on a besoin d'aucune simulation
	//et l'intervalle de confiance est de 0 car on est dans un calcul du prix déterministe
	if (t == T){
		prix = opt_->payoff(path, T);
		ic = 0;
		pnl_mat_free(&path);
		pnl_vect_free(&extractPast);
		return;
	}

	//tirages: vecteur de taille samples_ contenant la valeur des payoff de l'option
	PnlVect *tirages = pnl_vect_create(samples_);
	//G: matrice de dimension (N-taille)*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);
	//grid: vecteur de taille N-taille+1 pour générer la grille de temps de t à t_N
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);
	LET(grid, 0) = t;
	for (int i=1; i<timeStep-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}

	for (int j=0; j<samples_; j++){
		//Génération de l'évolution du sous-jacent par le modèle de Bs
		mod_->asset(path, t, timeStep , T, rng, extractPast, taille, G, grid);
		//Ajout dans tirages
		LET(tirages, j) = opt_->payoff(path, t);
	}

	//Calcul du prix
	prix = (1./(double)samples_)*pnl_vect_sum(tirages);
	//Calcul de la variance
	ic = (3.92/sqrt((double)samples_)) * sqrt(((1./(double)samples_)*SQR(pnl_vect_norm_two(tirages))-SQR((1./(double)samples_)*pnl_vect_sum(tirages))));

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

	//Delta à maturité
	//Si le payoff est positif alors la somme des deltas vaut 1
	//et chaque actif à un delta correspondant à son coefficnent
	if (fabs(T-t) < 0.00001){
		//Cas où le payoff est positif
		if (fabs(opt_->payoff(past, t)) > 0.001){
			PnlVect *coeff = opt_->get_Coeff();
			for (int d = 0; d < size; d++){
				LET(delta, d) =  GET(coeff, d);
			}
		} else {
			for (int d = 0; d < size; d++){
				LET(delta, d) =  0;
			}
		}
		return;
	}

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
	PnlMat *tirages = pnl_mat_create(samples_, size);
	PnlMat *tirages2 =  pnl_mat_create(samples_, size);
	PnlVect *tiragesRow = pnl_vect_create(samples_);

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
	//G: matrice de dimension (N-taille)*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(timeStep-taille, size);

	//Grid: vecteur de taille N-taille+1 pour générer la grille de temps (t, t_{i+1}, ..., t_{N})
	PnlVect *grid = pnl_vect_create(timeStep-taille+1);
	LET(grid, 0) = t;
	for (int i=1; i<timeStep-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}

	for (int j=0; j<samples_; j++){
		mod_->asset(path, t, timeStep, T, rng, extractPast, taille, G, grid);
		for (int d=0; d<size; d++){
			// On récupère la trajectoire shiftée
			mod_->shift_asset(_shift_path_plus, path, d, h_, taille+1);
			mod_->shift_asset (_shift_path_moins, path, d, -h_, taille+1);
			//On calcul la valeur du payoff et on retiens la dtérence
			temps1 = opt_->payoff(_shift_path_plus, t);
			temps2 = opt_->payoff(_shift_path_moins, t);
			MLET(tirages, j, d) = temps1-temps2;
			// recuperation des (phi(plus)-pi(moins))²
			MLET(tirages2, j, d) = (temps1-temps2)*(temps1-temps2);
		}
	}

	for (int d = 0; d < size; d++){
		pnl_mat_get_col(tiragesRow, tirages, d);
		// somme des phi
		sum = pnl_vect_sum(tiragesRow);

		pnl_mat_get_col(tiragesRow, tirages2, d);
		// somme des phi²
		sum2 = pnl_vect_sum(tiragesRow);

		// calcul de delta
		facteur =  1./(2.*h_*(double)samples_*MGET(past, d, past->n-1));
		result = facteur * sum;
		LET(delta, d) = result;

		// calcul de l'intervalle de confiance
		sum = (sum*facteur)*(sum*facteur);
		resultic = exp(r*(T-t))/2 * (facteur*sum2 - sum);
		resultic = 3.92*sqrt(resultic * 1./(double)samples_);
		LET(ic, d) = resultic;
	}


	pnl_mat_free(&G);
	pnl_mat_free(&path);
	pnl_mat_free(&_shift_path_plus);
	pnl_mat_free(&_shift_path_moins);
	pnl_mat_free(&tirages);
	pnl_mat_free(&tirages2);
	pnl_vect_free(&tiragesRow);
	pnl_vect_free(&extractPast);
	pnl_vect_free(&grid);
}

void MonteCarlo::couv(PnlMat *past, double &pl, double &plTheorique, int H, double T, PnlMat *summary)
{
	//Simulation du modèle sous la probabilité historique
	mod_->simul_market(past, H, T, rng);

	double r = mod_->get_r();
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double timeH = T/H;

	//delta1: vecteur contenant le delta à un instant donné
	PnlVect* delta1 = pnl_vect_create(size);
	PnlVect* ic_vect = pnl_vect_create(size);
	PnlMat* past_sub = pnl_mat_create(size, 1);
	PnlVect* past_extract = pnl_vect_create(H+1);
	//S: vecteur contenant le prix dusous-jacent à un instant donné
	PnlVect* S = pnl_vect_create(size);
	//result: vecteur contenant le résultat de la soustraction entre delta1 et delta2
	PnlVect* result;
	PnlVect* pF = pnl_vect_create(H+1);

	//prix: prix du sous-jacent à l'instant 0
	double prix;
	double ic;
	price(prix, ic);
	//Ajout du cours de l'action dans summary
	for (int i = 0; i < size; i++){
		pnl_mat_get_row(past_extract, past, i);
		pnl_mat_set_col(summary, past_extract, 1+3*i);
	}

	//Calcul à l'instant 0 de la composition du portefeuille
	pnl_mat_get_col(S, past, 0);
	pnl_mat_set_col(past_sub, S, 0);

	delta(past_sub, 0, delta1, ic_vect);

	LET(pF, 0) = prix - pnl_vect_scalar_prod(delta1, S);
	//Ajout dans summary de la date, du delta & du nombre d'actions à acheter, du delta théorique & du nombre d'actions théorique à acheter
	MLET(summary, 0, 0) = 0.;
	for (int i = 0; i < size; i++){
		MLET(summary, 0, 2+3*i) = GET(delta1, i);
		MLET(summary, 0, 3+3*i) = GET(delta1, i);
	}

	//delta2: vecteur contenant le delta à une date de constation précédente de delta1
	for (int i=1; i<H+1; i++)
	{
		//On met dans delta2 la valeur du delta à l'instant i-1
		PnlVect* delta2 = pnl_vect_copy(delta1);

		//Calcul du delta & du prix à l'instant tau_i
		pnl_mat_resize(past_sub, size, i+1);
		for (int j=0; j<i+1; j++){
			pnl_mat_get_col(S, past, j);
			pnl_mat_set_col(past_sub, S, j);
		}
		delta(past_sub, timeH*i, delta1, ic_vect);
		price(past_sub, timeH*i, prix, ic);

		//Ajout des informations dans summary
		MLET(summary, i, 0) = timeH*(double)i;
		for (int j = 0; j < size; j++){
			MLET(summary, i, 2+3*j) = GET(delta1, j);
			MLET(summary, i, 3+3*j) = GET(delta1, j) - GET(delta2, j);
		}

		result = pnl_vect_copy(delta1);
		pnl_vect_minus_vect(result, delta2);

		LET(pF, i) = GET(pF,i-1) * exp(r*T/H) - pnl_vect_scalar_prod(result , S);

		pnl_vect_free(&delta2);
	}
	//Calcul de l'erreur de couverture
	pl = GET(pF, H) + pnl_vect_scalar_prod(delta1, S) - prix;

	pnl_vect_free(&pF);
	pnl_vect_free(&S);
	pnl_vect_free(&delta1);
	pnl_vect_free(&ic_vect);
	pnl_vect_free(&past_extract);
}