#ifndef ADRESSEDAO_H
#define ADRESSEDAO_H

#include <adresse.h>
#include <dao.h>

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>

using namespace std;

// ----------------------------

/**
 * @brief classe AdresseDAO
 * Cette classe va représenter la porte d'entrée dans la bdd pour les adresses et donne différentes
 * fonctions qui permettront d'interagir avec
 * Auteur : Forest Jules
 */
class AdresseDAO : public DAO{
    public:
        AdresseDAO();

        /**
         * @brief creer
         * Cette méthode permet de créer une adresse en base
         * @param adresse
         * @return Adresse - renvoie l'adresse crée avec son id mis à jour
         *                   en corrélation avec celui en base
         */
        Adresse creer(Adresse adresse);

        /**
         * @brief updater
         * Cette méthode permet d'update l'adresse qu'on lui donne en paramètre dans la base de données
         * @param adresse
         * @return Adresse
         */
        Adresse updater(Adresse adresse);

        /**
         * @brief supprimer
         * Cette méthode supprime l'adresse en paramètre de la base de données
         * @param adresse
         */
        void supprimer(Adresse adresse);

        /**
         * @brief lire
         * Cette méthode renvoie l'adresse en base dont l'id est celui passé en paramètre
         * @param idAdresse
         * @return Adresse
         */
        Adresse lire(int idAdresse);
};

#endif // ADRESSEDAO_H
