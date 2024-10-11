/**
 * @author Forest Jules
*/
#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include <string>

using namespace std;

// -------------------------------------

class Administrateur {
    private:
        int idAdmin;
        string mailAdmin;
        string mdpAdmin;
        string pseudoAdmin;

    public:
        Administrateur(int idAdmin, string mailAmdin, string mdpAdmin, string pseudoAdmin);
        Administrateur();
        ~Administrateur();

        // ------------------- Getters et setters ------------------

        int getIdAdmin();
        string getMailAdmin();
        string getMdpAdmin();
        string getPseudoAdmin();
        void setIdAmin(int newIdAdmin);
        void setMailAdmin(string newMailAdmin);
        void setMdpAdmin(string newMdpAdmin);
        void setPseudoAdmin(string newPseudoAdmin);


        // ----------- Fonctions usuelles ------------

        /**
         * @brief afficheAdministrateur - affiche en console les détails de l'administrateur
         */
        void afficheAdministrateur();

        /**
         * @brief returnAffichageAdministrateur - renvoie sous forme de string les détails de l'administrateur
         * @return string - détails de l'administrateur
         */
        string detailsAdministrateur();
};

#endif // ADMINISTRATEUR_H
