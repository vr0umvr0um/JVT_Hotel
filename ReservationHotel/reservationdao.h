#ifndef RESERVATIONDAO_H
#define RESERVATIONDAO_H

#include <QString>
#include <vector>

#include "dao.h"
#include "reservation.h"

// -----------------------------

/**
 * @brief la classe ReservationDAO
 * Cette classe va représenter la porte d'entrée dans la bdd pour les reservations et donne différentes
 * fonctions qui permettront d'interagir avec
 * @author Forest Jules
*/
class ReservationDAO : public DAO{
    public:
        ReservationDAO();
        Reservation creer(Reservation reservation);
        Reservation updater(Reservation reservation);
        void supprimer(Reservation reservation);
        Reservation lire(int idReservation);

        /**
         * Cette méthode permet de lire une information à partir de différents types de paramètres.
         *
         * @author Vanessa Antivackis
         * @brief lire
         * @param mailClient
         * @param dateA
         * @param dateD
         * @param numChambre
         * @return
         */
        Reservation lire(QString mailClient, QString dateA, QString dateD, QString numChambre);

        vector<Reservation> lireAll(string ordonnancement);
};

#endif // RESERVATIONDAO_H
