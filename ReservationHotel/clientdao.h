#ifndef CLIENTDAO_H
#define CLIENTDAO_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QCryptographicHash>       //Hasher des QString

#include "client.h"
#include "dao.h"

using namespace std;

/**
 * Classe permet d'ajouter, supprimer, modifier et lire
 * un client de la BDD.
 *
 * @brief Classe ClientDAO
 * @author Vanessa Antivackis
 */
class ClientDAO : public DAO{

    public:
        //pas de constructeur, on prend celui de la classe mère DAO
        ClientDAO();

        // --------- Fonctions CRUD -----------

        /**
         * Méthode qui créer un objet Client
         * dans la base de données.
         *
         * @brief creer
         * @param client
         * @return
         */
        Client creer(Client client);

        /**
         * Méthode qui met à jours
         * les informations d'un objet Client
         * dans la base de données.
         *
         * @brief updater
         * @param client
         * @return
         */
        Client updater(Client client);

        /**
         * Méthode qui supprimer un objet Client
         * dans la base de données.
         *
         * @brief supprimer
         * @param client
         */
        void supprimer(Client client);

        /**
         * Méthode qui affiche les informations
         * liées à un objet client
         * dans la base de données à partir d'un Id.
         *
         * @brief lire
         * @param idClient
         * @return client
         */
        Client lire(int idClient);

        /**
         * Méthode qui affiche les informations
         * liées à un objet client
         * dans la base de données à partir d'un mail
         *
         * @brief lire
         * @param mailClient
         * @return
         */
        Client lire(QString mailClient);

        // --------- Fonctions usuelles -----------
        /**
         * Méthode qui affiche les informations
         * liées à un objet client
         * dans la base de données.
         *
         * @brief clientDAO
         * @param mailClient
         * @return
         */
        Client connexionClient(QString mailClient, QString mdpClient);

        /**
         *
         * Méthode qui renvoie un vector de Client.
         *
         * @brief lireAllClients
         * @return vector<Client>
         */
        vector<Client> lireAllClients();

};

#endif // CLIENTDAO_H
