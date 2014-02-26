#include "Option.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef PlaylistH
#define PlaylistH
/*!
 * \class Playlist
 * \brief Classe representant l'option panier
 */
class Playlist : public Option {

  private:
	double strike_; /*! strike de l'option */ 
	double r_;

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe Playlist
	 */
	Playlist();
	Playlist(double strike, double T, int timeStep, int size, double r, double* coeff);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Playlist
	 */
	virtual ~Playlist();

	/*!
	 * \brief Accesseur de strike_
	 *
	 *  Acceder au strike de l'option
	 *
	 * \return le strike de l'option 
	 */
	double get_Strike() const;
	
	double get_r() const;

	/*!
	 * \brief Mutateur de strike_
	 *
	 * Modifie la valeur du strike de l'option
	 *
	 * \param Strike: nouveau strike
	 */
	void set_Strike(double strike);

	void set_r(double r);
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

