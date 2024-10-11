#ifndef CLIENT_H
#define CLIENT_H

#include "adresse.h"

#include <string>

using namespace std;

/**
 * Classe fournit les constructeurs, getters et setters
 * des clients de la BDD.
 *
 * @brief Classe Client
 * @author Vanessa Antivackis
 */
class Client{
    private:
        /**
         *
         * Permet de stocker l'identifiant d'un client.
         *
         * @brief idClient
         */
        int idClient;

        /**
         *
         * Permet de stocker le nom, prenom, telephone, mail et mot de passe d'un client.
         *
         * @brief nomClient
         */
        string nomClient, prenomClient, telephone, mailClient, mdpClient;

        /**
         *
         * Permet de stocker une adresse.
         *
         * @brief adresse
         */
        Adresse adresse;

    public:

        // ----------- Constructeurs et Déstructeur ----------

        /**
         * Constructeur avec les paramètres suivants:
         *
         * @brief Client
         * @param idClient
         * @param nomClient
         * @param prenomClient
         * @param telephone
         * @param mailClient
         * @param mdpClient
         * @param idAdresse
         * @param numero
         * @param rue
         * @param ville
         * @param codePostal
         * @param pays
         */
        Client(int idClient, string nomClient, string prenomClient, string telephone, string mailClient, string mdpClient, Adresse adresse);
        /**
         * Constructeur par défaut de l'objet Client().
         *
         * @brief Client
         */
        Client();
        /**
         * Déstructeur de l'objet Client().
         */
        ~Client();

        // ----------- Getters et Setters ----------

        /**
         * Méthode qui retourne l'identifiant d'un client.
         *
         * @brief getIdClient
         * @return idClient
         */
        int getIdClient();

        /**
         * Méthode qui modifie l'identifiant d'un client.
         *
         * @brief setIdClient
         * @param idClient
         */
        void setIdClient(int idClient);

        /**
         * Méthode qui retourne le nom d'un client.
         *
         * @brief getNomClient
         * @return nomClient
         */
        string getNomClient();

        /**
         * Méthode qui modifie le nom d'un client.
         *
         * @brief setNomClient
         * @param nomClient
         */
        void setNomClient(string nomClient);

        /**
         * Méthode qui retourne le prénom d'un client.
         *
         * @brief getPrenomClient
         * @return prenomClient
         */
        string getPrenomClient();

        /**
         * Méthode qui modifie le prénom d'un client.
         *
         * @brief setPrenomClient
         * @param prenomClient
         */
        void setPrenomClient(string prenomClient);

        /**
         * Méthode qui retourne le téléphone d'un client.
         *
         * @brief getTelephoneClient
         * @return telephone
         */
        string getTelephoneClient();

        /**
         * Méthode qui modifie le téléphone d'un client.
         *
         * @brief setTelephoneClient
         * @param telephone
         */
        void setTelephoneClient(string telephone);
        /**
         * Méthode qui retourne le mail d'un client.
         *
         * @brief getMailClient
         * @return mail
         */
        string getMailClient();

        /**
         * Méthode qui modif le mail d'un client.
         *
         * @brief setMailClient
         * @param mailClient
         */
        void setMailClient(string mailClient);

        /**
         * Méthode qui retourne le mot de passe d'un client.
         *
         * @brief getMdpClient
         * @return mdpClient
         */
        string getMdpClient();

        /**
         * Méthode qui retourne le mot de passe d'un client.
         *
         * @brief setMdpClient
         * @param mdpClient
         */
        void setMdpClient(string mdpClient);

        /**
         * Méthode qui retourne tous les attributs d'une adresse
         *
         * @brief getAdresse
         * @return adresse
         */
        Adresse getAdresse();

        // --------- Fonctions usuelles -----------

        /**
         * Méthode permettant d'afficher les détails du client.
         *
         * @brief afficherDetails
         */
        void afficherDetails();
};

#endif // CLIENT_H
