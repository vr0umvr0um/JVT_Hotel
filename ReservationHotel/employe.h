/**
 * @author Haton Tom
 */
#ifndef EMPLOYE_H
#define EMPLOYE_H

#include "hotel.h"

#include <string>

using namespace std;

/**
 * @brief la classe Employe
 * Cette classe représente un Employe
 */
class Employe
{
private:
    int numEmploye;
    string poste;
    string nom;
    string prenom;
    string mdpEmploye;
    bool estResponsable;
    string mailEmploye;
    Hotel hotel;

public:
    //On pourrait s'éviter l'utilisation de 2 constructeurs (1 avec / sans paramètres) via les valeurs de base. Ex :
    //Employe(string nom="", string prenom="", string numEmploye="", string poste="");
    /**
         * @brief Employe
         */
    Employe();
    Employe(int numEmploye, string poste, string nom, string prenom, string mdpEmploye, bool estResponsable, string mailEmploye, Hotel hotel);
    ~Employe();

    // ----------- Getters et Setters ----------
    string getNom();
    string getPrenom();
    int getNumEmploye();
    void setNumEmploye(int numEmploye);
    string getPoste();
    bool getEstResponsable();
    string getMailEmploye();
    string getMdpEmploye();
    Hotel getHotel();

    // --------- Fonctions usuelles -----------

    /**
     * @brief gererReservation
     * Méthode permettant à l'employé de gérer les réservations du client
     */
    void gererReservation();

    /**
     * @brief verifierReservation
     * @return un booleen
     * Méthode permettant à l'employé de vérifier la disponibilité des chambres dans l'hôtel
     */
    bool verifierReservation();

    /**
     * @brief afficherDetails
     * Méthode permettant d'afficher les détails de l'employé
     */
    void afficherDetails();

};

#endif // EMPLOYE_H
