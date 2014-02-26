#include "Option.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef BasketH
#define BasketH
/*!
 * \class Basket
 * \brief Classe representant l'option panier
 */
class Basket : public Option {

  private:
	double strike_; /*! strike de l'option */ 

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe Basket
	 */
	Basket();
	Basket(double strike, double T, int timeStep, int size, double* coeff);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Basket
	 */
	virtual ~Basket();

	/*!
	 * \brief Accesseur de strike_
	 *
	 *  Acceder au strike de l'option
	 *
	 * \return le strike de l'option 
	 */
	double get_Strike() const;

	/*!
	 * \brief Mutateur de strike_
	 *
	 * Modifie la valeur du strike de l'option
	 *
	 * \param Strike: nouveau strike
	 */
	void set_Strike(double strike);

	/*!
	 * \brief Payoff option panier
	 *
	 * Calcul la valeur du payoff de l'option panier sur la trajectoire passee en parametre
	 *
	 * \param path: matrice de taille d x (N+1) contenant une trajectoire du modele telle que creee par la fonction asset
	 * \return payoff de l'option panier
	 */
	double payoff (const PnlMat * path) const;
}; 
#endif 