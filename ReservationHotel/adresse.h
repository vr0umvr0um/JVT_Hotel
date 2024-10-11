#ifndef ADRESSE_H
#define ADRESSE_H

#include <string>

using namespace std;

// -------------------------------------

/**
 * @brief la classe Adresse
 * Cette classe va représenter des adresses physiques
 * Auteur : Forest Jules
 */
class Adresse{
    private:
        int idAdresse;
        int numero;
        string rue;
        string ville;
        int codePostal;
        string pays;
    public:
        Adresse();
        Adresse(int idAdresse, int numero, string rue, string ville, int codePostal, string pays);
        ~Adresse();

        // ------------ Getters et Setters -------------

        /**
         * @brief getIdAdresse - renvoie l'id de l'adresse
         * @return int - id de l'adresse
         */
        int getIdAdresse();

        /**
         * @brief getNumero
         * @return int - numero d'adresse
         */
        int getNumero();

        /**
         * @brief getRue
         * @return string - rue de l'adresse
         */
        string getRue();

        /**
         * @brief getVille
         * @return string - ville de l'adresse
         */
        string getVille();

        /**
         * @brief getCodePostal
         * @return int - codePostal de l'adresse
         */
        int getCodePostal();

        /**
         * @brief getPays
         * @return string - pays de l'adresse
         */
        string getPays();

        /**
         * @brief setId - remplace l'id de l'adresse par celle en paramètre
         * @param id
         */
        void setId(int id);


        // ----------- Fonctions usuelles ------------

        /**
         * @brief afficheAdresse - affiche en console les détails de l'adresse
         */
        void afficheAdresse();

        /**
         * @brief returnAffichageAdresse - renvoie sous forme de string les détails de l'adresse
         * @return string - détails de l'adresse
         */
        string detailsAdresse();
};

#endif // ADRESSE_H
