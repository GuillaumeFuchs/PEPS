#include "Asian.h"
#include "Barrier.h"
#include "Barrier_l.h"
#include "Barrier_u.h"
#include "Basket.h"
#include "Performance.h"
#include "Playlist.h"

/* Computation librairies */
#include "Computations.h"
#include "Montecarlos.h"
#include "Montecarlo.h"
#include "Modelasset.h"
#include "Bs.h"

/* Others librairies */
#include "pnl/pnl_random.h"
#include "pnl/pnl_cdf.h"
#include <cstdio>
#include <ctime>


#include "Test.h"


using namespace std;

int main(){	
	double prix = 0; 
	double ic = 0;
	double pl;
	double plTheorique;

	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, time(NULL));

	int const size = 1;
	double strike = 100;
	double spot[size] = {100};//, 80, 100, 120};
	double T = 1;
	double sigma[size] = {0.2};//, 0.2, 0.2, 0.15};	
	double r = .05;
<<<<<<< HEAD
	double coeff[size] = {1.};// , .2, .2, .2, .2};
	int N = 1;
	int samples = 20000;
	int H = 200;

	PnlMat *past = pnl_mat_create(size, H+1);    
	PnlVect *delta = pnl_vect_create(size);
	PnlVect *ic_delta = pnl_vect_create(size);
	Bs mod(size, r, NULL, sigma, spot, NULL);
	Basket opt(strike, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, samples);
	
	/*vector<double> v;
	int rejet = 0;
	double t;
	for (int k = 0; k < 1000; k++){
		t = pnl_rng_uni(rng);
		PnlMat* past = pnl_mat_create(1, (int)(t*100)+1);
		//rejet += compute_prix(prix, ic, &mc, &mod, past, (int)(t*100), (int)(t*100)/100., spot, strike, r, T, sigma, rng, &v);
		rejet += compute_delta(delta, ic_delta, &mc, &mod, past, (int)(t*100), (int)(t*100)/100. , strike, r, T, sigma, rng, &v);
		pnl_mat_free(&past);
	}
	printf("Taux de prix dont l'écart avec prix_th est superieur a 0,5: %f \n", (double)rejet*100./1000.); 
	sort(v.begin(), v.end());
	for (vector<double>::iterator it=v.begin(); it!=v.end(); ++it)
		cout << *it << endl;
		*/
<<<<<<< HEAD
=======

>>>>>>> c8180235e9eaa8e3e5a0e78ce65b96d80c6f601e
	//Couverture
	ofstream fichier1("couv_simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
	ofstream fichier2("couv_theorique.txt", ios::out | ios::trunc);
	if(fichier1 && fichier2)
	{
	for (int i = 0; i < 500; i++){
	mc.couv(past, pl, plTheorique, H, T);
	mc.price(prix, ic);
	double prix_th = prix_theorique(100., 100., .05, 1., .2);
	cout << endl;
	cout << pl/prix << endl;
	cout << plTheorique/prix_th << endl;
	
	fichier1 << pl/prix << endl;
	fichier2 << plTheorique/prix_th << endl;
	}
	fichier1.close();
	fichier2.close();
	}else
	cerr << "Impossible d'ouvrir le fichier !" << endl;
	
=======
	double coeff[size] = {1};//, .25, .25, .25};
	//double rho[size*(size-1)/2] = {0., 0., 0., 0., 0., 0.};
	int N = 10;
	int samples = 50000;
	int H = 25;
	double t = 0.5;

	

	Bs mod(size, r, NULL, sigma, spot, NULL);
	Basket opt(strike, coeff, T, N, size);
	MonteCarlo mc(&mod, &opt, rng, 0.01, samples);
	Test test(&mc);

	//test.compute_prix_samples(1000, true);
	test.compute_delta_samples(1000, true);
	//test.compute_prix(25, 0.5);
	//test.compute_delta(25, 0.5);
	//test.compute_couv(50, false);
>>>>>>> commit

	system("pause");

	return 0;
}
