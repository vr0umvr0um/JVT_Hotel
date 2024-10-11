#include "reservation.h"
#include <iostream>

// -------------------- Constructeurs et destructeur ---------------

Reservation::Reservation(int idReservation, string dateArrive, string dateDepart, int estValide, int estTraite, Chambre chambre, Client client)
    : idReservation(idReservation), dateArrive(dateArrive), dateDepart(dateDepart), estValide(estValide), estTraite(estTraite), chambre(chambre), client(client){}

Reservation::Reservation() : idReservation(-1), dateArrive("NULL"), dateDepart("NULL"), chambre(), client(){}

Reservation::~Reservation(){}


// --------------- getters et setters ------------
int Reservation::getIdReservation(){
    return this->idReservation;
}

string Reservation::getDateArrive(){
    return this->dateArrive;
}

string Reservation::getDateDepart(){
    return this->dateDepart;
}

int Reservation::getEstValide(){
    return this->estValide;
}

int Reservation::getEstTraite(){
    return this->estTraite;
}

Chambre Reservation::getChambre(){
    return this->chambre;
}

Client Reservation::getClient(){
    return this->client;
}

void Reservation::setIdReservation(int id){
    this->idReservation = id;
}

void Reservation::setDateArrive(string date){
    this->dateArrive = date;
}

void Reservation::setDateDepart(string date){
    this->dateDepart = date;
}

void Reservation::setEstValide(int val){
    this->estValide = val;
}

void Reservation::setEstTraite(int val){
    this->estTraite = val;
}

// ----------- fonctions usuelles -----------

void Reservation::afficherReservation(){
    cout << "Numero de reservation : "  << this->getIdReservation() << "    Sejour du " << this->getDateArrive() << " au " << this->getDateDepart() << " à l'hotel "
         << this->getChambre().getHotel().getNomHotel() << " pour le client "
         << this->client.getNomClient() << " " << this->getClient().getPrenomClient() << endl;
}

string Reservation::getDetails() {
    return "Numero de reservation : " + to_string(this->getIdReservation()) + "Sejour du " + this->getDateArrive() + " au " + this->getDateDepart() + " à l'hotel "
           + this->getChambre().getHotel().getNomHotel() + " pour le client "
           + this->client.getNomClient() + " " + this->getClient().getPrenomClient() + "\n";
}
