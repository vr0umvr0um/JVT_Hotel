/**
 * @author Forest Jules
 */

#include "chambre.h"
#include <iostream>

// ---------------------- Constructeurs et destructeur ---------------------

Chambre::Chambre(int numChambre, int prix, int nbCouchages, Hotel hotel) : numChambre(numChambre), prix(prix), nbCouchages(nbCouchages), hotel(hotel){}

Chambre::Chambre() : numChambre(-1), prix(-1), nbCouchages(-1), hotel(){}

Chambre::~Chambre(){}


// ------------- Getters et setters ------------

int Chambre::getNumChambre(){
    return this->numChambre;
}

int Chambre::getPrix(){
    return this->prix;
}

int Chambre::getNbCouchages(){
    return this->nbCouchages;
}

Hotel Chambre::getHotel(){
    return this->hotel;
}

void Chambre::setNumChambre(int num){
    this->numChambre = num;
}

// --------------- fonctions usuelles -----------

void Chambre::afficheChambre(){
    cout << "Chambre n° " << this->numChambre << " de l'hotel " << this->hotel.getNomHotel() << "    Prix : " << this->prix << "    Nb de couchages : " << this->nbCouchages << endl;
}

string Chambre::detailsChambre(){
    return "Chambre n° " + to_string(this->numChambre) + "de l'hotel " + this->hotel.getNomHotel() + "    Prix : " + to_string(this->prix) + "    Nb de couchages : " + to_string(this->nbCouchages) + "\n";
}
