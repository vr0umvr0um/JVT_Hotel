/**
 * @author Forest Jules
 */

#include "hotel.h"

#include <iostream>

// -------------------- Constructeurs et destructeur ---------------
Hotel::Hotel(int idHotel, string nomHotel, int nbChambres, Adresse adresse)
    : idHotel(idHotel), nomHotel(nomHotel), nbChambres(nbChambres), adresse(adresse){}


Hotel::Hotel() : idHotel(-1),nomHotel("None"), nbChambres(-1){}

Hotel::~Hotel(){}


// ----------------- Getters et setters --------------

int Hotel::getIdHotel(){
    return this->idHotel;
}

string Hotel::getNomHotel(){
    return this->nomHotel;
}

int Hotel::getNbChambres(){
    return this->nbChambres;
}

Adresse Hotel::getAdresse(){
    return this->adresse;
}

void Hotel::setIdHotel(int id){
    this->idHotel = id;
}


// ----------------- Fonctions usuelles --------------

/**
 * @brief Hotel::rechercherChambre
 * Méthode permettant de rechercher des chambres
 * disponibles dans l'hôtel
*/
void Hotel::rechercherChambre(){

}

/**
 * @brief Hotel::ajouterReservation
 * Méthode permettant d'ajouter une réservation
 * pour une chambre de l'hôtel.
*/
void Hotel::ajouterReservation(){

}

/**
 * @brief Hotel::annulerReservation
 * Méthode permettant d'annuler une réservation
 * existante pour une chambre de l'hôtel.
*/
void Hotel::annulerReservation(){

}

/**
 * @brief Hotel::afficherDetails
 * Méthode permettant d'afficher les détails de l'hôtel.
 */
void Hotel::afficherDetails(){
    cout << "Nom de l'hotel : " << this->nomHotel << "    Nombre de chambres :" << this->nbChambres << "     Adresse : " << this->adresse.detailsAdresse() << endl;
}

/**
 * @brief Hotel::detailsHotel
 * @return string - chaine de cracatères du détail de l'hotel
 */
string Hotel::detailsHotel(){
    string chaine = "Nom de l'hotel : " + this->nomHotel + "    Nombre de chambres :" + to_string(this->nbChambres) + "     Adresse : " + this->adresse.detailsAdresse() + "\n";
    return chaine;
}

