#include "Bs.h"
#include <math.h>
#include <cstdio>
#include <iostream>

using namespace std;

Bs::Bs() : ModelAsset() {
}

Bs::Bs(int size, double r, double* rho, double* sigma, double* spot, double* trend) : ModelAsset(size, r, rho, sigma, spot, trend){
}

Bs::~Bs(){
}

void Bs::asset(
	int N, 
	double T, 
	PnlVect* grid, 
	PnlMat *path, 
	PnlMat *G, 
	PnlRng *rng)
{
	//s: double pour la valeur du sous-jacent à la date t_{i+1}
	double s;
	//diff: double t_{i+1}-t_{i}
	double diff;

	//Simulation de la suite (G_i)i>=1 iid de vecteurs gaussiens centrés de matrice de covariance identité
	pnl_mat_rng_normal(G, N, size_, rng);
	//Calcul de l'évolution du sous-jacent de chaque actif pour t=t_1 à t=t_N;
	for (int d=0; d<size_; d++){
		for (int i=0; i<N; i++){
			//Sélection de la ligne de la matrice de Cholesky associé à l'actif sur lequel on travaille
			pnl_mat_get_row(Ld_, Cho_, d);
			//Sélection de la ligne de la matrice de vecteurs gaussiens associé au temps sur lequel on travaille
			pnl_mat_get_row(Gi_, G, i);
			//Calcul de la différence de pas de temps
			diff = GET(grid, i+1)-GET(grid, i);
			//Calcul de l'évolution du sous-jacent à l'aide de la formule du modèle de BS
			s = MGET(path, d, i)*
				exp((r_-pow(GET(sigma_, d),2.0)/2)*diff +
				GET(sigma_, d)*sqrt(diff)*pnl_vect_scalar_prod(Ld_, Gi_));
			//Ajout du résultat dans path
			MLET(path, d, i+1) = s;
		}
	}
}

void Bs::asset(
	int N, 
	int taille, 
	double T, 
	double t, 
	const PnlVect* pastT, 
	const PnlVect* grid, 
	PnlMat* path,
	PnlMat* G, 
	PnlRng *rng)
{
	//s: double pour la valeur du sous-jacent à la date t_{i+1}
	double s;
	//diff: double t_{i+1}-t_{i}
	double diff;

	//Simulation de la suite (G_i)i>=1 iid de vecteurs gaussiens centés de matrice de covariance identité
	pnl_mat_rng_normal(G, N-taille, size_, rng);
	//Calcul de l'évolution du sous-jacent de chaque actif pour t=t_{i+1} à t=t_N;
	for (int d=0; d<size_; d++){
		for (int i=0; i<N-taille; i++){
			//Sélection de la ligne de la matrice de Cholesky associé à l'actif sur lequel on travaille
			pnl_mat_get_row(Ld_, Cho_, d);
			//Sélection de la ligne de la matrice de vecteurs gaussiens associé au temps sur lequel on travaille
			pnl_mat_get_row(Gi_, G, i);
			//Calcul de la différence de pas
			diff = GET(grid, i+1)-GET(grid,i);

			if (i == 0){
				s = GET(pastT, d);
			} else {
				s = MGET(path, d, i+taille);
			}
			//Calcul de l'évolution du sous-jacent à l'aide de la formule du modèle de Bs
			s = s*exp((r_-pow(GET(sigma_, d),2.0)/2)*diff + GET(sigma_, d) * sqrt(diff) * pnl_vect_scalar_prod(Ld_, Gi_));
			//Ajout du résultat dans path
			MLET(path, d, i+taille+1) =  s;
		}
	}
}

void Bs::shift_asset(
	int d,
	int indice,
	double h,
	PnlMat* shift_path, 
	const PnlMat *path)
{
		pnl_mat_clone(shift_path, path);
		for (int i = indice; i < path->n; i++)
			MLET(shift_path, d,i) =  (1+h)*MGET(path, d,i);
}

void Bs:: simul_market (
	int H, 
	double T, 
	PnlMat* past, 
	PnlRng* rng)
{
	if (T == 0){
		pnl_mat_resize(past, past->m, 1);
		pnl_mat_set_col(past, spot_, 0);
		return;
	}

	//Temps: incrémentation pour chaque date de constation
	double temps = T/H;
	//s: valeur du sous-jacent à la date t_{i+1}
	double s;
	//diff: calcul de la différence de temps entre t_{i+1} et t_{i}
	double diff;
	//G: matrice de dimension H*d pour générer une suite iid selon la loi normale centrée réduite
	PnlMat *G = pnl_mat_create(H, size_);
	//Grid: vecteur de taille H+1 pour générer la grille de temps (t_0=0, ..., t_N)
	PnlVect *grid = pnl_vect_create(H+1);

	//Calcul des dates de constatation;
	for (int t=0; t<H+1; t++){
		LET(grid, t) = temps*t;
	}
	//Ajout de la trajectoire du modèle dans past
	//Ajout du prix spot dans la première colonne de path
	pnl_mat_set_col(past, spot_, 0);
	//Simulation de la suite (G_i)i>=1 iid de vecteurs gaussiens centés de matrice de covariance identité
	pnl_mat_rng_normal(G, H, size_, rng);
	//Calcul de l'évolution du sous-jacent de chaque actif pour t=tau_1 à t=tau_H;
	//Idem à asset pour t>0 mais on utilise le taux d'intérêt sous la probabilité historique
	//et on ajoute les résultats dans la matrice past
	for (int d=0; d<size_; d++){
		for (int i=0; i<H; i++){
			pnl_mat_get_row(Ld_, Cho_, d);
			pnl_mat_get_row(Gi_, G, i);
			diff = GET(grid, i+1)-GET(grid, i);
			s = MGET(past, d, i)*
				exp((GET(trend_, d)-pow(GET(sigma_, d),2.0)/2)*diff +
				GET(sigma_, d)*sqrt(diff)*pnl_vect_scalar_prod(Ld_, Gi_));
			MLET(past, d, i+1) = s;
		}
	}

	pnl_mat_free(&G);
	pnl_vect_free(&grid);
}
