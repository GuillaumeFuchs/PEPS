#include "Option.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef PerformanceH
#define PerformanceH

/*!
 *  \file	performance.h
 *  \brief	Header de la classe fille d'Option: performance
 *  \author Equipe 11
 */

/*!
 * \class Performance
 * \brief Classe representant l'option performance
 */
class Performance : public Option {

  private:
	

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe performance
	 */
	Performance();
	Performance( double T, int timeStep, int size, double r, double* coeff);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe performance
	 */
	~ Performance();

	/*!
	 * \brief Payoff option performance
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
