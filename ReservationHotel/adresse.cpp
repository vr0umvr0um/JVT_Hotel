/**
 * @author Forest Jules
 */

#include "adresse.h"

#include <iostream>

// ------------- Constructeurs et destructeur -------------------

Adresse::Adresse() : idAdresse(-1), numero(-1), rue("Null"), ville("Null"), codePostal(-1), pays("Null") {}

Adresse::Adresse(int idAdresse, int numero, string rue, string ville, int codePostal, string pays)
    : idAdresse(idAdresse), numero(numero), rue(rue), ville(ville), codePostal(codePostal), pays(pays){}

Adresse::~Adresse(){}


// ------------ Getters et Setters -------------

int Adresse::getIdAdresse(){
    return this->idAdresse;
}

string Adresse::getRue(){
    return this->rue;
}

int Adresse::getNumero(){
    return this->numero;
}
string Adresse::getVille(){
    return this->ville;
}

int Adresse::getCodePostal(){
    return this->codePostal;
}

string Adresse::getPays(){
    return this->pays;
}

void Adresse::setId(int id){
    this->idAdresse = id;
}

// ----------- Fonctions usuelles ------------

void Adresse::afficheAdresse(){
    cout << this->numero << " " << this->rue << ", " << this->codePostal << " " << this->ville << " " << this->pays << endl;
}

string Adresse::detailsAdresse(){
    return to_string(this->numero) + " " + this->rue + ", " + to_string(this->codePostal) + " " + this->ville + " " + this->pays +"\n";
}
