#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef OptionH
#define OptionH
/*!
* \class option
* \brief Classe representant la classe mere de tous les types d'options: Option
*/
class Option {

protected: 
	double T_; /*!< maturite */
	int timeStep_; /*!< nombre de pas de temps de discretisation */
	int size_; /*!< dimension du modele, redondant avec option::size_ */
	double r_; /*!< taux sans risque */
	PnlVect *Coeff_; /*!< payoff coefficients */


public:

	/*!
	* \brief Constructeur par defaut
	*
	* Constructeur par defaut de la classe option
	*/
	Option();
	Option(double T, int timeStep, int size, double r, double* coeff);


	/*!
	* \brief Destructeur
	*
	* Destructeur de la classe option
	*/
	virtual ~Option();

	/*!
	* \brief Accesseur de T_
	*
	*  Acceder à la maturite du sous-jacent
	*
	* \return la maturite du sous-jacent
	*/
	double get_T() const;

	/*!
	* \brief Accesseur de timeStep_
	*
	*  Acceder au nombre de pas de temps de discretisation
	*
	*  \return le nombre de pas de temps de discretisation
	*/
	int get_timeStep() const;

	/*!
	* \brief Accesseur de size_
	*
	*  Acceder a la taille du sous-jacent
	*
	* \return la taille du sous-jacent
	*/
	int get_size() const; 

	/*!
	* \brief Accesseur de r_
	*
	*  Acceder au taux sans risque
	*
	* \return le taux sans risque
	*/
	int get_r() const; 

	/*!
	 * \brief Accesseur de Coeff_
	 *
	 *  Acceder au vecteur des coefficients des payoff de l'option
	 *
	 * \return le vecteur des coefficients des payoff
	 */
	PnlVect * get_Coeff() const;

	/*!
	* \brief Mutateur de T_
	*
	*  Modifier la maturite du sous-jacent
	*
	* \param la nouvelle maturite du sous-jacent
	*/
	void set_T(double T);

	/*!
	* \brief Mutateur de timeStep_
	*
	*  Modifier le nombre de pas de temps de discretisation 
	*
	* \param le nouveau nombre de pas de temps de discretisation
	*/
	void set_timeStep(int timeStep);

	/*!
	* \brief Mutateur de size_
	*
	*  Modifier a la taille du sous-jacent
	*
	* \param la nouvelle taille du sous-jacent
	*/
	void set_size(int size);
	
	/*!
	* \brief Mutateur de r_
	*
	*  Modifier le taux sans risque
	*
	* \param le nouveau taux sans risque
	*/
	void set_r(int r);
	
	/*!
	 * \brief Mutateur de Coeff_
	 *
	 * Modifie le vecteur des coefficients des payoff de l'option 
	 *
	 * \param Coeff: nouveau vecteur des coefficients des payoff
	 */
	void set_Coeff(PnlVect *Coeff);


	/*!
	* \brief Calcule la valeur du payoff sur la trajectoire passee en parametre
	 *
	 * Calcul la valeur du payoff du sous-jacent asiatique sur la trajectoire passee en parametre
	 *
	 * \param path: matrice de taille d x (N+1) contenant une trajectoire du modele telle que creee par la fonction asset
	 * \param t: temps où l'option est pricer
	 *
	 * \return payoff du sous-jacent asiatique
	 */
	virtual double payoff (const PnlMat *path, double t) const = 0;
};
#endif 
