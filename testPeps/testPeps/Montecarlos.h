#ifndef MontecarlosH
#define MontecarlosH
#include "Modelasset.h"
#include "Option.h"
#include <pnl/pnl_random.h>

/*!
*  \file	Montecarlos.h
*  \brief	Classe repr�sentant la classe mere de tous les types de simulation de MC
*/

class MonteCarlos {
protected:
	ModelAsset *mod_; /*!< pointeur vers le modele */
	Option *opt_; /*!< pointeur sur l�option */
	PnlRng *rng; /*!< pointeur sur le generateur */
	double h_; /*!< pas de difference finie */
	int samples_; /*!< nombre de tirages Monte Carlo */

public:

	/*!
	* \brief Constructeur par defaut
	*
	* Constructeur par defaut de la classe MonteCarlos
	* \param rng: generateur aleatoire
	*/
	MonteCarlos(PnlRng *rng);


	/*!
	* \brief Constructeur avec arguments
	*
	Constructeur avec arguments de la classe MonteCarlos
	*
	* \param mod_: pointeur vers le modele 
	* \param opt_: pointeur sur l'option 
	* \param rng: pointeur sur le generateur
	* \param h_: pas de difference finie
	* \param samples_: nombre de tirages Monte Carlo
	*/
	MonteCarlos(ModelAsset *mod, Option *opt, PnlRng *rng, double h, int samples);

	/*!
	* \brief Destructeur
	*
	* Destructeur de la classe MonteCarlos
	*/
	virtual ~MonteCarlos();

	/*!
	* \brief Accesseur de mod_
	*
	*  Acceder au modele du sous-jacent
	*
	*  \return le modele du sous-jacent
	*/
	ModelAsset* get_mod() const;

	/*!
	* \brief Accesseur de opt_
	*
	*  Acceder � l'option
	*
	* \return l'option
	*/
	Option* get_opt() const;

	/*!
	* \brief Accesseur de rng_
	*
	*  Acceder au generateur
	*
	* \return le generateur
	*/
	PnlRng* get_rng() const;

	/*!
	* \brief Accesseur de h_
	*
	*  Acceder au pas de difference finie
	*
	* \return le pas de difference finie
	*/
	double get_h() const;

	/*!
	* \brief Accesseur de samples_
	*
	*  Acceder au nombre de tirages Monte Carlo
	*
	* \return le nombre de tirage Monte Carlo
	*/
	int get_samples() const;

	/*!
	* \brief Mutateur de mod_
	*
	*  Modifier le modele
	*
	* \param le nouveau modele
	*/
	void set_mod(ModelAsset* mod);

	/*!
	* \brief Mutateur de opt_
	*
	*  Modifier l'option
	*
	* \param la nouvelle option
	*/
	void set_opt(Option* opt);

	/*!
	* \brief Mutateur de rng_
	*
	*  Modifier le generateur
	*
	* \param le nouveau generateur
	*/
	void set_rng(PnlRng* rng);

	/*!
	* \brief Mutateur de h_
	*
	*  Modifier le pas de difference finie
	*
	* \param le nouveau pas de difference finie
	*/
	void set_h(double h);

	/*!
	* \brief Mutateur de samples_
	*
	*  Modifier le nombre de tirages Monte Carlo
	*
	* \param le nouveau nombre de tirages Monte Carlo
	*/
	void set_samples(int samples);

	/*!
	* \brief Calcule du prix de l�option a la date 0
	*
	* \param prix (ouptut) contient le prix
	* \param ic (ouptut) contient la largeur de l�intervalle de confiance sur le calcul du prix
	*/
	virtual void price (double &prix, double &ic) = 0;	

	/*!
	* \brief Calcule le prix de l�option a la date t
	*
	* \param past (input) contient la trajectoire du sous-jacent jusqu�a l�instant t
	* \param t (input) date a laquelle le calcul est fait
	* \param prix (ouptut) contient le prix
	* \param ic (ouptut) contient la largeur de l�intervalle de confiance sur le calcul du prix
	*/
	virtual void price (const PnlMat *past, double t, double &prix, double &ic) = 0;

	/*!
	* \brief Calcul du delta de l�option a la date t
	*
	* \param past (input) contient la trajectoire du sous-jacent jusqu�a l�instant t
	* \param t (input) date a laquelle le calcul est fait
	* \param delta (ouptut) contient le vecteur de delta
	* \param ic (ouptut) contient la largeur de l�intervalle de confiance sur le calcul du delta
	*/
	virtual void delta (const PnlMat *past, double t, PnlVect *delta, PnlVect *ic) = 0; 

	/*!
	* \brief Calcul de l'erreur de couverture
	*
	* \param past contient une trajectoire du modele 
	* \param pl erreur de courverture du portefeuille
	* \param H nombre de date dans la simulation
	* \param T maturite du portefeuille
	 * \param summary contient les informations li�s � l'achat & � la vente d'actions pour le portefeuille de couverture
	 *	1er colonne: date de recalibrage
	 *	2e  colonne: cours de l'action
	 *	3e  colonne: delta simul�
	 *	4e	colonne: nombre d'actions � acheter (si n�gatif alors vente)
	 *	5e	colonne: delta th�orique selon B&S
	 *	6e	colonne: nb d'actions � acheter th�orique
	*/
	virtual void couv (PnlMat *past, double &pl, double &plTheo, int H, double T, PnlMat* summarySimul, PnlMat* summaryTheo) = 0;

};
#endif