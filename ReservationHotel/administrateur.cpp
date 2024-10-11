#include "administrateur.h"

#include <iostream>

using namespace std;

// -------------------- Constructeurs -----------------
Administrateur::Administrateur(int idAdmin, string mailAdmin, string mdpAdmin, string pseudoAdmin)
    : idAdmin(idAdmin), mailAdmin(mailAdmin), mdpAdmin(mdpAdmin), pseudoAdmin(pseudoAdmin){}
Administrateur::Administrateur() : idAdmin(-1), mailAdmin("None"), mdpAdmin("None"), pseudoAdmin("None") {}
Administrateur::~Administrateur(){}


// ------------------- Getters et setters ------------------

int Administrateur::getIdAdmin(){
    return this->idAdmin;
}

string Administrateur::getMailAdmin(){
    return this->mailAdmin;
}

string Administrateur::getMdpAdmin(){
    return this->mdpAdmin;
}

string Administrateur::getPseudoAdmin(){
    return this->pseudoAdmin;
}

void Administrateur::setIdAmin(int newIdAdmin){
    this->idAdmin = newIdAdmin;
}

void Administrateur::setMailAdmin(string newMailAdmin){
    this->mailAdmin = newMailAdmin;
}

void Administrateur::setMdpAdmin(string newMdpAdmin){
    this->mdpAdmin = newMdpAdmin;
}

void Administrateur::setPseudoAdmin(string newPseudoAdmin){
    this->pseudoAdmin = newPseudoAdmin;
}


// ----------- Fonctions usuelles ------------

/**
         * @brief afficheAdministrateur - affiche en console les détails de l'administrateur
         */
void Administrateur::afficheAdministrateur(){
    cout << "Id admin : " << this->idAdmin << "    Mail admin : " << this->mailAdmin << "   Pseudo admin : " << this->pseudoAdmin << endl;
}

/**
         * @brief returnAffichageAdministrateur - renvoie sous forme de string les détails de l'administrateur
         * @return string - détails de l'administrateur
         */
string Administrateur::detailsAdministrateur(){
    return "Id admin : " + to_string(this->idAdmin) + "    Mail admin : " + this->mailAdmin + "   Pseudo admin : " + this->pseudoAdmin + "\n";
}
