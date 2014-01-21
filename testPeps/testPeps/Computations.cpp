

#include "Asian.h"
#include "Barrier.h"
#include "Barrier_l.h"
#include "Barrier_u.h"
#include "Basket.h"
#include "Performance.h"
#include "Playlist.h"

/* Computation librairies */
#include "Computations.h"
#include "Montecarlo.h"
#include "Bs.h"

/* Others librairies */
#include "pnl/pnl_random.h"
#include "pnl/pnl_cdf.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <fstream>


using namespace std;

double delta_theorique(double S, double K, double r, double T, double sigma){
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

double prix_theorique(double S, double K, double r, double T, double sigma){
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


int main(){	
    double prix;
    double ic;
    double pl;
    double plTheorique;

    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));
    
    int const size = 1;
    double strike = 100;
    double spot[size] = {100};//, 80, 100, 120, 110};
    double T = 1;
    double sigma[size] = {0.2};//, 0.2, 0.2, 0.15, 0.15};	
    double r = .05;
    double coeff[size] = {1.};// , .2, .2, .2, .2};
    int N = 5;
    int samples = 10;
    double t = .2;
    int H = 360;

    PnlMat *past = pnl_mat_create(size, H+1);    
    PnlVect *delta = pnl_vect_create(size);
    PnlVect *ic_delta = pnl_vect_create(size);

    Bs bs(size, r, NULL, sigma, spot, NULL);
    Basket opt(strike, coeff, T, N, size);
    MonteCarlo mc(&bs, &opt, rng, 0.01, samples);

    /*Prix en 0
    mc.price(prix, ic);
    double prix_th = prix_theorique(spot[0], strike, r, T, sigma[0]);
    printf("Prix(0): %f \nPrix theorique: %f\n\n", prix, prix_th);

    /*Calcul Prix t
    bs.simul_market(past, H, t, rng);
    pnl_mat_print(past);
    mc.price(past, t, prix, ic);
    double prix_th = prix_theorique(MGET(past, 0, H), strike, r, T-t, sigma[0]);
    printf("Prix(%f): %f \nPrix theorique: %f\n\n", t, prix, prix_th);

    /*Calcul Delta
    bs.simul_market(past, H, t, rng);
    pnl_mat_print(past);
    mc.delta(past, t, delta, ic_delta);
    printf("Delta(%f)\n", t);
    pnl_vect_print(delta);
    double delta_th = delta_theorique(MGET(past, 0, H), strike, r, T-t, sigma[0]);
    printf("Delta théorique: %f\n", delta_th);

    /*Couverture
    ofstream fichier1(c"ouv_simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    ofstream fichier2("couv_theorique.txt", ios::out | ios::trunc);
    if(fichier1 && fichier2)
    {
    for (int i = 0; i < 500; i++){
    */
            mc.couv(past, pl, plTheorique, H, T);
            /*mc.price(prix, ic);
            double prix_th = prix_theorique(100., 100., .05, 1., .2);
            cout << endl;
            cout << pl/prix << endl;
            cout << plTheorique/prix_th << endl;
            /*
            fichier1 << pl/prix << endl;
            fichier2 << plTheorique/prix_th << endl;
    }
        fichier1.close();
        fichier2.close();
    }else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        */

    system("pause");

    return 0;
}
