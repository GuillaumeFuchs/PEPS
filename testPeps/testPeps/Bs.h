#ifndef BsH
#define BsH
#include "Modelasset.h"
#include <pnl/pnl_vector.h>
#include <pnl/pnl_random.h>

/*!
 * \class Bs
 * \brief Classe representant le modele de Black Scholes
 */
class Bs : public ModelAsset {
  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe Bs
	 */
	Bs();
	Bs(int size, double r, double* rho, double* sigma, double* spot, double* trend);


	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Bs
	 */
	virtual ~Bs();

	/*!
	 * \brief Génère une trajectoire du modele et la stocke dans path
	 *
	 * \param path contient une trajectoire du modele. C’est une matrice de dimension d x (N+1)
	 * \param T  maturite
	 * \param N nombre de dates de constatation
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 * \param G contient N vecteurs gaussiens centres de matrice de covariance identite
	 * \param grid contient les indices de temps utilises pour l'evolution du sous-jacent
	 */
	void asset(PnlMat *path, double T,  int N, PnlRng *rng, PnlMat* G, PnlVect* grid) ;

	/*!
	 * \brief Calcule une trajectoire du sous-jacent connaissant le passe jusqu'a la date t
	 *
	 * \param path contient une trajectoire du sous-jacent donnee jusqu'a l'instant par la matrice past
	 * \param t date jusqu'a laquelle on connait la trajectoire t n'est pas forcement une date de discretisation
	 * \param N nombre de pas de constatation
	 * \param T date jusqu'a laquelle on simule la trajectoire (maturite)
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 * \param past trajectoire realisee a la date t
	 * \param taille contient le nombre d'evolution du sous-jacent jusqu'a la date t
	 * \param G contient N-taille vecteurs gaussiens centrés de matrice de covariance identite
	 * \param grid contient les indices de temps utilises pour l'evolution du sous-jacent
	 */
	void asset(PnlMat *path, double t, int N, double T, PnlRng *rng, const PnlVect *pastT, int taille, PnlMat* G, PnlVect* grid);

	/*!
	 * \brief Shift d’une trajectoire du sous-jacent
	 *
	 * \param path (input) contient en input la trajectoire du sous-jacent
	 * \param shift_path (output) contient la trajectoire path dont la composante d a ete shiftee par (1+h) a partir de la date t.
	 * \param t (input) date a partir de laquelle on shift
	 * \param h (input) pas de differences finies
	 * \param d (input) indice du sous-jacent à shifter
	 * \param timestep (input) pas de constatation du sous-jacent
	 */
	void shift_asset (PnlMat *_shift_path, const PnlMat *path,
		int d, double h, double t, double timestep);

	/*!
	 *
	 * \brief Simulation du marche
	 *
	 * \param past (output) trajectoire du sous-jacent sous la probabilite historique
	 * \param H (input) nombre de date
	 * \param T (input) date jusqu'a laquelle on simule la trajectoire (maturite)
	 * \param PL (output) erreur de couverture
	 */
	void simul_market (PnlMat* past, int H, double T, PnlRng *rng); 
};
#endif
