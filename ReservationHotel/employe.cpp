/**
 * @author Haton Tom
 */

#include "employe.h"
#include <iostream>

/**
 * @brief Employe::Employe
 * @param numEmploye
 * @param poste
 * @param nom
 * @param prenom
 * @param estResponsable
 * @param mailEmploye
 */
Employe::Employe(int numEmploye, string poste, string nom, string prenom, string mdpEmploye, bool estResponsable, string mailEmploye, Hotel hotel)
    : numEmploye(numEmploye), poste(poste), nom(nom), prenom(prenom), mdpEmploye(mdpEmploye), estResponsable(estResponsable), mailEmploye(mailEmploye), hotel(hotel) {}

Employe::Employe()
    : numEmploye(-1), poste("None"), nom("None"), prenom("None"), mdpEmploye("None"), estResponsable(false), mailEmploye("None") {}

Employe::~Employe(){

}
string Employe::getNom(){
    return this->nom;
}
string Employe::getPrenom(){
    return this->prenom;
}
int Employe::getNumEmploye(){
    return this->numEmploye;
}
void Employe::setNumEmploye(int numEmpl){
    this->numEmploye = numEmpl;
}
string Employe::getPoste(){
    return this->poste;
}
bool Employe::getEstResponsable(){
    return this->estResponsable;
}
string Employe::getMailEmploye(){
    return this->mailEmploye;
}
string Employe::getMdpEmploye(){
    return this->mdpEmploye;
}
Hotel Employe::getHotel(){
    return this->hotel;
}
/*Méthode permettant à l'employé de gérer les réservations du client*/
void Employe::gererReservation(){

}
/*Méthode permettant à l'employé de vérifier la disponibilité des chambres dans l'hôtel*/
bool Employe::verifierReservation(){
    return true;
}
/*Méthode permettant d'afficher les détails de l'employé*/
void Employe::afficherDetails(){
    cout << "Nom : " << this->getNom() << ", Prénom : " << this->getPrenom() << ", N° Employé : " << this->getNumEmploye()
         << ", Poste : " << this->getPoste() << ", estResponsable : " << this->getEstResponsable() << ", mailEmploye : "
         << this->getMailEmploye() << ", MDP : " << this->getMdpEmploye() << ", Hotel : " << this->getHotel().detailsHotel() << endl;
}
