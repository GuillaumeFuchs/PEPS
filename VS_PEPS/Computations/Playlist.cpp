#include "Playlist.h"
#include <math.h>
#include <iostream>
using namespace std;
/*!
* \file Playlist.cpp
* \brief Option panier
* \author Equipe 11
*/

Playlist :: Playlist() : Option() {
}

Playlist::Playlist(double T, int timeStep, int size, double r, double *coeff) : Option(T, timeStep, size, r, coeff){
}

Playlist :: ~Playlist(){
}

double Playlist :: payoff (const PnlMat *path, double t) const{
	PnlVect* S0 = pnl_vect_create(size_);
	pnl_mat_get_col(S0, path, 0);

	double gain = 0.;
	int compteur20, compteur10;
	double s, s0;
	double progression;

	//Traitement de t = 1, t = 2
 	for (int k = 1; k < 3; k++){
		compteur10 = 0;
		compteur20 = 0;
		for (int d = 0; d < size_; d++){
			s = MGET(path, d, k*timeStep_/6);
			s0 = GET(S0, d);
			progression = (s/s0 - 1)*100.;

			//Cas où l'indice a progressé de 10%
			if (fabs(progression - 10.) < 0.0001 || progression > 10.){
				compteur10++;

				//Cas où l'indice a progressé de 20%
				if (fabs(progression - 20.) < 0.0001 || progression > 20.){
					compteur20++;
					//Cas où plus de 3 indices ont progressé de 20%
					if (compteur20 > 2){
						gain += 0.045;
						pnl_vect_free(&S0);
						//Cas où on price à un temps t et que le produit s'est déjà executé
						if ((double)k < t)
							return 0;

						return exp(-r_*((double)k - t)) * 150. * (1. + gain);

					}
				}
				//Cas où plus de 30 indices ont progressé de 20%
				if (compteur10 > 2){
					gain += 0.045;
					break;
				}
			}
		} 
	}

	//Traitement de t = 3 à t = 6
	for (int k = 3; k < 7; k++){
		compteur10 = 0;
		for (int d = 0; d < size_; d++){
			s = MGET(path, d, k*timeStep_/6);
			s0 = GET(S0, d);
			progression = (s/s0 - 1)*100.;

			if (fabs(progression - 10) < 0.0001 || progression > 10.){
				compteur10++;
				if (compteur10 > 2){
					gain += 0.045;
					break;
				}
			}
		}
	}
	pnl_vect_free(&S0);
	return exp(-r_*(6.-t)) * 150. * (1.+gain);
}
