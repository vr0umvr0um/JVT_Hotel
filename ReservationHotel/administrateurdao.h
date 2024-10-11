#ifndef ADMINISTRATEURDAO_H
#define ADMINISTRATEURDAO_H

#include "administrateur.h"
#include "dao.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>
#include <QCryptographicHash> //Hasher des QString
#include <QtWidgets>
#include <QtCharts>

using namespace std;

class AdministrateurDAO : public DAO{
    public:
        AdministrateurDAO();

        /**
         * @brief creer
         * Cette méthode permet de créer un admin en base
         * @param Administrateur
         * @return Administrateur - renvoie l'admin crée avec son id mis à jour
         *                   en corrélation avec celui en base
         */
        Administrateur creer(Administrateur admin);

        /**
         * @brief updater
         * Cette méthode permet d'update l'admin, qu'on donne en paramètre, dans la base de données
         * @param Administrateur
         * @return Administrateur
         */
        Administrateur updater(Administrateur admin);

        /**
         * @brief supprimer
         * Cette méthode supprime l'admin, en paramètre, de la base de données
         * @param Administrateur
         */
        void supprimer(Administrateur admin);

        /**
         * @brief lire
         * Cette méthode renvoie l'admin en base dont l'id est celui passé en paramètre
         * @param idAdmin - int
         * @return Administrateur
         */
        Administrateur lire(int idAdmin);

        /**
         * @brief lireAllAdminExceptMe
         * Cette méthode sert à un admin pour renvoyer la liste de tout les admins sans lui
         * @param idAdminAPasRenvoyer - id de l'admin qu'il ne faut pas renvoyer c'est à dire celui qui demande la liste des admins
         * @return vector<Administrateur>
         */
        vector<Administrateur> lireAllAdminExceptMe(int idAdminAPasRenvoyer);

        /**
         * @brief isMailUsed
         * On cherche dans la table admin si le paramètre mail est déja utilisé ou non
         * @param mail - string correspondant à un mail
         * @return bool - true si déja utilisé sinon false
         */
        bool isMailUsed(string mail);

        Administrateur connexionAdmin(QString mailAdmin, QString mdpAdmin);

        // ------------- Méthodes de statistiques
        // récupérer le nombre de clients en plus par annee/mois
        map<vector<string>,int> getNbClientsYM();
        // récuperer le max du nombre de clients en plus sur l'app par mois
        int getMaxNbClientsYM(map<vector<string>, int> dico);
        // Renvoie l'instance du graphe rempli
        QChartView* getGrapheNbClientsYM();

        // récupérer le nombre de réservations par annee/mois
        map<vector<string>,int> getNbReservationsYM();
        // récuperer le max du nombre de réservations sur l'app par mois
        int getMaxNbReservationsYM(map<vector<string>, int> dico);
        // Renvoie l'instance du graphe rempli
        QChartView* getGrapheNbReservationsYM();

        // récupérer le nombre de clients par departement
        map<string,int> getNbClientsDep();
        // récuperer le max du nombre de clients par departement
        int getMaxNbClientsDep(map<string,int> dico);
        // Renvoie l'instance du graphe rempli
        QChartView* getGrapheNbClientsDep();
};
#endif // ADMINISTRATEURDAO_H
