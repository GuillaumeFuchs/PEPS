#ifndef MonteCarloH
#define MonteCarloH
#include "Montecarlos.h"

/*!
 *  \file	montecarlo.h
 *  \brief	Header de la classe MonteCarlo
 *  \author Equipe 11
 */

/*!
 * \class MonteCarlo
 * \brief Classe representant le pricer Monte Carlo
 */

class MonteCarlo : public MonteCarlos {
  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe montecarlo
	 * \param rng: generateur aleatoire
	 */
	MonteCarlo(PnlRng *rng);

	/*!
	 * \brief Constructeur avec argument
	 *
	 Constructeur avec argument de la classe montecarlo
	 *
	 * \param mod_: pointeur vers le modele 
	 * \param opt_: pointeur sur l'option 
	 * \param rng: pointeur sur le generateur
	 * \param h_: pas de difference finie
	 * \param samples_: nombre de tirages Monte Carlo
	 */
	MonteCarlo(ModelAsset *mod, Option *opt, PnlRng *rng, double h, int samples);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Bs
	 */
	virtual ~MonteCarlo();

	/*!
	 * \brief Calcule du prix de l’option a la date 0
	 *
	 * \param prix (ouptut) contient le prix
	 * \param ic (ouptut) contient la largeur de l’intervalle de confiance sur le calcul du prix
	 */
	void price (double &prix, double &ic);	

	/*!
	 * \brief Calcule le prix de l’option a la date t
	 *
	 * \param past (input) contient la trajectoire du sous-jacent jusqu’a l’instant t
	 * \param t (input) date a laquelle le calcul est fait
	 * \param prix (ouptut) contient le prix
	 * \param ic (ouptut) contient la largeur de l’intervalle de confiance sur le calcul du prix
	 */
	void price (const PnlMat *past, double t, double &prix, double &ic);

	/*!
	 * \brief Calcul du delta de l’option a la date t
	 *
	 * \param past (input) contient la trajectoire du sous-jacent jusqu’a l’instant t
	 * \param t (input) date a laquelle le calcul est fait
	 * \param delta (ouptut) contient le vecteur de delta
	 * \param ic (ouptut) contient la largeur de l’intervalle de confiance sur le calcul du delta
	 */
	void delta (const PnlMat *past, double t, PnlVect *delta, PnlVect *ic); 

	/*!
	 * \brief Calcul de l'erreur de couverture
	 *
	 * \param past contient une trajectoire du modele 
	 * \param pl erreur de courverture du portefeuille
	 * \param H nombre de date dans la simulation
	 * \param T maturite du portefeuille
	 */
	void couv (PnlMat *past, double &pl, double &plTheorique, int H, double T);

};
#endif
