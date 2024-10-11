#ifndef RESERVATION_H
#define RESERVATION_H

#include "chambre.h"
#include "client.h"

using namespace std;

// ----------------------------

/**
 * @brief la classe Reservation
 * Cette classe représente de manière applicative les Reservations
 * @author : Forest Jules
 */
class Reservation {
    private:
        int idReservation;
        string dateArrive;
        string dateDepart;
        int estValide, estTraite;
        Chambre chambre;
        Client client;

    public:
        Reservation(int idReservation, string dateArrive, string dateDepart, int estValide, int estTraite, Chambre chambre, Client client);
        Reservation();
        ~Reservation();

        // --------------- getters et setters ------------
        /**
         * @brief getIdReservation
         * @return int - id de la reservation
         */
        int getIdReservation();

        /**
         * @brief getDateArrive
         * @return string - date d'arrive de la reservation
         */
        string getDateArrive();

        /**
         * @brief getDateDepart
         * @return string - date de depart de la reservation
         */
        string getDateDepart();

        /**
         * @brief getEstValide
         * @return
         */
        int getEstValide();

        /**
         * @brief getEstTraite
         * @return
         */
        int getEstTraite();

        /**
         * @brief getChambre
         * @return
         */
        Chambre getChambre();

        /**
         * @brief getClient
         * @return Client - client qui a fait la réservation
         */
        Client getClient();

        /**
         * @brief setIdReservation
         * Modifie l'id de la réservation avec celui en paramètre
         * @param id
         */
        void setIdReservation(int id);

        /**
         * @brief setDateArrive
         * Modifie la date d'arrivee
         * @param date
         */
        void setDateArrive(string date);

        /**
         * @brief setDateDepart
         * Modifie la date de depart
         * @param date
         */
        void setDateDepart(string date);

        /**
         * @brief setEstValide
         * @param val
         */
        void setEstValide(int val);
        /**
         * @brief setEstTraite
         * @param val
         */
        void setEstTraite(int val);

        // ----------- fonctions usuelles -----------
        /**
         * @brief afficherReservation
         * Affiche en console les détails de la réservation
         */

        void afficherReservation();

        /**
         * @brief getDetails
         * @return string - détails de la reservation sous forme de string
         */
        string getDetails();
};

#endif // RESERVATION_H
