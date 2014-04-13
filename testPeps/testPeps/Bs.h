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
	 * \param N nombre de dates de constatation
	 * \param T  maturite
	 * \param grid contient les indices de temps utilises pour l'evolution du sous-jacent
	 * \param path contient une trajectoire du modele. C’est une matrice de dimension d x (N+1)
	 * \param G contient N vecteurs gaussiens centres de matrice de covariance identite
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 */
	void asset(int N, double T, PnlVect* grid, PnlMat *path, PnlMat *G, PnlRng *rng);

	/*!
	 * \brief Calcule une trajectoire du sous-jacent connaissant le passe jusqu'a la date t
	 *
	 * \param N nombre de pas de constatation
	 * \param taille contient le nombre d'evolution du sous-jacent jusqu'a la date t
	 * \param T date jusqu'a laquelle on simule la trajectoire (maturite)
	 * \param t date jusqu'a laquelle on connait la trajectoire t n'est pas forcement une 		 * \param pastT trajectoire realisee a la date t
	 * \param grid contient les indices de temps utilises pour l'evolution du sous-jacent
	 * \param path contient une trajectoire du sous-jacent donnee jusqu'a l'instant par la matrice past
date de discretisation
	 * \param G contient N-taille vecteurs gaussiens centrés de matrice de covariance identite
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 */
	void asset(int N, int taille, double T, double t, const PnlVect* pastT, const PnlVect* grid, PnlMat* path, PnlMat* G, PnlRng *rng);

	/*!
	 * \brief Shift d’une trajectoire du sous-jacent
	 *
	 * \param d (input) indice du sous-jacent à shifter
	 * \param indice (intput) indice dans path à partir duquel il faut shifter
	 * \param h (input) pas de differences finies
	 * \param shift_path (output) contient la trajectoire path dont la composante d a ete shiftee par (1+h) a partir de la date t.
	 * \param path (input) contient en input la trajectoire du sous-jacent
	 */
	void shift_asset(int d, int indice, double h, PnlMat* shift_path, const PnlMat* path);

	/*!
	 *
	 * \brief Simulation du marche
	 *
	 * \param H (input) nombre de date
	 * \param T (input) date jusqu'a laquelle on simule la trajectoire (maturite)
	 * \param past (output) trajectoire du sous-jacent sous la probabilite historique
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 */
	void simul_market (int H, double T, PnlMat* past, PnlRng* rng); 
};
#endif
