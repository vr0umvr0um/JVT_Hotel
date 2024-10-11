#ifndef CHAMBRE_H
#define CHAMBRE_H

#include <hotel.h>

using namespace std;

// ------------------------------

/**
 * @brief class Chambre
 * Cette classe va représenter une chambre d'un hotel
 * Auteur : Forest Jules
 */
class Chambre{
    private:
        int numChambre;
        int prix;
        int nbCouchages;
        Hotel hotel;
    public:
        Chambre(int numChambre, int prix, int nbCouchages, Hotel hotel);
        Chambre();
        ~Chambre();

    // ------------- Getters et setters ------------

    /**
     * @brief getNumChambre
     * @return int - numéro de chambre de la chambre
     */
    int getNumChambre();

    /**
     * @brief getPrix
     * @return int - prix de la chambre pour une nuit
     */
    int getPrix();

    /**
     * @brief getNbCouchages
     * @return int - nombre de couchages dans la chambre
     */
    int getNbCouchages();

    /**
     * @brief getHotel
     * @return Hotel - hotel dans lequel se trouve la chambre
     */
    Hotel getHotel();

    /**
     * @brief setNumChambre - modifie le numéro de chambre avec celui en paramètre
     * @param num
     */
    void setNumChambre(int num);

    // --------------- fonctions usuelles -----------
    /**
     * @brief afficheChambre - affiche en console les détails de la chambre
     */
    void afficheChambre();

    /**
     * @brief detailsChambre
     * @return string - renvoie sous forme de string les détails de la chambre
     */
    string detailsChambre();
};

#endif // CHAMBRE_H
