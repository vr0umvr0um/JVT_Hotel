#ifndef SINGLECONNECTION_H
#define SINGLECONNECTION_H

#include <QSqlDatabase>
#include <string>
#include <QDebug>
#include <QSqlError>

using namespace std;

/**
 * @brief The SingleConnection class
 * @author Forest Jules
 */
class SingleConnection {
    public:
        SingleConnection(string hostName, string dbName, string login, string password);
        ~SingleConnection();

        /**
       * Renvoie la connexion actuelle à la base de données. Si aucune connexion
       * n'existe, une nouvelle est établie avec la base de données par défaut
       * (absences).
       */
        static QSqlDatabase getInstance();

        /**
       * Ferme la connexion actuelle à la base de données.
       */
        static void close();

    private:
        static QSqlDatabase db;
};

#endif // SINGLECONNECTION_H
