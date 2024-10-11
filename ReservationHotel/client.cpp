/**
 * @author Vanessa Antivackis
 */

#include "client.h"
#include <iostream>

// ----------- Constructeurs et Déstructeur ----------

Client::Client(int idClient, string nomClient, string prenomClient, string telephone, string mailClient, string mdpClient, Adresse adresse)
    : idClient(idClient), nomClient(nomClient), prenomClient(prenomClient), telephone(telephone), mailClient(mailClient), mdpClient(mdpClient), adresse(adresse){}

Client::Client()
    : idClient(-1), nomClient("NULL"), prenomClient("NULL"), telephone("NULL"), mailClient("NULL"), mdpClient("NULL"){}

Client::~Client(){

}

// ----------- Getters et Setters ----------

int Client::getIdClient(){
    return this->idClient;
}

void Client::setIdClient(int idC){
    idClient=idC;
}

string Client::getNomClient(){
    return this->nomClient;
}

void Client::setNomClient(string nomC){
    nomClient=nomC;
}

string Client::getPrenomClient(){
    return this->prenomClient;
}

void Client::setPrenomClient(string prenomC){
    prenomClient=prenomC;
}

string Client::getTelephoneClient(){
    return this->telephone;
}

void Client::setTelephoneClient(string telephoneC){
    telephone=telephoneC;
}

string Client::getMailClient(){
    return this->mailClient;
}

void Client::setMailClient(string mailC){
    mailClient=mailC;
}

string Client::getMdpClient(){
    return this->mdpClient;
}

void Client::setMdpClient(string mdpC){
    mdpClient=mdpC;
}

Adresse Client::getAdresse(){
    return this->adresse;
}

// --------- Fonctions usuelles -----------

void Client::afficherDetails(){
    cout << "Le client " << getPrenomClient() << " " << getNomClient() << ", d'identifiant " << getIdClient() << ", a pour numero de telephone " << getTelephoneClient() << " et pour adresse mail " << getMailClient() << "." << endl;
    cout << "Son mot de passe est " << getMdpClient() << "." << endl;
    cout << "L'adresse du client est " << this->adresse.detailsAdresse()<< endl;
    cout << "L'identifiant de l'adresse est " << this->adresse.getIdAdresse() << endl;
};
