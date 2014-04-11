#ifndef TestH
#define TestH
#include "Montecarlos.h"

/*!
 * \class Test
 * \brief Classe utilis�e pour tester le moteur de calcul
 */
class Test {
  private:
	MonteCarlos *mc_; /*!< pointeur vers le modele de monte-carlo */

  public:
	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe test
	 */
	Test();
	Test(MonteCarlos *mc);
	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe test
	 */
	virtual ~Test();

	/*!
	* \brief Accesseur de mc_
	*
	*  Acceder au modele du monte-carlo
	*
	*  \return le modele du monte-carlo
	*/
	MonteCarlos* get_mc() const;

	/*!
	* \brief Test des valeurs de prix pour un call
	*
	* samples: nombre de prix calcul�
	* display: booleen pour savoir si les prix sont affich�s � l'�cran ou non
	* output: bool pour savoir si les prix sont stock�s dans un fichier price_simul.txt et price_theo.txt et les temps o� les prix sont calcul�s dans price_time.txt 
	*/
	void compute_price_samples(int samples, bool display, bool output, PnlMat* past);

	/*!
	* \brief Test des valeurs du delta pour un call
	*
	* samples: nombre de prix calcul�
	* display: booleen pour savoir si les prix sont affich�s � l'�cran ou non
	* spread: ecart � tester entre le prix th�orique et le prix calcul�
	* output: bool pour savoir si les prix sont stock�s dans un fichier delta_simul.txt et delta_theo.txt et les temps o� les prix sont calcul�s dans delta_time.txt
	*/
	void compute_delta_samples(int samples, bool display, bool output, PnlMat* past);

	/*!
	* \brief Calcul du prix de l'option � une date t donn�e
	*
	* H: nombre de pas dans la matrice de simulation de marche jusqu'� la date t
	* t: date de calcul
	*/
	void compute_price(int H, double t);
	
	/*!
	* \brief Calcul du delta de l'option � une date t donn�e
	*
	* H: nombre de pas dans la matrice de simulation de marche jusqu'� la date t
	* t: date de calcul
	*/
	void compute_delta(int H, double t);

	/*!
	* \brief Calcul du portefeuille de couverture sur la duree de vie de l'option
	*
	* H: nombre de pas dans la matrice de simulation de marche jusqu'� la date t
	* output: si vrai alors display les r�sultat de 500 couverture dans couv_simulation.txt (couverture simulee) et dans couv_theorique (couverture calculee avec BS)
	*/
	void compute_couv(int H, bool output);

	void compute_hedge(int H);

	/*!
	* \brief Calcul la valeur theorique d'un call selon la formule d'�valution de B&S
	*/
	static double theo_price(double S, double K, double r, double T, double sigma);

	/*!
	* \brief Calcul la valeur theorique du delta d'un call selon la formule d'�valution de B&S
	*/
	static double theo_delta(double S, double K, double r, double T, double sigma);

};
#endif