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

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe Playlist
	 */
	Playlist();
	Playlist(double T, int timeStep, int size, double r, double* coeff);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Playlist
	 */
	virtual ~Playlist();

	/*!
	 * \brief Payoff option panier
	 *
	 * Calcul la valeur du payoff du sous-jacent asiatique sur la trajectoire passee en parametre
	 *
	 * \param path: matrice de taille d x (N+1) contenant une trajectoire du modele telle que creee par la fonction asset
	 * \param t: temps où l'option est pricer
	 *
	 * \return payoff du sous-jacent asiatique
	 */
	double payoff (double t, const PnlMat* path) const;
}; 

#endif 

