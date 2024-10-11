#ifndef CHAMBREDAO_H
#define CHAMBREDAO_H

#include "dao.h"
#include "chambre.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>

#include <vector>

using namespace std;

// --------------------------

/**
 * @brief classe ChambreDAO
 * Cette classe va représenter la porte d'entrée dans la bdd pour les chambres et donne différentes
 * fonctions qui permettront d'interagir avec
 * Auteur : Forest Jules
 */
class ChambreDAO : public DAO{
public:
    ChambreDAO();

    /**
     * @brief creer
     * Cette méthode crée une chambre en base via celle mise en paramètre
     * @param chambre
     * @return Chambre - instance mise en paramètre mise a jour avec son id en base
     */
    Chambre creer(Chambre chambre);

    /**
     * @brief updater
     * Cette méthode update la chambre correspondante à celle en paramètre
     * @param chambre
     * @return Chambre
     */
    Chambre updater(Chambre chambre);

    /**
     * @brief supprimer
     * Cette méthode supprime la chambre correspondante à celle en paramètre dans la BDD
     * @param chambre
     */
    void supprimer(Chambre chambre);

    /**
     * @brief lire
     * Cette méthode renvoie la chambre en BDD correspondante à l'id mit en paramètre
     * @param idChambre
     * @return Chambre
     */
    Chambre lire(int idChambre);

    /**
     * Méthode qui affiche les informations
     * liées à un objet client
     * dans la base de données à partir d'un numero de chambre.
     *
     * @author Vanessa Antivackis
     * @brief lire
     * @param numChambre
     * @return chambre
     */
    Chambre lire(QString numChambre);

    /**
     * @brief lireParIDHotel
     * Renvoie les chambres d'un hôtel
     * @param idHotel
     * @return vecteur de Chambre
     */
    vector<Chambre> lireParIDHotel();
};

#endif // CHAMBREDAO_H
