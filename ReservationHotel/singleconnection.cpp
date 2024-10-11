#include "singleconnection.h"

// ---------------- Constructeur ---------------
/**
 * @brief SingleConnection::SingleConnection
 * Constructeur de singleConnection, permet de créer une connexion unique à la bdd
 * @param hostName : nom de l'hôte de la bdd
 * @param dbName : nom de la base de données
 * @param login : login
 * @param password : mot de passe du login
 */
SingleConnection::SingleConnection(string hostName, string dbName, string login, string password) {
    // Connexion à la base de données du nom : reservationhotel
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(QString::fromStdString(hostName));
    db.setDatabaseName(QString::fromStdString(dbName));
    db.setUserName(QString::fromStdString(login));
    db.setPassword(QString::fromStdString(password));

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
    }

    qDebug() << "Connexion réussie !";
}


// ---------------- fonctions usuelles ----------------
/**
* Renvoie la connexion actuelle à la base de données. Si aucune connexion
* n'existe, une nouvelle est établie avec la base de données par défaut
* (absences).
*
* @return connect sinon null - valeur représentant la connexion établit à la
*         base de données
*/
QSqlDatabase SingleConnection::getInstance() {
    if (!db.open()) {
        new SingleConnection("localhost", "reservationhotel", "root", "");
    }
    return db;
}

/**
 * @brief SingleConnection::close
 * Permet de fermer la connexion en cours à la bdd
 */
void SingleConnection::close() {
    db.close();
}
