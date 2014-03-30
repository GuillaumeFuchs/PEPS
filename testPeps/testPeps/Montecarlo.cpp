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

void MonteCarlo::couv(PnlMat *past, double &pl, int H, double T, PnlMat *summary_simul)
{
	int size = opt_->get_size();
	int timeStep = opt_->get_timeStep();
	double r = mod_->get_r();
	double timeH = T/H; //timestep of the hedging
	double update = exp(r*timeH); //term of actualisation
	double priceVal;
	double ic;
	PnlVect* delta_i = pnl_vect_create(size);
	PnlVect* delta_i_1 = pnl_vect_create(size); 
	PnlVect* ic_vect = pnl_vect_create(size);
	PnlMat* past_sub = pnl_mat_create(size, 1);
	PnlVect* past_extract = pnl_vect_create(H+1);
	PnlVect* S = pnl_vect_create(size); 	//spot
	PnlVect* result;
	double pF; //portfolio value (simualte)
	double pF_risk; //risked portfolio value (simulate)
	double pF_risk_free; //risk-free portfolio value (simulate)
	double pF_risk_free_ant; //risk-free portfolio previous value (simulate)
	double trade; //trade of asset

	//
	//SIMULATION OF AN ASSET TO HEDGE
	//
	mod_->simul_market(past, H, T, rng);
	printf("%f\n", MGET(past, 0, H));
	//
	//COMPUTE IN 0
	//
	//Price
	price(priceVal, ic);
	
	//Delta
	pnl_mat_get_col(S, past, 0);
	pnl_mat_set_col(past_sub, S, 0);
	delta(past_sub, 0, delta_i, ic_vect);
	
	//Compute portfolios (risk and risk-free)
	//simulate
	pF = priceVal;
	pF_risk = pnl_vect_scalar_prod(delta_i, S);
	pF_risk_free = priceVal - pF_risk;
	
	//Add informations in summary matrix
	//simulate
	MLET(summary_simul, 0, 0) = 0;
	for (int d = 0; d < size; d++){
		pnl_mat_get_row(past_extract, past, d);
		pnl_mat_set_col(summary_simul, past_extract, 1+d);
		MLET(summary_simul, 0, 1+size+d) = GET(delta_i, d);
	}
	MLET(summary_simul, 0, 2*size+1) = priceVal;
	MLET(summary_simul, 0, 2*size+2) = pF_risk;
	MLET(summary_simul, 0, 2*size+3) = pF_risk_free;
	MLET(summary_simul, 0, 2*size+4) = pF;

	//
	//COMPUTE IN t>0
	//
	for (int i=1; i<H+1; i++)
	{
		printf("%d\n", i);
		//Save delta at i-1
		delta_i_1 = pnl_vect_copy(delta_i);
		//Save portfolio risk free value at i-1
		pF_risk_free_ant = pF_risk_free;

		//Compute delta at tau_i
		pnl_mat_resize(past_sub, size, i+1);
		for (int j=0; j<i+1; j++){
			pnl_mat_get_col(S, past, j);
			pnl_mat_set_col(past_sub, S, j);
		}
		delta(past_sub, timeH*i, delta_i, ic_vect);

		//Compute price at tau_i
		price(past_sub, timeH*i, priceVal, ic);

		//Compute portfolios
		//simulate
		trade = GET(delta_i, 0) - GET(delta_i_1, 0);
		pF_risk = pnl_vect_scalar_prod(delta_i, S);
		pF_risk_free = pF_risk_free_ant*update + pnl_vect_scalar_prod(delta_i_1, S) - pF_risk;
		pF = pF_risk + pF_risk_free;

		//Add informations in summary matrix
		//simulate
		MLET(summary_simul, i, 0) = timeH*i;
		for (int d = 0; d < size; d++)
			MLET(summary_simul, i, 1+size+d) = GET(delta_i, d);
		MLET(summary_simul, i, 2*size+1) = priceVal;
		MLET(summary_simul, i, 2*size+2) = pF_risk;
		MLET(summary_simul, i, 2*size+3) = pF_risk_free;
		MLET(summary_simul, i, 2*size+4) = pF;
	}
	price(past, T, priceVal, ic);

	//Calcul de l'erreur de couverture
	pl = pF_risk_free + pnl_vect_scalar_prod(delta_i, S) - priceVal;

	pnl_vect_free(&S);
	pnl_vect_free(&delta_i_1);
	pnl_vect_free(&delta_i);
	pnl_vect_free(&ic_vect);
	pnl_vect_free(&past_extract);
}