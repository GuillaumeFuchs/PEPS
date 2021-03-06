#ifndef ModelassetH
#define ModelassetH
#include <pnl/pnl_vector.h>
#include <pnl/pnl_random.h>

/*!
 * \class ModelAsset
 * \brief Classe representant la classe mere de tous les mod�les de simulation de sous-jacent
 */
class ModelAsset {
  protected:
	int size_; /*!< nombre d�actifs du modele */
	double r_; /*!< taux d�interet */
	double* rho_; /*!< parametre de correlation */
	PnlVect *sigma_; /*!< vecteur de volatilites */
	PnlVect *spot_; /*!< valeurs initiales du sous-jacent */
	PnlVect *trend_; /*!< taux utilise sous la probabilite historique */
	PnlMat *Cho_; /*!< Matrice de Cholesky utilise pour la correlation*/
	PnlVect *Gi_; /*!< Vecteur gaussien centr� du modele de Bs multidimensionnel*/
	PnlVect *Ld_; /*!< Ligne d de la matrice de Cholesky Cho_*/

  public:
	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe modelasset
	 */
	ModelAsset();
	ModelAsset(int size, double r, double* rho, double* sigma, double* spot, double* trend);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe modelasset
	 */
	virtual ~ModelAsset();

	/*!
	 * \brief Accesseur de size_
	 *
	 *  Acceder � la taille du sous-jacent
	 *
	 * \return la taille du sous-jacent
	 */
	int get_size() const;

	/*!
	 * \brief Accesseur de r_
	 *
	 *  Acceder au taux d'interet du sous-jacent
	 *
	 * \return le taux d'interet du sous-jacent
	 */
	double get_r() const;

	/*!
	 * \brief Accesseur de rho_
	 *
	 *  Acceder au parametre de correlation du sous-jacent
	 *
	 * \return le parametre de correlation du sous-jacent 
	 */
	double* get_rho() const;
 
	/*!
	 * \brief Accesseur de Sigma_
	 *
	 *  Acceder au vecteur de volatilites
	 *
	 * \return le vecteur de volatilites
	 */
	PnlVect *get_sigma() const;

	/*!
	 * \brief Accesseur de Spot_
	 *
	 *  Acceder aux valeurs initiales du sous-jacent
	 *
	 * \return la valeurs initiales du sous-jacent
	 */
	PnlVect *get_spot() const;

	/*!
	 * \brief Accesseur de Trend_
	 *
	 *  Acceder au vecteur de taux sous la probabilite historique
	 *
	 * \return le vecteur de taux sous la probabilite historique
	 */
	PnlVect *get_trend() const;

	/*!
	 * \brief Accesseur de Cho_
	 *
	 *  Acceder a la matrice de cholesky associee a la correlation du sous-jacent
	 *
	 *  \return la matrice de cholesky associee a la correlation du sous-jacent
	 */
	PnlMat *get_cho() const;

	/*!
	 * \brief Accesseur de Gi_
	 *
	 *  Acceder au vecteur gaussien centre du modele de Bs
	 *
	 *  \return le vecteur gaussien centr� du modele de Bs
	 */
	PnlVect *get_gi() const;

	/*!
	 * \brief Accesseur de Ld_
	 *
	 *  Acceder a la ligne d de la matrice de Cholesky Cho_
	 *
	 *  \return la ligne d de la matrice de Cholesky Cho_
	 */
	PnlVect *get_ld() const;

	/*!
	 * \brief Mutateur de size_
	 *
	 *  Modifier la taille du sous-jacent
	 *
	 * \param la nouvelle taille du sous-jacent
	 */
	void set_size(int size);

	/*!
	 * \brief Mutateur de r_
	 *
	 *  Modifier le taux d'interet du sous-jacent
	 *
	 * \param le nouveau taux d'interet du sous-jacent
	 */
	void set_r(double r);

	/*!
	 * \brief Mutateur de rho_
	 *
	 *  Modifier au parametre de correlation du sous-jacent
	 *
	 * \param le nouveau parametre de correlation du sous-jacent 
	 */
	void set_rho(double* rho);

	/*!
	 * \brief Mutateur de Sigma_
	 *
	 *  Modifier au vecteur de volatilites
	 *
	 * \param le nouveau vecteur de volatilites
	 */
	void set_sigma(PnlVect *sigma);

	/*!
	 * \brief Mutateur de Spot_
	 *
	 *  Modifier aux valeurs initiales du sous-jacent
	 *
	 * \param la nouvelle valeurs initiales du sous-jacent
	 */
	void set_spot(PnlVect *spot);

	/*!
	 * \brief Mutateur de Trend_
	 *
	 *  Modifier au vecteur de taux sous la probabilite historique
	 *
	 * \param le nouveau vecteur de taux sous la probabilite historique
	 */
	void set_trend(PnlVect *trend);

	/*!
	 * \brief Mutateur de Cho_
	 *
	 *  Modifier la matrice de cholesky associee a la correlation du sous-jacent
	 *
	 *  \param la nouvelle matrice de cholesky associee a la correlation du sous-jacent
	 */
	void set_cho(PnlMat *Cho);

	/*!
	 * \brief Mutateur de Gi_
	 *
	 *  Modifier le vecteur gaussien centre du modele de Bs
	 *
	 *  \param le nouveau vecteur gaussien centre du modele de Bs
	 */
	void set_gi(PnlVect *Gi);

	/*!
	 * \brief Mutateur de Ld_
	 *
	 *  Modifier la ligne d de la matrice de Cholesky Cho_
	 *
	 *  \param la nouvelle ligne d de la matrice de Cholesky Cho_
	 */
	void set_ld(PnlVect *Ld);

	/*!
	 * \brief G�n�re une trajectoire du modele et la stocke dans path
	 *
	 * \param N nombre de dates de constatation
	 * \param T  maturite
	 * \param grid contient les indices de temps utilises pour l'evolution du sous-jacent
	 * \param path contient une trajectoire du modele. C�est une matrice de dimension d x (N+1)
	 * \param G contient N vecteurs gaussiens centres de matrice de covariance identite
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 */
	virtual void asset(int N, double T, PnlVect* grid, PnlMat *path, PnlMat *G, PnlRng *rng) = 0;

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
	 * \param G contient N-taille vecteurs gaussiens centr�s de matrice de covariance identite
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 */
	virtual void asset(int N, int taille, double T, double t, const PnlVect* pastT, const PnlVect* grid, PnlMat* path, PnlMat* G, PnlRng *rng) = 0;

	/*!
	 * \brief Shift d�une trajectoire du sous-jacent
	 *
	 * \param d (input) indice du sous-jacent � shifter
	 * \param indice (intput) indice dans path � partir duquel il faut shifter
	 * \param h (input) pas de differences finies
	 * \param shift_path (output) contient la trajectoire path dont la composante d a ete shiftee par (1+h) a partir de la date t.
	 * \param path (input) contient en input la trajectoire du sous-jacent
	 */
	virtual void shift_asset(int d, int indice, double h, PnlMat* shift_path, const PnlMat* path) = 0;

	/*!
	 *
	 * \brief Simulation du marche
	 *
	 * \param H (input) nombre de date
	 * \param T (input) date jusqu'a laquelle on simule la trajectoire (maturite)
	 * \param past (output) trajectoire du sous-jacent sous la probabilite historique
	 * \param rng pointeur sur le generateur de nombre aleatoire
	 */
	virtual void simul_market (int H, double T, PnlMat* past, PnlRng* rng) = 0; 

};
#endif