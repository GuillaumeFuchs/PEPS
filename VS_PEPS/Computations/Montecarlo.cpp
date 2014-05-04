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
void MonteCarlo::price(
	double &prix, 
	double &ic)
{
	int size = opt_->get_size();
	int N = opt_->get_timeStep();
	double r = mod_->get_r();
	double T = opt_->get_T();
	//path: matrice représentant l'évolution du sous-jacent sur l'ensemble des pas de temps
	PnlMat *path = pnl_mat_create(size, N+1);
	//G: matrice de dimension N*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(N, size);
	//grid: vecteur de taille N+1 pour générer la grille de temps (t_0=0, ..., t_N)
	PnlVect *grid = pnl_vect_create(N+1);
	//tirages: vecteur de taille samples_ contenant les valeurs des M payoff
	PnlVect *tirages = pnl_vect_create(samples_);
	//temps: incrémentation pour chaque date de constation
	double temps = T/N;

	//Calcule de chaque date de constatation;
	for (int t=0; t<N+1; t++){
		LET(grid, t) = temps*t;
	}

	//Ajout du prix spot dans la première colonne de path
	pnl_mat_set_col(path, mod_->get_spot(), 0);

	for (int j=0; j<samples_; j++){
		//Génération de la trajectoire du modèle de Black Scholes
		mod_->asset(N, T, grid, path, G, rng);
		//Ajout du payoff dans tirages
		LET(tirages, j) = opt_->payoff(0., path);
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

void MonteCarlo::price(
	double t, 
	double &prix, 
	double &ic, 
	const PnlMat* past)
{
	double T = opt_->get_T();
	int size = opt_->get_size();
	int N = opt_->get_timeStep();
	double r = mod_->get_r();
	//path: matrice représentant l'évolution du sous-jacent sur l'ensemble des pas de temps
	PnlMat *path = pnl_mat_create(size, N+1);
	//dt: pas d'incrémentation
	double dt = T/N;
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
		prix = opt_->payoff(T, path);
		ic = 0;
		pnl_mat_free(&path);
		pnl_vect_free(&extractPast);
		return;
	}

	//tirages: vecteur de taille samples_ contenant la valeur des payoff de l'option
	PnlVect *tirages = pnl_vect_create(samples_);
	//G: matrice de dimension (N-taille)*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(N-taille, size);
	//grid: vecteur de taille N-taille+1 pour générer la grille de temps de t à t_N
	PnlVect *grid = pnl_vect_create(N-taille+1);
	LET(grid, 0) = t;
	for (int i=1; i<N-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}
	for (int j=0; j<samples_; j++){
		//Génération de l'évolution du sous-jacent par le modèle de Bs
		mod_->asset(N, taille, T, t, extractPast, grid, path, G, rng);
		//Ajout dans tirages
		LET(tirages, j) = opt_->payoff(t, path);
	}

	//Calcul du prix
	prix = (1./(double)samples_)*pnl_vect_sum(tirages);
	//Calcul de la variance
	ic = (3.92/sqrt((double)samples_)) * sqrt(
		(1./(double)samples_)*SQR(pnl_vect_norm_two(tirages))
		-SQR((1./(double)samples_)*pnl_vect_sum(tirages)));

	pnl_mat_free(&path);
	pnl_mat_free(&G);
	pnl_vect_free(&tirages);
	pnl_vect_free(&extractPast);
	pnl_vect_free(&grid);
}

void MonteCarlo::delta (
	double t, 
	PnlVect* delta, 
	PnlVect* ic, 
	const PnlMat* past)
{
	int size = opt_->get_size();
	int indice;
	int N = opt_->get_timeStep();
	double temps1 = 0;
	double temps2 = 0;
	double sum, sum2;
	double facteur, facteur_com;
	double result, resultic;
	double T = opt_->get_T();
	double r = mod_->get_r();

	//Initialisation de path comme une matrice de dimension d x (N+1)
	PnlMat *path = pnl_mat_create(size, N+1);
	//temps: incrémentation pour chaque date de constatation
	double dt = T/N;
	//extractPast: vecteur de taille size servant à extraire de la matrice past les colonnes pour les insérer dans path
	PnlVect *extractPast = pnl_vect_create(size);
	PnlMat *shift_path_plus = pnl_mat_create(size, N+1);
	PnlMat *shift_path_moins = pnl_mat_create(size, N+1);
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
	PnlMat *G = pnl_mat_create(N-taille, size);

	//Grid: vecteur de taille N-taille+1 pour générer la grille de temps (t, t_{i+1}, ..., t_{N})
	PnlVect *grid = pnl_vect_create(N-taille+1);
	LET(grid, 0) = t;
	for (int i=1; i<N-taille+1; i++){
		LET(grid, i) = dt*(i+taille);
	}

	for (int j=0; j<samples_; j++){
		mod_->asset(N, taille, T, t, extractPast, grid, path, G, rng);
		for (int d=0; d<size; d++){
			// On récupère la trajectoire shiftée
			//Si on est à maturité, on fait varier le spot à maturité et on observe le payoff
			//Sinon on fait varier le spot à t + dt et on observe le payoff
			mod_->shift_asset(d, taille+1, h_, shift_path_plus, path);
			mod_->shift_asset (d, taille+1, -h_, shift_path_moins, path);

			//On calcul la valeur du payoff et on retiens la dtérence
			temps1 = opt_->payoff(t, shift_path_plus);
			temps2 = opt_->payoff(t, shift_path_moins);
			MLET(tirages, j, d) = temps1-temps2;
			// recuperation des (phi(plus)-pi(moins))²
			MLET(tirages2, j, d) = (temps1-temps2)*(temps1-temps2);
		}
	}

	facteur_com = 1./(2.*h_*(double)samples_);
	for (int d = 0; d < size; d++){
		//calcul delta
		pnl_mat_get_col(tiragesRow, tirages, d);
		facteur = facteur_com/MGET(past, d, past->n-1);
		result = facteur * pnl_vect_sum(tiragesRow);
		LET(delta, d) = result;

		//calcul ic
		pnl_mat_get_col(tiragesRow, tirages2, d);
		resultic = (3.92/sqrt((double)samples_)) * sqrt(
			(1./(double)samples_)*pnl_vect_sum(tiragesRow)
			- (result * result));
		LET(ic, d) = resultic;
	}


	pnl_mat_free(&G);
	pnl_mat_free(&path);
	pnl_mat_free(&shift_path_plus);
	pnl_mat_free(&shift_path_moins);
	pnl_mat_free(&tirages);
	pnl_mat_free(&tirages2);
	pnl_vect_free(&tiragesRow);
	pnl_vect_free(&extractPast);
	pnl_vect_free(&grid);
}

void MonteCarlo::couv(
	int H,
	double T,
	double& pl,
	PnlMat *past, 
	PnlMat *summary)
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
	mod_->simul_market(H, T, past, rng);

	//
	//COMPUTE IN 0
	//
	//Price
	price(priceVal, ic);
	
	//Delta
	pnl_mat_get_col(S, past, 0);
	pnl_mat_set_col(past_sub, S, 0);
	delta(0, delta_i, ic_vect, past_sub);
	
	//Compute portfolios (risk and risk-free)
	//simulate
	pF = priceVal;
	pF_risk = pnl_vect_scalar_prod(delta_i, S);
	pF_risk_free = priceVal - pF_risk;
	
	//Add informations in summary matrix
	//simulate
	MLET(summary, 0, 0) = 0;
	for (int d = 0; d < size; d++){
		pnl_mat_get_row(past_extract, past, d);
		pnl_mat_set_col(summary, past_extract, 1+d);
		MLET(summary, 0, 1+size+d) = GET(delta_i, d);
	}
	MLET(summary, 0, 2*size+1) = priceVal;
	MLET(summary, 0, 2*size+2) = pF_risk;
	MLET(summary, 0, 2*size+3) = pF_risk_free;
	MLET(summary, 0, 2*size+4) = pF;

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
		delta(timeH*i, delta_i, ic_vect, past_sub);

		//Compute price at tau_i
		price(timeH*i, priceVal, ic, past_sub);

		//Compute portfolios
		//simulate
		trade = GET(delta_i, 0) - GET(delta_i_1, 0);
		pF_risk = pnl_vect_scalar_prod(delta_i, S);
		pF_risk_free = pF_risk_free_ant*update + pnl_vect_scalar_prod(delta_i_1, S) - pF_risk;
		pF = pF_risk + pF_risk_free;

		//Add informations in summary matrix
		//simulate
		MLET(summary, i, 0) = timeH*i;
		for (int d = 0; d < size; d++)
			MLET(summary, i, 1+size+d) = GET(delta_i, d);
		MLET(summary, i, 2*size+1) = priceVal;
		MLET(summary, i, 2*size+2) = pF_risk;
		MLET(summary, i, 2*size+3) = pF_risk_free;
		MLET(summary, i, 2*size+4) = pF;
	}
	price(T, priceVal, ic, past);

	//P&L compute
	pl = pF - priceVal;

	pnl_vect_free(&S);
	pnl_vect_free(&delta_i_1);
	pnl_vect_free(&delta_i);
	pnl_vect_free(&ic_vect);
	pnl_vect_free(&past_extract);
}

void MonteCarlo::compute_portfolio(
	int H, 
	double T, 
	double t, 
	double& risk_free,
	double& risk,
	double& priceVal,
	double& ciVal,
	double& err,
	PnlVect* delta_ant,
	const PnlMat *past) 
{
	int size = opt_->get_size();
	double r = mod_->get_r();
	double timeH = T/H; //timestep of the hedging

	PnlVect *delta_t = pnl_vect_create(size); //delta at t
	PnlVect* ci_t = pnl_vect_create(size); //confidence interval for delta at t
	PnlVect* spot = pnl_vect_create(size); //spot at t

	//Get spot price
	pnl_mat_get_col(spot, past, past->n-1);

	//Compute delta at t
	delta(t, delta_t, ci_t, past);

	//Compute portfolios (risk and risk_free)
	risk = pnl_vect_scalar_prod(delta_t, spot);
	
	if (t == 0.00){
		price(priceVal, ciVal);
		risk_free = priceVal - risk;
	}
	else{
		price(t, priceVal, ciVal, past);
		risk_free = risk_free*exp(r*timeH) + pnl_vect_scalar_prod(delta_ant,spot) - risk;
	}

	//Update delta risk portfolio 
	for (int i = 0; i < size; i++)
		LET(delta_ant, i) = GET(delta_t, i);

	err = (risk_free+risk) / priceVal - 1 ;
	pnl_vect_free(&delta_t);
	pnl_vect_free(&ci_t);
	pnl_vect_free(&spot);
}