#include "Option.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef barrier_llH
#define barrier_llH

/*!
 *  \file	barrier_l.h
 *  \brief	Header de la classe fille d'Option: barrier_l
 *  \author Equipe 11
 */

/*!
 * \class Barrier_l
 * \brief Classe representant l'option barriere
 */
class Barrier_l : public Option {

  private:
	double strike_; /*!< strike du sous-jacent */
	PnlVect *Bl_; /*!< barriere basse */

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe barrier_l
	 */
	Barrier_l();
	Barrier_l(double strike, double* bl, double T, int timeStep, int size, double r, double* coeff);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe barrier_l
	 */
	virtual ~Barrier_l();

	/*!
	 * \brief Accesseur de strike_
	 *
	 *  Acceder au strike du sous-jacent
	 *
	 * \return le strike du sous-jacent 
	 */
	double get_Strike() const;

	/*!
	 * \brief Accesseur de Bl_
	 *
	 *  Acceder au vecteur de la barriere basse du sous-jacent
	 *
	 * \return le vecteur de la barriere basse du sous-jacent
	 */
	PnlVect* get_Bl() const;

	/*!
	 * \brief Mutateur de strike_
	 *
	 * Modifie la valeur du strike du sous-jacent
	 *
	 * \param Strike: nouveau strike
	 */
	void set_Strike(double Strike);

	/*!
	 * \brief Mutateur de Bl_
	 *
	 * Modifie la vecteur de la barriere basse du sous-jacent
	 *
	 * \param Bl: nouveau vecteur de la barriere basse du sous-jacent
	 */
	void set_Bl(PnlVect *Bl);

	/*!
	 * \brief Payoff option barriere
	 *
	 * Calcul la valeur du payoff du sous-jacent asiatique sur la trajectoire passee en parametre
	 *
	 * \param path: matrice de taille d x (N+1) contenant une trajectoire du modele telle que creee par la fonction asset
	 * \param t: temps où l'option est pricer
	 *
	 * \return payoff du sous-jacent asiatique
	 */
	double payoff (const PnlMat *path, double t) const;
};
#endif
