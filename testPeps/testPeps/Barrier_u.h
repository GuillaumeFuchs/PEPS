#include "Option.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef barrier_ulH
#define barrier_ulH

/*!
 *  \file	barrier_u.h
 *  \brief	Header de la classe fille d'Option: barrier_u
 *  \author Equipe 11
 */

/*!
 * \class Barrier_u
 * \brief Classe representant l'option barriere haute
 */
class Barrier_u : public Option {

  private:
	double strike_; /*!< strike du sous-jacent */
	PnlVect *Bu_; /*!< barriere haute */

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe barrier_u
	 */
	Barrier_u();
	Barrier_u(double strike, double *bu, double T, int timeStep, int size, double r, double* coeff);
	
	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe barrier_u
	 */
	virtual ~Barrier_u();

	/*!
	 * \brief Accesseur de strike_
	 *
	 *  Acceder au strike du sous-jacent
	 *
	 * \return le strike du sous-jacent 
	 */
	double get_Strike() const;

	/*!
	 * \brief Accesseur de Bu_
	 *
	 *  Acceder au vecteur de la barriere haute basse du sous-jacent
	 *
	 * \return le vecteur de la barriere haute basse du sous-jacent
	 */
	PnlVect* get_Bu() const;

	/*!
	 * \brief Mutateur de strike_
	 *
	 * Modifie la valeur du strike du sous-jacent
	 *
	 * \param Strike: nouveau strike
	 */
	void set_Strike(double Strike);

	/*!
	 * \brief Mutateur de Bu_
	 *
	 * Modifie la vecteur de la barriere haute basse du sous-jacent
	 *
	 * \param Bu: nouveau vecteur de la barriere haute basse du sous-jacent
	 */
	void set_Bu(PnlVect *Bl);

	/*!
	 * \brief Payoff option barriere haute
	 *
	 * Calcul la valeur du payoff du sous-jacent asiatique sur la trajectoire passee en parametre
	 *
	 * \param path: matrice de taille d x (N+1) contenant une trajectoire du modele telle que creee par la fonction asset
	 * \param t: temps o� l'option est pricer
	 *
	 * \return payoff du sous-jacent asiatique
	 */
	double payoff (const PnlMat *path, double t) const;
};
#endif
