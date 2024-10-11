#ifndef HOTEL_H
#define HOTEL_H

#include "adresse.h"

using namespace std;

// ---------------------------------

/**
 * @brief la classe Hotel
 * Cette classe représente un hotel
 * Auteur : Forest Jules
 */
class Hotel{
private:
    int idHotel;
    string nomHotel;
    int nbChambres;
    Adresse adresse;

public:
    Hotel();
    Hotel(int idHotel, string nomHotel, int nbChambres, Adresse adresse);
    ~Hotel();

    // ----------- Getters et Setters ----------

    /**
     * @brief getIdHotel
     * @return int - id de l'hotel
     */
    int getIdHotel();

    /**
     * @brief getNomHotel
     * @return string - nom de l'hotel
     */
    string getNomHotel();

    /**
     * @brief getNbChambres
     * @return int - nombre de chambres das l'hotel
     */
    int getNbChambres();

    /**
     * @brief getAdresse
     * @return Adresse - adresse de l'hotel
     */
    Adresse getAdresse();

    /**
     * @brief setIdHotel - modifie l'id de l'hotel par le'id en paramètre
     * @param id
     */
    void setIdHotel(int id);



    // --------- Fonctions usuelles -----------

    /**
     * @brief rechercherChambre
     * Méthode permettant de rechercher des chambres
     * disponibles dans l'hôtel
     */
    void rechercherChambre();

    /**
     * @brief ajouterReservation
     * Méthode permettant d'ajouter une réservation
     * pour une chambre de l'hôtel.
     */
    void ajouterReservation();

    /**
     * @brief annulerReservation
     *  Méthode permettant d'annuler une réservation
     *  existante pour une chambre de l'hôtel.
     */
    void annulerReservation();

    /**
     * @brief afficherDetails - affiche les details de l'hotel en console
     */
    void afficherDetails();

    /**
     * @brief detailsHotel
     * @return string - details de l'hotel sous forme de string
     */
    string detailsHotel();
};

#endif // HOTEL_H
